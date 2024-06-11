#pragma once

#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>
#include "include_logger.h"
#include "CmdFactory.h"
#include "SSD_WriteBuffer.cpp"

using std::vector;
using std::string;

class SSD_Invoker {
public:
	SSD_Invoker(vector<string> userCommand)
	{
		userCmd = userCommand;
		command_Instance = std::move(cmd_fac.getCmdInstance(userCmd[0]));
	}

	string run()
	{
		if (command_Instance == nullptr)
		{
			return "INVALID COMMAND.";
		}
		else {
			try {
				cmd_send_write_buf_logging();
				command_Instance->execute(userCmd);
			}
			catch (exception& e) {
				return exceptionTypeHandle(e);
			}
		}

		return string();
	}
private:
	CommandFactory cmd_fac;
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

	void cmd_send_write_buf_logging()
	{
		std::string raw_cmd;
		for (const auto& cmd : userCmd) {
			raw_cmd += cmd + " ";
		}
		WRITE_LOG_WITHOUT_CONSOLE("Send Write Buffer!! " + raw_cmd);
	}
};
