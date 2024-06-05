#include <iostream>
#include "ssdTestShell.cpp"
#include "ssdExecutor.cpp"

int main()
{
    ssdExecutor ssdExe;
    SddDataReader datareader;
    TestShell shell{ &ssdExe, &datareader };

    while (1) {
        char userInput[100];
        std::cin.getline(userInput, 100);
        if (string(userInput) == "")
            continue;
        if (shell.TestExecute(userInput) == true) {
            break;
        }
    }
    return 0;
}
