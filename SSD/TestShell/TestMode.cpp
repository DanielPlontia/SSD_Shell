#include "TestMode.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "TestScenarioFactory.h"

TestMode::TestMode(int argc, char* argv[], TestShell& shell)
    : argc(argc), argv(argv), shell(shell) {}

int TestMode::run() {
    if (isRunnerMode()) {
        return runnerMode();
    }

    interactiveMode();
    return 0;
}

bool TestMode::isRunnerMode() {
    return argc == 2;
}

int TestMode::runnerMode() {
    std::ifstream fin(argv[1]);
    if (!fin) {
        std::cerr << "Failed to open scenario list file\n";
        return -1;
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::vector<std::string> testScenario = splitTestScenario(line);

        if (!isValidScenario(testScenario)) {
            return 0;
        }

        try {
            std::cout << line << " ... ";
            TestScenario testapp;
            testapp.run("TestApp1");
            std::cout << "Pass" << std::endl;
        }
        catch (const std::exception& e) {
            std::cout << "FAIL!!" << std::endl;
            break;
        }
    }
    return 0;
}

void TestMode::interactiveMode() {
    while (true) {
        char userInput[100];
        std::cin.getline(userInput, 100);
        if (std::string(userInput).empty())
            continue;

        try {
            if (shell.TestExecute(userInput)) {
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
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

bool TestMode::isValidScenario(const std::vector<std::string>& testScenario) {
    if (testScenario.empty()) {
        std::cout << "Please check scenario list file\n";
        return false;
    }
    if (testScenario.size() > 1) {
        std::cout << "Please check Scenario CMD: " << testScenario[0] << std::endl;
        return false;
    }

    std::string invalidCmds[] = {"fullread", "fullwrite", "read", "write", "erase", "flush", "help", "exit"};
    if (std::find(std::begin(invalidCmds), std::end(invalidCmds), testScenario[0]) != std::end(invalidCmds)) {
        return false;
    }
    return true;
}