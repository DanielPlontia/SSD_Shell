#include <iostream>
#include "ssdExecutor.h"
#include "TestShell.h"
#include "TestMode.h"
#include "TestScenarioFactory.h"

int main(int argc, char* argv[])
{
    ssdExecutor ssdExe;
    SddDataReader datareader;
    TestShell shell{ &ssdExe, &datareader };
    //TestMode testMode(argc, argv, shell);
    //return testMode.run();

    TestScenario testapp;
    testapp.run("TestApp1");
}
