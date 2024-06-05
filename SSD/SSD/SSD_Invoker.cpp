#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "Command.h"
#include "SSD_HW.h"
#include "MySSD.cpp"
#include "read.cpp"
#include "write.cpp"

using std::vector;
using std::string;

class WriteCmd;
class ReadCmd;

class SSD_Invoker {
public:
	SSD_Invoker(vector<string> userCommand)
	{
		mapping_instance = "";

		userCmd = userCommand;

		SSD_Instance = getSSD();

		command_Instance = getCmdInstance();
	}

	string run()
	{
		if (command_Instance == nullptr)
		{
			std::cout << "INVALID COMMAND." << std::endl;
		}
		else {
			try {
				command_Instance->execute(userCmd);
				deleteInstance();
			}
			catch (ReadException e) {
				std::cout << e.what() << endl;
				return "ReadException";
			}
			catch (WriteException e) {
				std::cout << e.what() << endl;
				return "WriteException";
			}
			catch (exception e) {
				std::cout << e.what() << endl;
				return "cmd validation check Throw something";
			}
		}

		return mapping_instance;
	}

private:
	vector<string> userCmd;
	Command* command_Instance;
	SSD_HW* SSD_Instance;
	string mapping_instance;

	SSD_HW* getSSD()
	{
		return new MySSD();
	}

	void deleteInstance() {
		delete SSD_Instance;
		delete command_Instance;
		SSD_Instance = nullptr;
		command_Instance = nullptr;
	}

	Command* getCmdInstance()
	{
		if (SSD_Instance == nullptr)
			return nullptr;


		if (userCmd[0] == "R") {
			mapping_instance = "read_instance";
			return new ReadCmd(SSD_Instance);
		}
		if (userCmd[0] == "W") {
			mapping_instance = "write_instance";
			return new WriteCmd(SSD_Instance);
		}
		return nullptr;

	}
};