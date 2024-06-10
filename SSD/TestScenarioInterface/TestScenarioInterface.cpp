#include "../SSDShellLibrary/ssdExecutor.h"
#include "../SSDShellLibrary/TestShell.h"
#include "TestScenarioInterface.h"

void TestScenarioInterface::execute() {
	ssdExecutor ssdExe;
	SddDataReader datareader;
	TestShell shell{ &ssdExe, &datareader };

	shell.TestExecute("read 3 ");
};

TestScenarioInterface _app;
void Run() {
	_app.execute();
}

