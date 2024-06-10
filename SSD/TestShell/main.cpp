#include <iostream>
#include "ssdExecutor.h"
#include "TestShell.h"
#include "TestMode.h"

int main(int argc, char* argv[])
{
    ssdExecutor ssdExe;
    SddDataReader datareader;
    TestShell shell{ &ssdExe, &datareader };
    TestMode testMode(argc, argv, shell);
    return testMode.run();
}
