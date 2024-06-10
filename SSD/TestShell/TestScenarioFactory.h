#pragma once
#include <string>

#ifdef DEBUG
#pragma comment (lib, "../x64/Debug/logger.lib")
#else
#pragma comment (lib, "../x64/Release/logger.lib")
#endif // DEBUG

class TestScenario {
public:
	void run(std::string scenario);
};
