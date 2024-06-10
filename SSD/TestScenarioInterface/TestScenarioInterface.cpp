#include "../SSDShellLibrary/ssdExecutor.h"
#include "../SSDShellLibrary/TestShell.h"
#include "TestScenarioInterface.h"

#ifdef _DEBUG
#pragma comment (lib, "../x64/Debug/SSDShellLibrary.lib")
#else
#pragma comment (lib, "../x64/Release/SSDShellLibrary.lib")
#endif // _DEBUG

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

