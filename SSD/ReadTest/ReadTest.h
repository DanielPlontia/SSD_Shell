#pragma once
#include "../SSDShellLibrary/TestScenarioInterface.h"

#ifdef READTEST_EXPORTS
#define READTEST_DECLSPEC __declspec(dllexport)
#else
#define READTEST_DECLSPEC __declspec(dllimport)
#endif

class ReadTest : public TestScenarioInterface {
public:
	void execute();
};

extern "C" {
	READTEST_DECLSPEC void Run();
}