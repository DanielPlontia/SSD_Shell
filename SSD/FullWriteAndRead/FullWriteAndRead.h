#pragma once
#include "../SSDShellLibrary/TestScenarioInterface.h"

#ifdef FULLWRITEANDREAD_EXPORTS
#define TEST_DECLSPEC __declspec(dllexport)
#else
#define TEST_DECLSPEC __declspec(dllimport)
#endif

class FullWirteAndRead : public TestScenarioInterface {
public:
	void execute();
};

extern "C" {
	TEST_DECLSPEC void Run();
}