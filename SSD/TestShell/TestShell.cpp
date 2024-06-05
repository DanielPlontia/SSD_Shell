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
        try {
            if (shell.TestExecute(userInput) == true) {
                break;
            }
        }
        catch(exception &e){
            std::cout << e.what() << std::endl;
            continue;
        }
    }
    return 0;
}
