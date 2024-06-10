#pragma once

#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "Command.h"
#include "SSD_WriteBuffer.cpp"
#include "read.cpp"
#include "write.cpp"
#include "erase.cpp"
#include "flush.cpp"

using std::vector;
using std::string;

class SSD_Invoker {
public:
	SSD_Invoker(vector<string> userCommand)
	{
		userCmd = userCommand;
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
				execute_cmd_logging();
				command_Instance->execute(userCmd);
			}
			catch (exception& e) {
				return exceptionTypeHandle(e);
			}
		}

		return string();
	}
private:
	vector<string> userCmd;
	std::shared_ptr<Command> command_Instance;

	string exceptionTypeHandle(exception& e)
	{
		if (std::is_same<decltype(e), ReadException>::value)
			return dynamic_cast<ReadException*>(&e)->what();

		if (std::is_same<decltype(e), WriteException>::value)
			return dynamic_cast<WriteException*>(&e)->what();

		if (std::is_same<decltype(e), EraseException>::value)
			return dynamic_cast<EraseException*>(&e)->what();

		if (std::is_same<decltype(e), FlushException>::value)
			return dynamic_cast<FlushException*>(&e)->what();

		return e.what();
	}

	std::shared_ptr<Command> getCmdInstance()
	{
		if (userCmd.empty())
			return nullptr;

		if (userCmd[0] == "R") {
			WRITE_LOG_WITHOUT_CONSOLE("ReadCmd Instance Return"); 
			return std::make_shared<ReadCmd>();
		}
		if (userCmd[0] == "W") {
			WRITE_LOG_WITHOUT_CONSOLE("WriteCmd Instance Return"); 
			return std::make_shared<WriteCmd>();
		}
		if (userCmd[0] == "E") {
			WRITE_LOG_WITHOUT_CONSOLE("EraseCmd Instance Return"); 
			return std::make_shared<EraseCmd>();
		}
		if (userCmd[0] == "F") {
			WRITE_LOG_WITHOUT_CONSOLE("FlushCmd Instance Return"); 
			return std::make_shared<FlushCmd>();
		}
		return nullptr;
	}
	void execute_cmd_logging()
	{
		std::string raw_cmd;
		for (const auto& cmd : userCmd) {
			raw_cmd += cmd + " ";
		}
		WRITE_LOG_WITHOUT_CONSOLE("Execute!! " + raw_cmd);
	}
};
