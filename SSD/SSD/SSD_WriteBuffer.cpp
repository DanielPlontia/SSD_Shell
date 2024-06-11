#pragma once

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include "SSD_HW.h"
#include "MySSD.cpp"
#include "include_logger.h"

class SSD_WriteBuffer {
public:
	static SSD_WriteBuffer* getInstance() {
		std::call_once(m_onceFlag, [] {
			write_buffer.reset(new SSD_WriteBuffer);
			});
		return write_buffer.get();
	}

	~SSD_WriteBuffer() {
		dump_buffer_data();
	}

	void read(int addr) {
		std::string command = check_fast_read(addr);
		if (commands.empty() || command.empty()) {
			ssd_hw->read(addr);
			return;
		}
		fast_read(command);
	}

	void write(int addr, unsigned int data) {
		std::stringstream ss;
		ss << "W " << addr << " " << data << std::endl;
		commands.push_back(ss.str());

		if (need_self_flush()) {
			flush();
		}
	}

	void erase(int addr, int size) {
		std::stringstream ss;
		ss << "E " << addr << " " << size << std::endl;
		commands.push_back(ss.str());

		if (need_self_flush()) {
			flush();
		}
	}

	void flush() {
		optimize();

		execute_ssd();
		commands.clear();
	}

private:
	static std::shared_ptr<SSD_WriteBuffer> write_buffer;
	static std::once_flag m_onceFlag;

	SSD_WriteBuffer()
	{
		buffer_file_ = "./buffer.txt";
		optimize_file_ = "./optimize.txt";
		result_file_ = "./result.txt";
		ssd_hw = std::make_shared<MySSD>();

		load_buffer_data();
	}

	SSD_WriteBuffer& operator=(const SSD_WriteBuffer& other) = delete;
	SSD_WriteBuffer(const SSD_WriteBuffer& other) = delete;

	std::string buffer_file_;
	std::string optimize_file_;
	std::string result_file_;
	std::vector<std::string> commands;
	std::shared_ptr<SSD_HW> ssd_hw;

	void load_buffer_data() {
		try {
			std::ifstream file;
			file.open(buffer_file_);
			if (!file.is_open()) return;

			std::string line;
			while (std::getline(file, line)) {
				if (line == "") continue;
				line += '\n';
				commands.push_back(line);
			}
			file.close();
		}
		catch (std::exception& e) {
			throw e;
		}
	}

	void dump_buffer_data() {
		try {
			std::ofstream file;
			file.open(buffer_file_);

			for (std::string command : commands) {
				file << command;
			}
			file.close();
		}
		catch (std::exception& e) {
			throw e;
		}
	}

	bool need_self_flush() {
		if (commands.size() >= 10) return true;
		return false;
	}

	void optimize() {
		remove_redundant_command();
		merge_erase_command();
		std::ofstream file;
		file.open(optimize_file_);

		for (std::string command : commands) {
			file << command;
		}
		file.close();
	}

	// 역순으로 동일한 address에 access하는 command를 제거
	// erase는 모든 범위가 포함되어야 삭제 가능
	void remove_redundant_command() {
		std::vector<std::string> new_commands = {};
		std::set<unsigned int> addrs = {};
		for (auto rit = commands.rbegin(); rit != commands.rend(); ++rit) {
			std::string command = *rit;
			std::vector<std::string> words = parse_command(command);
			std::string opcode = words.at(0);
			int addr = stoi(words.at(1));
			if (opcode == "W" && addrs.find(addr) == addrs.end()) {
				addrs.insert(addr);
				new_commands.push_back(command);
			}
			else if (opcode == "E") {
				int size = stoi(words.at(2));

				// check already existing range
				bool range_exist = true;
				for (int a = addr; a < addr + size; a++) {
					if (addrs.find(a) == addrs.end()) {
						range_exist = false;
					}
				}
				if (range_exist) continue;

				// check if we can modify start_addr and size
				int size_left = size;
				int start_addr = addr;
				// from start
				for (int a = addr; a < addr + size; a++) {
					if (addrs.find(a) != addrs.end()) {
						size_left--;
						start_addr++;
						continue;
					}
					break;
				}
				// from end
				for (int a = addr + size - 1; size_left > 0 && a >= addr; a--) {
					if (addrs.find(a) != addrs.end()) {
						size_left--;
						continue;
					}
					break;
				}

				if (size_left != 0) {
					std::stringstream ss;
					ss << "E " << start_addr << " " << size_left << std::endl;
					new_commands.push_back(ss.str());

					for (int a = start_addr; a < start_addr + size_left; a++) {
						addrs.insert(a);
					}
				}
			}
		}
		reverse(new_commands.begin(), new_commands.end());
		commands = new_commands;
	}

