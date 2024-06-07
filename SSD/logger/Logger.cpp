#include "Logger.h"

void WriteLog(const std::string& funcName, const std::string& msg) {
    Logger::getInstance().writelog(funcName, msg);
}

void Logger::writelog(const std::string& funcName, const std::string& msg) {
    std::string formated_str = LogFormatter::get_log_formatted(funcName, msg);
    file_mng.WriteFile(formated_str);
    std::cout << msg << std::endl;
}
