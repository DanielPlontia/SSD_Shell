#pragma once
#define Interface struct

#include <vector>

Interface Command{
public:
	virtual void execute() = 0;
	virtual bool check_validation(std::vector<int> operation) = 0;
};
