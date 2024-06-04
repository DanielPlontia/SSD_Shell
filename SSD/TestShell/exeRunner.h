#pragma once

#include <string>

#define interface struct

interface exeRunner {
	virtual void runner(std::string cmd) = 0;
};
