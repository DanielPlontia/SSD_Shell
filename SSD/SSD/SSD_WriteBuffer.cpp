#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
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
			WRITE_LOG_WITHOUT_CONSOLE("Can't Fast Read Address : " + std::to_string(addr) + " nand.txt read!!");
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
		result_file_ = "./result.txt";
		ssd_hw = std::make_shared<MySSD>();

		load_buffer_data();
	}

	SSD_WriteBuffer& operator=(const SSD_WriteBuffer& other) = delete;
	SSD_WriteBuffer(const SSD_WriteBuffer& other) = delete;

	std::string buffer_file_;
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
				line += '\n';
				commands.push_back(line);
				WRITE_LOG_WITHOUT_CONSOLE("Buffer Laod : " + line);
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
			int value = stoi(words.at(2));
			if (opcode == "W" && addr == target_addr) return command;
			if (opcode == "E" && (addr <= target_addr && target_addr < (addr + value))) return command;
		}
		return "";
	}

	unsigned int get_value(std::string command) {
		std::vector<std::string> words = parse_command(command);
		WRITE_LOG_WITHOUT_CONSOLE(words.back() + " stoul unsigned int"); 
		unsigned int value = std::stoul(words.back(), nullptr, 10);
		return value;
	}

	void execute_ssd() {
		for (std::string command : commands) {
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
					ssd_hw->write(addr, 0);
				}
			}
		}
	}
};