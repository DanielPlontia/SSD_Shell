#include "Logger.h"

void Logger::writelog(const std::string& funcName, const std::string& msg) {

    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // localtime�� ����Ͽ� tm ����ü�� �ð� ��ȯ
    struct std::tm localTime;
    localtime_s(&localTime, &currentTime);

    // �ð� ������ �����Ͽ� ���
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "[%y.%m.%d %H:%M]", &localTime);

    std::string formated_str = std::format("{} {:30}: {}", buffer, funcName.c_str(), msg.c_str());

    std::cout << formated_str << std::endl;
}

Logger _log;
void WriteLog(const std::string& funcName, const std::string& msg) {
    _log.writelog(funcName, msg);
}