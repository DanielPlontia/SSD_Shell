#pragma once

#include <vector>
#include <string>
#include "TestShell.h"

#ifdef DEBUG
#pragma comment (lib, "../x64/Debug/logger.lib")
#else
#pragma comment (lib, "../x64/Release/logger.lib")
#endif // DEBUG


class TestMode {
public:
    TestMode(int argc, char* argv[], TestShell& shell);
    int run();

private:
    int argc;
    char** argv;
    TestShell& shell;

    bool isRunnerMode();
    int runnerMode();
    void interactiveMode();
    std::vector<std::string> splitTestScenario(const std::string& line);
    bool isValidScenario(const std::vector<std::string>& testScenario);
};
