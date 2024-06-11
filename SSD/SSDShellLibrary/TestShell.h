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

class ShellAPI {
public:
    ShellAPI(exeRunner* exe, dataReader* reader);
    bool TestExecute(std::string inputData);

private:
    std::unordered_map<std::string, test_func> test_func_map;
    std::vector<std::string> readedData;
    exeRunner* myExecuter;
    dataReader* fileReader;

    const int TEST_APP2_REPEAT_COUNT = 30;
    const int MIN_LBA = 0;
    const int MAX_LBA = 99;
    const int MIN_ERASE_SIZE = 1;
    const int MAX_ERASE_SIZE = 100;

    void read();
    void write();
    void erase();
    void erase_range();
    void flush();
    void fullRead();
    void fullWrite();
    void showHelp();

    void split_input_data(std::string input);
    void check_user_input_count(int count);
    void erase_validation_check(int size, int startLba);
    void make_test_func_map();
    void run_executer(std::string& cmd);
};
