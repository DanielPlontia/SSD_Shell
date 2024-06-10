#pragma once
#include "../SSDShellLibrary/TestScenarioInterface.h"

#ifdef READTEST_EXPORTS
#define READTEST_DECLSPEC __declspec(dllexport)
#else
#define READTEST_DECLSPEC __declspec(dllimport)
#endif

class ReadTest : public TestScenarioInterface {
public:
	bool execute();
};

extern "C" {
	READTEST_DECLSPEC bool Run();
}