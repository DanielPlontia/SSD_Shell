#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include "ssdTestShell.cpp"
#include "ssdExecutor.cpp"

void my_handler(sig_atomic_t s) {
    exit(1);
}
int main()
{
    ssdExecutor ssdExe;
    SddDataReader datareader;
    TestShell shell{ &ssdExe, &datareader };

    signal(SIGINT, my_handler);

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
