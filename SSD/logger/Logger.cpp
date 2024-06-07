#include "Logger.h"

void WriteLog(const std::string& funcName, const std::string& msg) {
    Logger::getInstance().writelog(funcName, msg);
}

void Logger::writelog(const std::string& funcName, const std::string& msg) {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // localtime을 사용하여 tm 구조체로 시간 변환
    struct std::tm localTime;
    localtime_s(&localTime, &currentTime);

    // 시간 형식을 변경하여 출력
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "[%y.%m.%d %H:%M]", &localTime);

    std::string formated_str = std::format("{} {:30}: {}\n", buffer, split(funcName, "::").c_str(), msg.c_str());

    file_mng.WriteFile(formated_str);
    std::cout << msg << std::endl;
}

std::string Logger::split(std::string_view str, std::string_view delim) {
    auto view{ str
    | std::ranges::views::split(delim)
    | std::ranges::views::transform([](auto&& elem) {
            return std::string_view(&*elem.begin(), std::ranges::distance(elem));
    }) };

    std::vector<std::string> strings{ view.begin(), view.end() };
    return strings[1] + "()";
}
