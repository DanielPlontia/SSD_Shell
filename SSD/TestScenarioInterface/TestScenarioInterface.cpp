#include "ssdExecutor.h"
#include "TestShell.h"
#include "TestScenarioInterface.h"

void testApp::execute() {
	ssdExecutor ssdExe;
	SddDataReader datareader;
	TestShell shell{ &ssdExe, &datareader };

	shell.TestExecute("read 3 ");
};

testApp _app;
void Run() {
	_app.execute();
}

