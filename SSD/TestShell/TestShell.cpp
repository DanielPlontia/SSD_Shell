#include <iostream>
#include "ssdTestShell.cpp"
#include "ssdExecutor.cpp"
#include "TestShell.h"

int main(int argc, char* argv[])
{
    ssdExecutor ssdExe;
    SddDataReader datareader;
    TestShell shell{ &ssdExe, &datareader };

    if (isRunnerMode(argc)) {
        return RunnerMode(argv, shell);
    }

    while (1) {
        char userInput[100];
        std::cin.getline(userInput, 100);
        if (string(userInput) == "")
            continue;

        try {
            if (shell.TestExecute(userInput) == true) {
                break;
            }
        }
        catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}

int RunnerMode(char* argv[], TestShell& shell)
{
    ifstream fin;
    fin.open(argv[1]);

    string line;
    while (!fin.eof())
    {
        getline(fin, line);

        vector<string> testScenario = split_test_scenario(line);

        if (is_valid_check_of_scenario_list(testScenario) == false) return 0;

        try {
            cout << line << " ... ";
            shell.TestExecute(line);
            cout << "Pass" << endl;
        }
        catch (std::exception& e) {
            cout << "FAIL!!" << endl;
            break;
        }
    }
    return 0;
}

std::vector<std::string> split_test_scenario(std::string& line)
{
    vector<string> testScenario;
    istringstream ss(line);
    string subs1;

    while (getline(ss, subs1, ' ')) {
        testScenario.push_back(subs1);
    }
    return testScenario;
}

bool isRunnerMode(int argc)
{
    return argc == 2;
}

bool is_valid_check_of_scenario_list(std::vector<std::string>& testScenario)
{
    if (testScenario.empty()) {
        cout << "please check scenario list file\n";
        return false;
    }
    if (testScenario.size() > 1) {
        cout << "please check Scenario CMD : " << testScenario[0] << endl;
        return false;
    }

    // TestShell 내부 CMD 수행 불가
	std::string cmd[] = {"fullread", "fullwrite", "read", "write", "erase", "flush", "help", "exit"};
	if (std::find(std::begin(cmd), std::end(cmd), testScenario[0]) != std::end(cmd)) return false;
	return true;
}
