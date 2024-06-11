#include "../SSDShellLibrary/ssdExecutor.h"
#include "../SSDShellLibrary/TestShell.h"
#include "FullWriteAndRead.h"

#ifdef _DEBUG
#pragma comment (lib, "../x64/Debug/SSDShellLibrary.lib")
#else
#pragma comment (lib, "../x64/Release/SSDShellLibrary.lib")
#endif // _DEBUG

void FullWirteAndRead::execute() {
	ssdExecutor ssdExe;
	SddDataReader datareader;
	ShellAPI shell{ &ssdExe, &datareader };
	shell.TestExecute("fullwrite 0x12345678 ");
	shell.TestExecute("fullread");
};

FullWirteAndRead _app;
void Run() {
	_app.execute();
}

