#include <iostream>
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


struct inputData {
	std::string command;
	int dataAddr{ 0 };
	std::string data;
};

class TestShell {
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

	void write(int addr, string data) {
		std::string cmd = "W ";
		cmd += to_string(addr);
		cmd += " ";
		cmd += data;
		myExecuter->runner(cmd);
	}
};
