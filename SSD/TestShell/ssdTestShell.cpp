#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "exeRunner.h"
using namespace std;

class TestShell {
private:
	vector<string> readedData;
	exeRunner* myExecuter;

	void split_input_data(string input) {
		istringstream ss (input);
		string subs1;

		while(getline(ss,subs1,' ')){
			readedData.push_back(subs1);
		}
	}
	
public:
	TestShell(exeRunner* exe, string inputData) : myExecuter(exe)
	{
		split_input_data(inputData);
		if (readedData[0] == "Read") read();
		if (readedData[0] == "Write") write();
	}

	void read() {
		std::string cmd = "R ";
		cmd += readedData[1];
		myExecuter->runner(cmd);
	}

	void write() {
		std::string cmd = "W ";
		cmd += readedData[1];
		cmd += " ";
		cmd += readedData[2];
		myExecuter->runner(cmd);
	}
};
