#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

#include "exeRunner.h"

using namespace std;
using test_func = std::function<void()>;

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
	TestShell(exeRunner* exe, dataReader* reader) : myExecuter{ exe }, fileReader{ reader } {
		test_func_map.emplace("read", std::bind(&TestShell::read, this));
		test_func_map.emplace("write", std::bind(&TestShell::write, this));
		test_func_map.emplace("fullread", std::bind(&TestShell::fullRead, this));
		test_func_map.emplace("fullwrite", std::bind(&TestShell::fullWrite, this));
		test_func_map.emplace("help", std::bind(&TestShell::showHelp, this));
	}

	bool TestExecute(std::string inputData)
	{
		split_input_data(inputData);
		if (readedData[0] == "exit") return true;

		if (test_func_map.find(readedData[0]) == test_func_map.end()) {
			throw std::exception("Invalid Command");
		}
		return false;
	}

	void read() {
		std::string cmd = "R ";
		cmd += readedData[1];
		myExecuter->runner(cmd);
		cout << fileReader->fileRead() << endl;
	}

	void write() {
		std::string cmd = "W ";
		cmd += readedData[1];
		cmd += " ";
		cmd += readedData[2];
		myExecuter->runner(cmd);
	}

	void fullRead() {
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
private:
	unordered_map<string, test_func> test_func_map;
	vector<string> readedData;
	exeRunner* myExecuter;
	dataReader* fileReader;

	void split_input_data(string input) {
		istringstream ss(input);
		string subs1;

		while (getline(ss, subs1, ' ')) {
			readedData.push_back(subs1);
		}
	}
};

