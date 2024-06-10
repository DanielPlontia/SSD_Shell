#include "../SSDShellLibrary/ssdExecutor.h"
#include "../SSDShellLibrary/TestShell.h"
#include "ReadTest.h"

#ifdef _DEBUG
#pragma comment (lib, "../x64/Debug/SSDShellLibrary.lib")
#else
#pragma comment (lib, "../x64/Release/SSDShellLibrary.lib")
#endif // _DEBUG

bool ReadTest::execute() {
	ssdExecutor ssdExe;
	SddDataReader datareader;
	TestShell shell{ &ssdExe, &datareader };
	try {
		return shell.TestExecute("read 100 ");
	}
	catch (std::exception e)
	{
		return false;
	}
};

ReadTest _app;
bool Run() {
	return _app.execute();
}

