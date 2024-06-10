#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "SSD_Invoker.cpp"
#include "include_logger.h"

using namespace std;

std::shared_ptr<SSD_WriteBuffer> SSD_WriteBuffer::write_buffer = NULL;
std::once_flag SSD_WriteBuffer::m_onceFlag;
int main(int argc, char *argv[]) {
	vector<string> command;

	if (argc == 1) {
		WriteLog("SSD::main", "INVALID ARGUMENTS SIZE");
		return -1;
	}

	for (int i = 1; i < argc; i++) {
		command.push_back(argv[i]);
	}
	SSD_Invoker invoker{ command };
	std::string err_msg = invoker.run();
	if (err_msg.empty() == false) {
		WriteLog("SSD::main", err_msg);
		return -2;
	}
	return 0;
}