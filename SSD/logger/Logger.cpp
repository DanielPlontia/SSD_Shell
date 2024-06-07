#include "Logger.h"

void Logger::writelog(const std::string& funcName, const std::string& msg) {

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // localtime을 사용하여 tm 구조체로 시간 변환
    struct std::tm localTime;
    localtime_s(&localTime, &currentTime);

    // 시간 형식을 변경하여 출력
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "[%y.%m.%d %H:%M]", &localTime);

    std::string formated_str = std::format("{} {:30}: {}", buffer, funcName.c_str(), msg.c_str());

    std::cout << formated_str << std::endl;
}

Logger _log;
void WriteLog(const std::string& funcName, const std::string& msg) {
    _log.writelog(funcName, msg);
}