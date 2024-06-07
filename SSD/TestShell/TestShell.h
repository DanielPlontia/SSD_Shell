#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include "exeRunner.h"
#include "DataReader.h"

struct test_func {
    test_func() = default;
    test_func(std::function<void()> _func, const char* _desc) : function{ _func }, description{ _desc } {}
    std::function<void()> function;
    std::string description;
};

class TestShell {
public:
    TestShell(exeRunner* exe, dataReader* reader);
    bool TestExecute(std::string inputData);

private:
    std::unordered_map<std::string, test_func> test_func_map;
    std::vector<std::string> readedData;
    exeRunner* myExecuter;
    dataReader* fileReader;

    const int TEST_APP2_REPEAT_COUNT = 30;

    void split_input_data(std::string input);
    void check_validation_user_input(int count);
    void repeatReadOperation(int start, int end);
    void repeatWriteOperation(int start, int end, std::string data);
    void make_test_func_map();

    void read();
    void write();
    void fullRead();
    void fullWrite();
    void showHelp();
    void testApp1();
    void testApp2();
};
