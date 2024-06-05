#pragma once

#include <string>

#define interface struct

interface exeRunner {
	virtual bool runner(std::string cmd) = 0;
};
