#pragma once

#include <vector>
#include <string>
#include "TestShell.h"

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
    bool IsScenarioCommand(const std::vector<std::string>& testScenario);
    bool IsValidScenarioCommand(const std::vector<std::string>& testScenario);
};
