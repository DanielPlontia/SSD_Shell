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
#include "SSD_WriteBuffer.cpp"
#include "read.cpp"
#include "write.cpp"
#include "erase.cpp"

#include "../logger/Logger.h"
#pragma comment (lib, "../x64/Debug/logger.lib")

using std::vector;
using std::string;

class SSD_Invoker {
public:
	SSD_Invoker(vector<string> userCommand)
	{
		WriteLog(__FUNCTION__, "test");
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
	std::unique_ptr<SSD_WriteBuffer> write_buffer = std::move(SSD_WriteBuffer::getInstance());
	vector<string> userCmd;
	std::shared_ptr<Command> command_Instance;
	std::shared_ptr<SSD_HW> SSD_Instance;

	std::shared_ptr<SSD_HW> getSSD()
	{
		return std::make_shared<MySSD>();
	}

	std::shared_ptr<Command> getCmdInstance()
	{
		if (SSD_Instance == nullptr || userCmd.empty())
			return nullptr;

		if (userCmd[0] == "R") {
			return std::make_shared<ReadCmd>(SSD_Instance.get(), write_buffer.get());
		}
		if (userCmd[0] == "W") {
			return std::make_shared<WriteCmd>(SSD_Instance.get(), write_buffer.get());
		}
		if (userCmd[0] == "E") {
			return std::make_shared<EraseCmd>(SSD_Instance.get(), write_buffer.get());
		}
		return nullptr;
	}
};
