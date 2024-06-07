#include "Logger.h"

void Logger::writelog(const std::string& funcName, const std::string& msg) {
    std::cout << funcName << " : " << msg << std::endl;
}

Logger _log;
void WriteLog(const std::string& funcName, const std::string& msg) {
    _log.writelog(funcName, msg);
}