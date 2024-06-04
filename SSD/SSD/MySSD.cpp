#include "SSD_HW.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

const int MAX_LBA = 100;

class MySSD : public SSD_HW {
public:
	MySSD() {
		nand_file_ = "nand.txt";
		result_file_ = "result.txt";

		set_nand_data();
	};

	void read(int addr) override {

	};

	void write(int addr, unsigned int data) override {

	};

private:
	string nand_file_;
	string result_file_;

	vector<unsigned int> nand_data_;

	void set_nand_data() {
	}
};