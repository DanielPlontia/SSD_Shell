#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "exeRunner.h"
using namespace std;

interface dataReader {
public:
	virtual string fileRead() = 0;
};

class SddDataReader : public dataReader {
public:
	string fileRead() {
		// file read
		std::ifstream rfs;
		char readData[100];
		rfs.open("result.txt", 'r');
		rfs.getline(readData, 100);
		rfs.close();
		return readData;
	}
};

class TestShell {
public:
	struct inputData {
		std::string command;
		int dataAddr{ 0 };
		std::string data;
	};

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
		if (readedData[0] == "read") read();
		else if (readedData[0] == "exit") return;
		else if (readedData[0] == "write") 	write();
		else if (readedData[0] == "help") showHelp();
		else if (readedData[0] == "fullread") {
			SddDataReader dataReader;
			fullRead(&dataReader);
		}
		else if (readedData[0] == "fullwrite")	fullWrite();
		else
			return;
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

	void fullRead(dataReader*fileReader) {
		for (int index = 0; index < 100; ++index) {
			std::string cmd = "R ";
			cmd += to_string(index);
			myExecuter->runner(cmd);
			cout << fileReader->fileRead() << endl;
		}
	}

	void showHelp() {
	}

	void fullWrite() {
		std::string cmd = "W ";
		for (int index = 0; index < 100; ++index) {
			cmd += to_string(index);
			cmd += " ";
			cmd += readedData[1];
			myExecuter->runner(cmd);
		}
	}

};

