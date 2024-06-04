#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define interface struct

interface exeRunner {
	virtual void runner(std::string cmd) = 0;
};

class sddExeRunner : exeRunner{
public:
	void runner(std::string cmd) {
		// exe calling  byr cmd
		std::cout << "Runner called" << endl;
	}
};

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
	inputData readedData;
	exeRunner* myExecuter;
	
public:
	TestShell(exeRunner* exe) :
		myExecuter(exe) {
	}

	void read(int addr) {
		std::string cmd = "R ";
		cmd += to_string(addr);
		myExecuter->runner(cmd);
	}

	inputData inputStrParser(std::string inputCmd) {
		inputData ret;
		return ret;
	}

	void fullRead(dataReader *fileReader) {
		for (int index = 0; index < 100; ++index) {
			std::string cmd = "R ";
			cmd += to_string(index);
			myExecuter->runner(cmd);
			cout << fileReader->fileRead() << endl;
		}
	}

};


