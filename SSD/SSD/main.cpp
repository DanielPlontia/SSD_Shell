#pragma once
#include "SSD_Invoker.cpp"
#include <vector>
#include <string>
#include<iostream>

using namespace std;
int main(int argc, char *argv[]) {
	vector<string> command;

	if (argc == 1) {
		cout << "INVALID COMMAND" << endl;
		return -1;
	}

	for (int i = 1; i < argc; i++) {
		command.push_back(argv[i]);
	}
	SSD_Invoker invoker{ command };
	invoker.run();
}