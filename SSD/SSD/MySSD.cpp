#include "SSD_HW.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

const int MAX_LBA = 100;

class MySSD : public SSD_HW {
public:
	MySSD() {
		nand_file_ = "./nand.txt";
		result_file_ = "./result.txt";

		load_nand_data();
	};

	void read(int addr) override {
		dump_read_data(nand_data_[addr]);
	};

	void write(int addr, unsigned int data) override {
		nand_data_[addr] = data;
	};

	~MySSD() {
		dump_nand_data();
	}

private:
	std::string nand_file_;
	std::string result_file_;

	unsigned int nand_data_[MAX_LBA] = { 0 };

	void load_nand_data() {
		try {
			std::ifstream file;
			file.open(nand_file_);
			if (!file.is_open()) return;

			std::string line;
			while (std::getline(file, line)) {
				size_t pos = line.find(" ");
				int index = stoi(line.substr(0, pos));
				unsigned int value = std::stoul(line.substr(pos + 1, line.size()), nullptr, 16);
				nand_data_[index] = value;
			}
		}
		catch (std::exception& e) {
			throw e;
		}
	}

	void dump_nand_data() {
		try {
			std::ofstream file;
			file.open(nand_file_);

			for (int i = 0; i < MAX_LBA; i++) {
				std::stringstream ss;
				ss << i << " 0x" << std::setfill('0') << std::setw(8) << std::hex << nand_data_[i];
				file << ss.str() << std::endl;
			}
		}
		catch (std::exception& e) {
			throw e;
		}
	}

	void dump_read_data(unsigned int value) {
		try {
			std::ofstream file;
			file.open(result_file_);

			std::stringstream ss;
			ss << "0x" << std::setfill('0') << std::setw(8) << std::hex << value;
			file << ss.str() << std::endl;
		}
		catch (std::exception& e) {
			throw e;
		}
	}
};