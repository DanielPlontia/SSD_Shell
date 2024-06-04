// TestShell.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "ssdTestShell.cpp"

int main()
{
    sddExeRunner ssdExe;
    TestShell* shell = new TestShell(&ssdExe);

    while (1) {
        char userInput[100];
        std::cin.getline(userInput, 100);
        break;
    }
    std::cout << "Hello World!\n";
}
