#pragma once
#include "../SSDShellLibrary/TestScenarioInterface.h"

#ifdef STRESSTEST_EXPORTS
#define TEST_DECLSPEC __declspec(dllexport)
#else
#define TEST_DECLSPEC __declspec(dllimport)
#endif

class StressTest : public TestScenarioInterface {
public:
	void execute();
private:
	void repeatReadOperation(int start, int end);
	void repeatWriteOperation(int start, int end, std::string data);

};

extern "C" {
	TEST_DECLSPEC void Run();
}