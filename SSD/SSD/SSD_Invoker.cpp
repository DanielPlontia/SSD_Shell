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
			return "INVALID COMMAND.";
		}
		else {
			try {
				command_Instance->execute(userCmd);
			}
			catch (ReadException& e) {
				return e.what();
			}
			catch (WriteException& e) {
				return e.what();
			}
			catch (exception& e) {
				return e.what();
			}
		}

		return string();
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

	Command* getCmdInstance()
	{
		if (SSD_Instance == nullptr || userCmd.empty())
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
