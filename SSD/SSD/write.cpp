#include <stdexcept>

#include "SSD_HW.h"
#include "Command.h"

class WriteException : public std::exception {
public:
	char const* what() const override {
		return "WRITE :validation error!";
	}
};

class WriteCmd : public Command {
	// Command을(를) 통해 상속됨
public:
	WriteCmd(SSD_HW* _ssd) : ssd_hw{ _ssd } {};

	void execute(const std::vector<std::string>& operation) override
	{
		cmd_arg = operation;
		if (check_validation() == false) {
			throw WriteException();
		}
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