#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

#include "exeRunner.h"

using namespace std;

struct test_func {
	test_func() = default;
	test_func(std::function<void()> _func, const char* _desc) : function{ _func }, description{ _desc } {}
	std::function<void()> function;
	std::string description;
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
	unordered_map<string, test_func> test_func_map;
	TestShell(exeRunner* exe, dataReader* reader) : myExecuter{ exe }, fileReader{ reader } {
		make_test_func_map();
	}

	bool TestExecute(std::string inputData)
	{
		split_input_data(inputData);
		if (readedData[0] == "exit") return true;

		if (test_func_map.find(readedData[0]) == test_func_map.end()) {
			throw std::exception("Invalid Command");
		}
		test_func_map[readedData[0]].function();
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
	void fullWrite() {
		std::string cmd = "W ";
		for (int index = 0; index < 100; ++index) {
			cmd += to_string(index);
			cmd += " ";
			cmd += readedData[1];
			myExecuter->runner(cmd);
		}
	}
	void showHelp() {
		for (auto& test_func : test_func_map) {
			std::cout << test_func.first << " : " << test_func.second.description << std::endl;
		}
	}

private:
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

	void make_test_func_map() {
		test_func_map.emplace("read", test_func{ std::bind(&TestShell::read, this), "SSD�� Ư�� �޸� ���� �о� Console�� ������ݴϴ�.\n���� : read [�ּ�]\n" });
		test_func_map.emplace("write", test_func{ std::bind(&TestShell::write, this), "SSD Ư�� �޸𸮿� ���� �����ϴ�. Data�� 0x�� �����ϴ� 4byte Hex string���� �ۼ����ּž� �մϴ�.\n���� : write [�ּ�] [Data]\n" });
		test_func_map.emplace("fullread", test_func{ std::bind(&TestShell::fullRead, this), "SSD ��� �޸� ���� �о� Console�� ������ݴϴ�.\n���� : fullread\n" });
		test_func_map.emplace("fullwrite", test_func{ std::bind(&TestShell::fullWrite, this), "SSD ��� �޸𸮿� ���� �����ϴ�. Data�� 0x�� �����ϴ� 4byte Hex string���� �ۼ����ּž� �մϴ�.\n���� : fullwrite [Data]\n" });
		test_func_map.emplace("help", test_func{ std::bind(&TestShell::showHelp, this), "TestShell���� ����� �� �ִ� Command�鿡 ���� ������ Ȯ�� �� �� �ֽ��ϴ�.\n" });
	}
};
