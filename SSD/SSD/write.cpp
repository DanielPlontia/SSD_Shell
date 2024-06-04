#pragma once
#include "SSD_HW.h"
#include "Command.h"

class WriteCmd : public Command {
	// Command을(를) 통해 상속됨
public:
	WriteCmd(SSD_HW* _ssd) : ssd_hw{ _ssd } {};

	void execute(const std::vector<std::string>& operation) override
	{
		cmd_arg = operation;

	}

private:
	SSD_HW* ssd_hw;
	std::vector<std::string> cmd_arg;
	bool check_validation() override
	{
		return false;
	}
	void do_action() override
	{
	}
};