#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "TestShell.h"
#include "include_logger.h"

ShellAPI::ShellAPI(exeRunner* exe, dataReader* reader) : myExecuter{ exe }, fileReader{ reader } {
    make_test_func_map();
}

bool ShellAPI::TestExecute(std::string inputData) {
    split_input_data(inputData);
    if (readedData[0] == "exit") return true;

    if (IsShellAPI(readedData[0]) == false) {
        throw std::runtime_error("Invalid Command");
    }
    test_func_map[readedData[0]].function();
    return false;
}

bool ShellAPI::IsShellAPI(const std::string& cmd)
{
    if (test_func_map.find(cmd) == test_func_map.end()) {
        return false;
    }
    return true;
}

void ShellAPI::read() {
    check_user_input_count(2);
    std::string cmd = "R " + readedData[1];
    run_executer(cmd);
    WRITE_LOG(fileReader->fileRead());
}

void ShellAPI::write() {
    check_user_input_count(3);
    std::string cmd = "W " + readedData[1] + " " + readedData[2];
    run_executer(cmd);
}

void ShellAPI::erase() {
    check_user_input_count(3);

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
            run_executer(cmd);
            startLba = stoi(readedData[1]);
            startLba += 10;
            readedData[1] = std::to_string(startLba);
        }
        else {
            cmd = "E " + readedData[1] + " " + std::to_string(size);
            run_executer(cmd);
            break;
        }
    }
}


void ShellAPI::erase_range() {
    check_user_input_count(3);
    int startLba = stoi(readedData[1]);
    int endLba = stoi(readedData[2]);

    readedData[0] = "erase";
    readedData[1] = std::to_string(startLba);
    readedData[2] = std::to_string(endLba - startLba);

    erase();
}

void ShellAPI::flush() {
    check_user_input_count(1);
    std::string cmd = "F";
    run_executer(cmd);
}

void ShellAPI::fullRead() {
    check_user_input_count(1);
    for (int index = MIN_LBA; index <= MAX_LBA; ++index) {
        std::string cmd = "R " + std::to_string(index);
        run_executer(cmd);
        WRITE_LOG(fileReader->fileRead());
    }
}

void ShellAPI::fullWrite() {
    check_user_input_count(2);
    for (int index = MIN_LBA; index <= MAX_LBA; ++index) {
        std::string cmd = "W " + std::to_string(index) + " " + readedData[1];
        run_executer(cmd);
    }
}

void ShellAPI::showHelp() {
    for (const auto& tf : test_func_map) {
        std::cout << tf.first << " : " << tf.second.description << std::endl;
    }
}

void ShellAPI::split_input_data(std::string input) {
    std::istringstream ss(input);
    std::string subs;
    readedData.clear();
    while (std::getline(ss, subs, ' ')) {
        readedData.push_back(subs);
    }
}

void ShellAPI::check_user_input_count(int count) {
    if (readedData.size() != count) throw std::invalid_argument("Invalid Parameters.");
}

void ShellAPI::erase_validation_check(int size, int startLba)
{
    if (size > MAX_ERASE_SIZE || size < MIN_ERASE_SIZE) throw std::invalid_argument("Size 값을 다시 입력해주세요");
    if (startLba + size > MAX_ERASE_SIZE || startLba + size < MIN_ERASE_SIZE) throw std::invalid_argument("Size 값을 다시 입력해주세요");
}

void ShellAPI::make_test_func_map() {
    test_func_map.emplace("read", test_func{ std::bind(&ShellAPI::read, this), "SSD에 특정 메모리 값을 읽어 Console에 출력해줍니다.\n사용법 : read [주소]\n" });
    test_func_map.emplace("write", test_func{ std::bind(&ShellAPI::write, this), "SSD 특정 메모리에 값을 적습니다. Data는 0x로 시작하는 4byte Hex string으로 작성해주셔야 합니다.\n사용법 : write [주소] [Data]\n" });
    test_func_map.emplace("erase", test_func{ std::bind(&ShellAPI::erase, this), "SSD 특정 메모리에 값을 지웁니다.\n사용법 : erase [주소] [Size]\n" });
    test_func_map.emplace("erase_range", test_func{ std::bind(&ShellAPI::erase_range, this), "SSD 설정된 영역의 메모리에 값을 지웁니다.\n사용법 : erase_range [시작주소] [끝주소]\n" });
    test_func_map.emplace("flush", test_func{ std::bind(&ShellAPI::flush, this), "SSD의 모든 CMD를 NAND에 반영합니다.\n사용법 : flush\n" });
    test_func_map.emplace("fullread", test_func{ std::bind(&ShellAPI::fullRead, this), "SSD 모든 메모리 값을 읽어 Console에 출력해줍니다.\n사용법 : fullread\n" });
    test_func_map.emplace("fullwrite", test_func{ std::bind(&ShellAPI::fullWrite, this), "SSD 모든 메모리에 값을 적습니다. Data는 0x로 시작하는 4byte Hex string으로 작성해주셔야 합니다.\n사용법 : fullwrite [Data]\n" });
    test_func_map.emplace("help", test_func{ std::bind(&ShellAPI::showHelp, this), "TestShell에서 사용할 수 있는 Command들에 대한 설명을 확인 할 수 있습니다.\n" });
    test_func_map.emplace("exit", test_func{ nullptr, "실행중인 TestShell을 종료합니다.\n사용법 : exit\n" });
}

void ShellAPI::run_executer(std::string& cmd)
{
    if (!myExecuter->runner(cmd)) {
        std::string err_msg = cmd + " command execute fail";
        throw std::exception{ err_msg.c_str() };
    }
}