#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <format>
#include <ranges>
#include <filesystem>
#include <source_location>
#include <algorithm>

#define MAX_LEN 30

class LogFormatter {
public:
	static std::string get_log_formatted(const std::string& funcName, const std::string& msg, const std::source_location& loc);
	static std::string get_formatted_time(const std::string& format);

private:
	static std::tm get_cur_time();
	static std::string get_split_funcName(const std::string& funcName, std::string_view delim="::");
};