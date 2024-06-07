#include "TestShell.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

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
        std::cout << fileReader->fileRead() << std::endl;
    }
}

void TestShell::write() {
    check_validation_user_input(3);
    std::string cmd = "W " + readedData[1] + " " + readedData[2];
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
        myExecuter->runner(cmd);
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
    test_func_map.emplace("fullread", test_func{ std::bind(&TestShell::fullRead, this), "SSD 모든 메모리 값을 읽어 Console에 출력해줍니다.\n사용법 : fullread\n" });
    test_func_map.emplace("fullwrite", test_func{ std::bind(&TestShell::fullWrite, this), "SSD 모든 메모리에 값을 적습니다. Data는 0x로 시작하는 4byte Hex string으로 작성해주셔야 합니다.\n사용법 : fullwrite [Data]\n" });
    test_func_map.emplace("help", test_func{ std::bind(&TestShell::showHelp, this), "TestShell에서 사용할 수 있는 Command들에 대한 설명을 확인 할 수 있습니다.\n" });
    test_func_map.emplace("testapp1", test_func{ std::bind(&TestShell::testApp1, this), "SSD 전체 메모리에 0x12345678을 작성하고 전체 메모리를 읽어 정상적으로 작성이 됐는지 확인합니다.\n사용법 : testapp1\n" });
    test_func_map.emplace("testapp2", test_func{ std::bind(&TestShell::testApp2, this), "LBA 0~5에 0xAAAABBBB 30회 Write, 동일 LBA에 0x12345678 Overwrite후 Read하여 정상적으로 작성됐는지 확인합니다\n사용법 : testapp2\n" });
    test_func_map.emplace("exit", test_func{ nullptr, "실행중인 TestShell을 종료합니다.\n사용법 : exit\n" });
}
