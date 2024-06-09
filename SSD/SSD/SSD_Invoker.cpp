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
				command_Instance->execute(userCmd);
			}
			catch (ReadException& e) {
				return e.what();
			}
			catch (WriteException& e) {
				return e.what();
			}
			catch (EraseException& e) {
				return e.what();
			}
			catch (FlushException& e) {
				return e.what();
			}
			catch (exception& e) {
				return e.what();
			}
		}

		return string();
	}
private:
	std::unique_ptr<SSD_WriteBuffer> write_buffer = std::move(SSD_WriteBuffer::getInstance());
	vector<string> userCmd;
	std::shared_ptr<Command> command_Instance;

	std::shared_ptr<Command> getCmdInstance()
	{
		if (userCmd.empty())
			return nullptr;

		if (userCmd[0] == "R") {
			return std::make_shared<ReadCmd>(write_buffer.get());
		}
		if (userCmd[0] == "W") {
			return std::make_shared<WriteCmd>(write_buffer.get());
		}
		if (userCmd[0] == "E") {
			return std::make_shared<EraseCmd>(write_buffer.get());
		}
		if (userCmd[0] == "F") {
			return std::make_shared<FlushCmd>(write_buffer.get());
		}
		return nullptr;
	}
};
