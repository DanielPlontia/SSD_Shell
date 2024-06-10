#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include "exeRunner.h"
#include "DataReader.h"

struct test_func {
    test_func() = default;
    test_func(std::function<bool()> _func, const char* _desc) : function{ _func }, description{ _desc } {}
    std::function<bool()> function;
    std::string description;
};

class TestShell {
public:
    TestShell(exeRunner* exe, dataReader* reader);
    bool TestExecute(std::string inputData);
    std::unordered_map<std::string, test_func> test_func_map;

private:
    std::vector<std::string> readedData;
    exeRunner* myExecuter;
    dataReader* fileReader;

    const int TEST_APP2_REPEAT_COUNT = 30;

    void split_input_data(std::string input);
    void check_validation_user_input(int count);
    void erase_validation_check(int size, int startLba);
    void repeatReadOperation(int start, int end);
    void repeatWriteOperation(int start, int end, std::string data);
    void make_test_func_map();

    bool read();
    bool write();
    bool erase();
    bool erase_range();
    bool flush();
    bool fullRead();
    bool fullWrite();
    bool showHelp();
    bool testApp1();
    bool testApp2();
};
