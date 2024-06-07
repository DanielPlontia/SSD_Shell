#include <iostream>
#include "ssdTestShell.cpp"
#include "ssdExecutor.cpp"

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

            if (testScenario.empty())
            {
                cout << "please check file : " << argv[1] << endl;
                return 0;
            }
            if (testScenario.size() > 1) {
                cout << "please check Scenario CMD : " << testScenario[0] << endl;
                return 0;
            }

            try {
                cout << line << " ... ";
                if (shell.TestExecute(line) == true) {
					cout << "Pass" << endl;
                    break;
                }
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
