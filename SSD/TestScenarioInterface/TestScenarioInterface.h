#pragma once
#include "../SSDShellLibrary/TestScenarioInterface.h"

#ifdef TESTSCENARIO_EXPORT
#define TESTSCENARIO_DECLSPEC __declspec(dllexport)
#else
#define TESTSCENARIO_DECLSPEC __declspec(dllimport)
#endif

class TestScenarioInterface : public TestScenarioInterface {
public:
	void execute();
};

extern "C" {
	TESTSCENARIO_DECLSPEC void Run();
}