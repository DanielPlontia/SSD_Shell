#pragma once

#include <vector>
#include <string>
#include "TestShell.h"
#include "TestScenario.h"

class TestMode {
public:
    TestMode(int argc, char* argv[], ShellAPI& shell);
    int run();

private:
    int argc;
    char** argv;
    ShellAPI& shell;
    TestScenario* scenarioExcutor;

    int runnerMode();
    int interactiveMode();
    bool isRunnerMode();
    bool IsScenarioCommand(const std::vector<std::string>& testScenario);
    bool IsValidScenarioCommand_size(const std::vector<std::string>& testScenario);
    std::vector<std::string> splitTestScenario(const std::string& line);
};
