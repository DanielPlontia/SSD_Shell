#include <iostream>
#include "ssdTestShell.cpp"
#include "ssdExecutor.cpp"

bool is_valid_check_of_scenario_list(std::vector<std::string>& testScenario)
{
    if (testScenario.empty())
    {
        cout << "please check scenario list file\n";
        return false;
    }
    if (testScenario.size() > 1) {
        cout << "please check Scenario CMD : " << testScenario[0] << endl;
        return false;
    }

    // TestShell 내부 CMD 수행 불가
    if (testScenario[0] == "fullread") return false;
    if (testScenario[0] == "fullwrite") return false;
    if (testScenario[0] == "read") return false;
    if (testScenario[0] == "write") return false;
    if (testScenario[0] == "erase") return false;
    if (testScenario[0] == "flush") return false;
    if (testScenario[0] == "help") return false;
    if (testScenario[0] == "exit") return false;
    return true;
}

int main(int argc, char* argv[])
{
    ssdExecutor ssdExe;
    SddDataReader datareader;
    TestShell shell{ &ssdExe, &datareader };

    if (argc == 2) {
		ifstream fin;
		fin.open(argv[1]);

		string line;
		while (!fin.eof())
		{
			getline(fin, line);

			istringstream ss(line);
			string subs1;
            vector<string> testScenario;

			while (getline(ss, subs1, ' ')) {
				testScenario.push_back(subs1);
			}

            if(is_valid_check_of_scenario_list(testScenario) == false) return 0;

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
