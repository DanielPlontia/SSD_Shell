#pragma once

#include <vector>
#include <string>
#include "TestShell.h"
#include "TestScenario.h"

class TestMode {
public:
    TestMode(int argc, char* argv[], TestShell& shell);
    int run();

private:
    int argc;
    char** argv;
    TestShell& shell;
    TestScenario* scenarioExcutor;

    bool isRunnerMode();
    int runnerMode();
    void interactiveMode();
    std::vector<std::string> splitTestScenario(const std::string& line);
    bool IsScenarioCommand(const std::vector<std::string>& testScenario);
    bool IsValidScenarioCommand_size(const std::vector<std::string>& testScenario);
};