	void merge_erase_command() {
		std::vector<std::string> new_commands = {};
		std::set< std::set<int> > erase_sets = {};
		std::set<std::string> erase_commands = {};
		std::set<unsigned int> addrs = {};
		for (auto it = commands.begin(); it != commands.end(); ++it) {
			std::string command = *it;
			std::vector<std::string> words = parse_command(command);
			std::string opcode = words.at(0);
			int addr = stoi(words.at(1));
			if (opcode == "W") {
				new_commands.push_back(command);
			}
			else if (opcode == "E") {
				int size = stoi(words.at(2));

				// check subset
				std::set<int> target{};
				for (int a = addr; a < addr + size; a++) {
					target.insert(a);
				}

				bool is_subset = false;
				for (auto erase_set : erase_sets) {
					if (std::includes(erase_set.begin(), erase_set.end(), target.begin(), target.end())) {
						// target is subset of erase_set
						is_subset = true;
						break;;
					}
				}
				if (is_subset) continue;

				// check concat
				// from end
				int size_added = 0;
				int start_addr = addr + size;
				while (1) {
					if (addrs.find(start_addr + size_added) == addrs.end()) break;
					size_added++;
				}
				size += size_added;
				if (size_added > 0) {
					std::stringstream ss;
					ss << "E " << start_addr << " " << size_added << std::endl;
					erase_commands.erase(ss.str());

					target.clear();
					for (int a = start_addr; a < start_addr + size_added; a++) {
						target.insert(a);
					}
					erase_sets.erase(target);
				}

				// from start
				size_added = 0;
				start_addr = addr;
				while (1) {
					if (addrs.find(start_addr - size_added - 1) == addrs.end()) break;
					size_added++;
				}
				size += size_added;
				start_addr -= size_added;
				if (size_added > 0) {
					std::stringstream ss;
					ss << "E " << start_addr << " " << size_added << std::endl;
					erase_commands.erase(ss.str());

					target.clear();
					for (int a = start_addr; a < start_addr + size_added; a++) {
						target.insert(a);
					}
					erase_sets.erase(target);
				}

				std::stringstream ss;
				ss << "E " << start_addr << " " << size << std::endl;
				erase_commands.insert(ss.str());
				target.clear();
				for (int a = addr; a < addr + size; a++) {
					addrs.insert(a);
					target.insert(a);
				}
				erase_sets.insert(target);
			}
		}
		for (std::string command : erase_commands) {
			new_commands.insert(new_commands.begin(), command);
		}
		commands = new_commands;
	}

	void fast_read(std::string command) {
		try {
			unsigned int value = get_value(command);

			std::ofstream file;
			file.open(result_file_);
			std::stringstream ss;
			ss << "0x" << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << value;
			file << ss.str() << std::endl;
			file.close();
		}
		catch (std::exception& e) {
			throw e;
		}
	}

	std::vector<std::string> parse_command(std::string line) {
		std::regex regex{ R"([\s]+)" }; // split on space
		std::sregex_token_iterator tit{ line.begin(), line.end(), regex, -1 };
		std::vector<std::string> words{ tit, {} };
		return words;
	}

	std::string check_fast_read(int target_addr) {
		for (auto rit = commands.rbegin(); rit != commands.rend(); ++rit) {
			std::string command = *rit;
			std::vector<std::string> words = parse_command(command);
			std::string opcode = words.at(0);
			int addr = stoi(words.at(1));
			if (opcode == "W" && addr == target_addr) return command;
			if (opcode == "E") {
				int value = stoi(words.at(2));
				if (addr <= target_addr && target_addr < (addr + value)) return command;
			}
		}
		return "";
	}

	unsigned int get_value(std::string command) {
		std::vector<std::string> words = parse_command(command);
		std::string opcode = words.at(0);
		if (opcode == "W") {
			return std::stoul(words.back(), nullptr, 10);
		}
		if (opcode == "E") {
			return 0;
		}
		WRITE_LOG_WITHOUT_CONSOLE("Unreachable");
		return 0;
	}

	void execute_ssd() {
		for (std::string command : commands) {
			WRITE_LOG_WITHOUT_CONSOLE("Real Execute!! " + command);

			std::vector<std::string> words = parse_command(command);
			std::string opcode = words.at(0);
			int addr = stoi(words.at(1));
			if (opcode == "W") {
				unsigned int value = std::stoul(words.at(2), nullptr, 10);
				ssd_hw->write(addr, value);
			}
			else if (opcode == "E") {
				int size = stoi(words.at(2));
				for (int a = addr; a < addr + size; a++) {
					ssd_hw->write(a, 0);
				}
			}
		}
	}
};
