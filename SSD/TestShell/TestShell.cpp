// TestShell.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "ssdTestShell.cpp"
#include "ssdExeRunner.cpp"

int main()
{
    ssdExeRunner ssdExe;
    TestShell* shell = nullptr;

    while (1) {
        char userInput[100];
        std::cout << "Insert command " << std::endl;
        std::cin.getline(userInput, 100);
        shell = new TestShell(&ssdExe, userInput);
        break; // 현재 exit 코드가 없어 임의로 break 추가 됨. exit 코드 추가 시 삭제 요망
    }
}
