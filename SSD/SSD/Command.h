#pragma once
#define interface struct

#include <vector>
#include <string>

interface Command {
public:
	virtual void execute(const std::vector<std::string>& operation) = 0;
private:
	virtual bool check_validation() = 0;
	virtual void do_action() = 0;
};
