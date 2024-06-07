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

    std::string formated_str = std::format("{} {:30}: {}", buffer, split(funcName, "::").c_str(), msg.c_str());

    std::cout << formated_str << std::endl;

    std::lock_guard<std::mutex> lock(fileMutex);

    if (!std::filesystem::exists(log_file)) {
        std::filesystem::create_directory(log_file.parent_path());
    }

    std::ofstream file(log_file, std::ios::app);
    if (file.is_open()) {
        file.write(formated_str.c_str(), formated_str.length());
        file.close();
    }
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

Logger _log;
void WriteLog(const std::string& funcName, const std::string& msg) {
    _log.writelog(funcName, msg);
}