#include "LogFormatter.h"

std::string LogFormatter::get_log_formatted(const std::string& funcName, const std::string& msg)
{
	std::string formated_str = std::format("{} {:30}: {}\n", \
			get_formatted_time("[%y.%m.%d %H:%M]").c_str(), \
			get_split_funcName(funcName).c_str(), \
			msg.c_str());
	return formated_str;
}

std::string LogFormatter::get_formatted_time(const std::string& format)
{
    struct std::tm localTime = get_cur_time();

    char formattedTime[20];
    std::strftime(formattedTime, sizeof(formattedTime), format.c_str(), &localTime);

    return formattedTime;
}

std::tm LogFormatter::get_cur_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // localtime을 사용하여 tm 구조체로 시간 변환
    struct std::tm localTime;
    localtime_s(&localTime, &currentTime);

	return localTime;
}

std::string LogFormatter::get_split_funcName(const std::string& funcName, std::string_view delim)
{
    auto view{ funcName
    | std::ranges::views::split(delim)
    | std::ranges::views::transform([](auto&& elem) {
            return std::string_view(&*elem.begin(), std::ranges::distance(elem));
    }) };

    std::vector<std::string> strings{ view.begin(), view.end() };
    return strings[1] + "()";
}
