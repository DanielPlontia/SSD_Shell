#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "TestShell.h"
#include "include_logger.h"

TestShell::TestShell(exeRunner* exe, dataReader* reader) : myExecuter{ exe }, fileReader{ reader } {
    make_test_func_map();
}

bool TestShell::TestExecute(std::string inputData) {
    split_input_data(inputData);
    if (readedData[0] == "exit") return true;

    if (test_func_map.find(readedData[0]) == test_func_map.end()) {
        throw std::runtime_error("Invalid Command");
    }
    test_func_map[readedData[0]].function();
    return false;
}

void TestShell::read() {
    check_validation_user_input(2);
    std::string cmd = "R " + readedData[1];
    if (myExecuter->runner(cmd)) {
        WRITE_LOG(fileReader->fileRead());
    }
}

void TestShell::write() {
    check_validation_user_input(3);
    std::string cmd = "W " + readedData[1] + " " + readedData[2];
    myExecuter->runner(cmd);
}

void TestShell::erase() {
    check_validation_user_input(3);

    int startLba = stoi(readedData[1]);
    int size = stoi(readedData[2]);
    erase_validation_check(size, startLba);

    std::string cmd;
    while (1) {
        if (size > 10)
        {
            readedData[2] = std::to_string(10);
            cmd = "E " + readedData[1] + " " + readedData[2];
            size -= 10;
            myExecuter->runner(cmd);
            startLba = stoi(readedData[1]);
            startLba += 10;
            readedData[1] = std::to_string(startLba);
        }
        else {
            cmd = "E " + readedData[1] + " " + std::to_string(size);
            myExecuter->runner(cmd);
            break;
        }
    }
}


void TestShell::erase_range() {
    check_validation_user_input(3);
    int startLba = stoi(readedData[1]);
    int endLba = stoi(readedData[2]);

    readedData[0] = "erase";
    readedData[1] = std::to_string(startLba);
    readedData[2] = std::to_string(endLba - startLba);

    erase();
}

void TestShell::flush() {
    check_validation_user_input(1);
    std::string cmd = "F";
    myExecuter->runner(cmd);
}

void TestShell::fullRead() {
    check_validation_user_input(1);
    for (int index = 0; index < 100; ++index) {
        std::string cmd = "R " + std::to_string(index);
        if (!myExecuter->runner(cmd)) return;
        std::cout << fileReader->fileRead() << std::endl;
    }
}

void TestShell::fullWrite() {
    check_validation_user_input(2);
    for (int index = 0; index < 100; ++index) {
        std::string cmd = "W " + std::to_string(index) + " " + readedData[1];
        if (!myExecuter->runner(cmd)) return;
    }
}

void TestShell::showHelp() {
    for (const auto& tf : test_func_map) {
        std::cout << tf.first << " : " << tf.second.description << std::endl;
    }
}

void TestShell::testApp1() {
    check_validation_user_input(1);
    readedData = {"fullwrite", "0x12345678"};
    fullWrite();
    readedData = {"fullread"};
    fullRead();
}

void TestShell::testApp2() {
    check_validation_user_input(1);
    int startLba = 0;
    int endLba = 5;
    int count = 0;
    while (count < TEST_APP2_REPEAT_COUNT) {
        repeatWriteOperation(startLba, endLba, "0xAAAABBBB");
        count++;
    }
    repeatWriteOperation(startLba, endLba, "0x12345678");
    repeatReadOperation(startLba, endLba);
}

void TestShell::split_input_data(std::string input) {
    std::istringstream ss(input);
    std::string subs;
    readedData.clear();
    while (std::getline(ss, subs, ' ')) {
        readedData.push_back(subs);
    }
}

void TestShell::check_validation_user_input(int count) {
    if (readedData.size() != count) throw std::invalid_argument("Invalid Parameters.");
}

void TestShell::erase_validation_check(int size, int startLba)
{
    if (size > 100 || size < 1) throw std::invalid_argument("Size 값을 다시 입력해주세요");
    if (startLba + size > 100 || startLba + size < 1) throw std::invalid_argument("Size 값을 다시 입력해주세요");
}

void TestShell::repeatReadOperation(int start, int end) {
    for (int lba = start; lba <= end; lba++) {
        readedData = {"read", std::to_string(lba)};
        read();
    }
}

void TestShell::repeatWriteOperation(int start, int end, std::string data) {
    for (int lba = start; lba <= end; lba++) {
        readedData = {"write", std::to_string(lba), data};
        write();
    }
}

void TestShell::make_test_func_map() {
    test_func_map.emplace("read", test_func{ std::bind(&TestShell::read, this), "SSD에 특정 메모리 값을 읽어 Console에 출력해줍니다.\n사용법 : read [주소]\n" });
    test_func_map.emplace("write", test_func{ std::bind(&TestShell::write, this), "SSD 특정 메모리에 값을 적습니다. Data는 0x로 시작하는 4byte Hex string으로 작성해주셔야 합니다.\n사용법 : write [주소] [Data]\n" });
    test_func_map.emplace("erase", test_func{ std::bind(&TestShell::erase, this), "SSD 특정 메모리에 값을 지웁니다.\n사용법 : erase [주소] [Size]\n" });
    test_func_map.emplace("erase_range", test_func{ std::bind(&TestShell::erase_range, this), "SSD 설정된 영역의 메모리에 값을 지웁니다.\n사용법 : erase_range [시작주소] [끝주소]\n" });
    test_func_map.emplace("flush", test_func{ std::bind(&TestShell::flush, this), "SSD의 모든 CMD를 NAND에 반영합니다.\n사용법 : flush\n" });
    test_func_map.emplace("fullread", test_func{ std::bind(&TestShell::fullRead, this), "SSD 모든 메모리 값을 읽어 Console에 출력해줍니다.\n사용법 : fullread\n" });
    test_func_map.emplace("fullwrite", test_func{ std::bind(&TestShell::fullWrite, this), "SSD 모든 메모리에 값을 적습니다. Data는 0x로 시작하는 4byte Hex string으로 작성해주셔야 합니다.\n사용법 : fullwrite [Data]\n" });
    test_func_map.emplace("help", test_func{ std::bind(&TestShell::showHelp, this), "TestShell에서 사용할 수 있는 Command들에 대한 설명을 확인 할 수 있습니다.\n" });
    test_func_map.emplace("exit", test_func{ nullptr, "실행중인 TestShell을 종료합니다.\n사용법 : exit\n" });
}
