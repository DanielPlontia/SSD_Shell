#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <format>
#include <vector>
#include <ranges>
#include <fstream>
#include <mutex>
#include <filesystem>

#ifdef LOGGER_EXPORTS
#define LOGGER_DECLSPEC __declspec(dllexport)
#else
#define LOGGER_DECLSPEC __declspec(dllimport)
#endif

class Logger {
public:
	void writelog(const std::string& funcName, const std::string& msg);
private:
    std::string split(std::string_view str, std::string_view delim);
	std::mutex fileMutex;
	const std::filesystem::path log_file = "c:\\log\\lastest.log";
};

extern "C" {
	LOGGER_DECLSPEC void WriteLog(const std::string& funcName, const std::string& msg);
}