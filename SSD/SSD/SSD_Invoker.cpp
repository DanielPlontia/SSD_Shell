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

class WriteCmd;
class ReadCmd;

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
			std::cout << "INVALID COMMAND." << std::endl;
		}
		else {
			try {
				command_Instance->execute(userCmd);
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
	std::shared_ptr<Command> command_Instance;
	std::shared_ptr<SSD_HW> SSD_Instance;
	string mapping_instance;

	std::shared_ptr<SSD_HW> getSSD()
	{
		return std::shared_ptr<MySSD>(new MySSD);
	}

	std::shared_ptr<Command> getCmdInstance()
	{
		if (SSD_Instance == nullptr)
			return nullptr;

		if (userCmd[0] == "R") {
			mapping_instance = "read_instance";
			return std::shared_ptr<ReadCmd>(new ReadCmd(SSD_Instance.get()));
		}
		if (userCmd[0] == "W") {
			mapping_instance = "write_instance";
			return std::shared_ptr<WriteCmd>(new WriteCmd(SSD_Instance.get()));
		}
		return nullptr;

	}
};
