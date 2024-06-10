#include "../SSDShellLibrary/ssdExecutor.h"
#include "../SSDShellLibrary/TestShell.h"
#include "ReadTest.h"

#ifdef _DEBUG
#pragma comment (lib, "../x64/Debug/SSDShellLibrary.lib")
#else
#pragma comment (lib, "../x64/Release/SSDShellLibrary.lib")
#endif // _DEBUG

void ReadTest::execute() {
	ssdExecutor ssdExe;
	SddDataReader datareader;
	TestShell shell{ &ssdExe, &datareader };

	std::cout << "DLL started" << std::endl;

	shell.TestExecute("read 3 ");
};

ReadTest _app;
void Run() {
	_app.execute();
}

