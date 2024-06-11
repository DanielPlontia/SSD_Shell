#include "../SSDShellLibrary/ssdExecutor.h"
#include "../SSDShellLibrary/TestShell.h"
#include "StressTest.h"

#ifdef _DEBUG
#pragma comment (lib, "../x64/Debug/SSDShellLibrary.lib")
#else
#pragma comment (lib, "../x64/Release/SSDShellLibrary.lib")
#endif // _DEBUG

void StressTest::execute() {
    int startLba = 0;
    int endLba = 5;
    int count = 0;
    while (count < 30) {
        repeatWriteOperation(startLba, endLba, "0xAAAABBBB");
        count++;
    }
    repeatWriteOperation(startLba, endLba, "0x12345678");
    repeatReadOperation(startLba, endLba);
};

void StressTest::repeatReadOperation(int start, int end) {
    ssdExecutor ssdExe;
    SddDataReader datareader;
    ShellAPI shell{ &ssdExe, &datareader };

    for (int lba = start; lba <= end; lba++) {
        std::string testCpmmand = "read " + std::to_string(lba);
        shell.TestExecute(testCpmmand);
    }
}

void StressTest::repeatWriteOperation(int start, int end, std::string data) {
    ssdExecutor ssdExe;
    SddDataReader datareader;
    ShellAPI shell{ &ssdExe, &datareader };

    for (int lba = start; lba <= end; lba++) {
        std::string testCpmmand = "write " + std::to_string(lba) + " " + data;
        shell.TestExecute(testCpmmand);
    }
}

StressTest _app;
void Run() {
	_app.execute();
}

