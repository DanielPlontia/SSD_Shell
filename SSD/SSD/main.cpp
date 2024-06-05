#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "SSD_Invoker.cpp"

using namespace std;
int main(int argc, char *argv[]) {
	vector<string> command;

	if (argc == 1) {
		std::cerr << "INVALID ARGUMENTS SIZE" << endl;
		return -1;
	}

	for (int i = 1; i < argc; i++) {
		command.push_back(argv[i]);
	}
	SSD_Invoker invoker{ command };
	std::string err_msg = invoker.run();
	if (err_msg.empty() == false) {
		std::cerr << err_msg << std::endl;
		return -2;
	}
	return 0;
}