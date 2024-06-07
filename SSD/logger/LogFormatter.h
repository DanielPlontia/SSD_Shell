#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <format>

class LogFormatter {
public:
	std::string get_log_formatted(const std::string& funcName, const std::string& msg);
private:
	std::string get_cur_time();
	std::string get_split_funcNmae(const std::string& funcName);
};