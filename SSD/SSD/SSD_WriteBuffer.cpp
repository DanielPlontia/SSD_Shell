#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class SSD_WriteBuffer {
	friend std::unique_ptr<SSD_WriteBuffer> std::make_unique<SSD_WriteBuffer>();
public:
	static std::unique_ptr<SSD_WriteBuffer>& getInstance() {
		static std::unique_ptr<SSD_WriteBuffer> write_buffer{ std::make_unique<SSD_WriteBuffer>() };
		return write_buffer;
	}

	~SSD_WriteBuffer() {
		dump_buffer_data();
	}

	void read(int addr) {
		if (commands.size() == 10) {
			flush();
		}
	}

	void write(int addr, unsigned int data) {
		std::stringstream ss;
		ss << "W " << addr << " " << data << std::endl;
		commands.push_back(ss.str());

		if (commands.size() == 10) {
			flush();
		}
	}

	void erase(int addr, int size) {

	}

	void flush() {

	}

private:
	SSD_WriteBuffer()
	{
		buffer_file_ = "./buffer.txt";

		load_buffer_data();
	}

	SSD_WriteBuffer& operator=(const SSD_WriteBuffer& other) = delete;
	SSD_WriteBuffer(const SSD_WriteBuffer& other) = delete;

	std::string buffer_file_;
	std::vector<std::string> commands;

	void load_buffer_data() {
		try {
			std::ifstream file;
			file.open(buffer_file_);
			if (!file.is_open()) return;

			std::string line;
			while (std::getline(file, line)) {
				line += '\n';
				commands.push_back(line);
			}
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

	void optimize() {

	}
};