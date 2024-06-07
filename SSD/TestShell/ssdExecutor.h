#pragma once
#include "exeRunner.h"
#include <filesystem>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

class ssdExecutor : public exeRunner {
public:
    bool runner(std::string cmd) override;

private:
    fs::path SSD_exe_path = "SSD.exe";
    bool execute_exe(std::string& cmd);
    bool check_precondition(std::string& cmd);
};
