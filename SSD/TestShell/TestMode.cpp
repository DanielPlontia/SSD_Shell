#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "TestMode.h"
#include "include_logger.h"

TestMode::TestMode(int argc, char* argv[], ShellAPI& shell)
    : argc(argc), argv(argv), shell(shell) {
    scenarioExcutor = new TestScenario();
}

int TestMode::run() {
    if (isRunnerMode()) return runnerMode();
    return interactiveMode();
}

int TestMode::runnerMode() {
    std::ifstream runner_scenario(argv[1]);
    if (!runner_scenario) {
        WRITE_LOG("Failed to open scenario list file");
        return -1;
    }

    std::string line;
    while (std::getline(runner_scenario, line)) {
        std::vector<std::string> testScenario = splitTestScenario(line);

        if (!IsScenarioCommand(testScenario) || !IsValidScenarioCommand_size(testScenario)) {
            return -2;
        }

        try {
            DisableConsole();
            WRITE_LOG(line + " ... ");
            std::cout << line << " ... ";

            scenarioExcutor->run(testScenario[0]);          
          
            WRITE_LOG(line + " ... Pass");
            std::cout << "Pass" << std::endl;
            EnableConsole();
        }
        catch (const std::exception& e) {
            WRITE_LOG("FAIL!! : " + std::string(e.what()));
            std::cout << "FAIL!!" << std::endl;
            EnableConsole();
            break;
        }
    }
    return 0;
}

int TestMode::interactiveMode() {
    while (true) {
        char userInput[100];
        std::cin.getline(userInput, 100);
        if (std::string(userInput).empty())
            continue;

        std::vector<std::string> testScenario = splitTestScenario(userInput);

        try {
            if (IsScenarioCommand(testScenario)) {
                if(!IsValidScenarioCommand_size(testScenario))
                    throw std::runtime_error("Invalid Command");
                scenarioExcutor->run(testScenario[0]);
            }
            else if (shell.TestExecute(userInput)) {
                break;
            }
        }
        catch (const std::exception& e) {
            WRITE_LOG(e.what());
            continue;
        }
    }
    return 0;
}

bool TestMode::isRunnerMode() {
    return argc == 2;
}

bool TestMode::IsScenarioCommand(const std::vector<std::string>& testScenario) {
    if (testScenario.empty()) {
        WRITE_LOG("Please check scenario list file");
        return false;
    }
    return !shell.IsShellAPI(testScenario[0]);
}

bool TestMode::IsValidScenarioCommand_size(const std::vector<std::string>& testScenario) {
    if (testScenario.size() > 1) {
        WRITE_LOG("Please check Scenario CMD: " + testScenario[0]);
        return false;
    }
    return true;
}
std::vector<std::string> TestMode::splitTestScenario(const std::string& line) {
    std::vector<std::string> testScenario;
    std::istringstream ss(line);
    std::string subs;

    while (ss >> subs) {
        testScenario.push_back(subs);
    }
    return testScenario;
}
