#pragma once

#include <string>
#include "Command.h"
#include "read.cpp"
#include "write.cpp"
#include "erase.cpp"
#include "flush.cpp"

class CommandFactory {
public:
	std::shared_ptr<Command> getCmdInstance(const std::string& cmd)
	{
		if (cmd.empty())
			return nullptr;

		if (cmd == "R") {
			return std::make_shared<ReadCmd>();
		}
		if (cmd == "W") {
			return std::make_shared<WriteCmd>();
		}
		if (cmd == "E") {
			return std::make_shared<EraseCmd>();
		}
		if (cmd == "F") {
			return std::make_shared<FlushCmd>();
		}
		return nullptr;
	}
};