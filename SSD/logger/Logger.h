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
#include "SharedMutex.h"
#include "LogFormatter.h"

#ifdef LOGGER_EXPORTS
#define LOGGER_DECLSPEC __declspec(dllexport)
#else
#define LOGGER_DECLSPEC __declspec(dllimport)
#endif

class Logger {
public:
	Logger();
	void writelog(const std::string& funcName, const std::string& msg);
private:
    std::string split(std::string_view str, std::string_view delim);
	std::shared_ptr<SharedMutex> fileMutex;
	std::vector<std::filesystem::path> existFileList;
	void findLogFiles(const std::filesystem::path & directory);
	const std::filesystem::path log_file = "c:\\log\\lastest.log";
};

extern "C" {
	LOGGER_DECLSPEC void WriteLog(const std::string& funcName, const std::string& msg);
}