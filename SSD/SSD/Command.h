#pragma once
#define interface struct

#include <vector>

interface Command{
public:
	virtual void execute() = 0;
	virtual bool check_validation(std::vector<int> operation) = 0;
};
