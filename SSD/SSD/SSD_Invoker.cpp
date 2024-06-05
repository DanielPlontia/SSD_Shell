#pragma once

#include <memory>
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

		SSD_Instance = std::move(getSSD());
		command_Instance = std::move(getCmdInstance());
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
	std::shared_ptr<Command> command_Instance;
	std::shared_ptr<SSD_HW> SSD_Instance;
	string mapping_instance;

	std::shared_ptr<SSD_HW> getSSD()
	{
		return std::make_shared<MySSD>();
	}

	std::shared_ptr<Command> getCmdInstance()
	{
		if (SSD_Instance == nullptr || userCmd.empty())
			return nullptr;

		if (userCmd[0] == "R") {
			mapping_instance = "read_instance";
			return std::make_shared<ReadCmd>(SSD_Instance.get());
		}
		if (userCmd[0] == "W") {
			mapping_instance = "write_instance";
			return std::make_shared<WriteCmd>(SSD_Instance.get());
		}
		return nullptr;
	}
};
