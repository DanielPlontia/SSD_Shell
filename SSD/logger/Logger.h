#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include <format>
#include <vector>
#include <ranges>

#include "LogFileManager.h"

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
	
	LogFileManager file_mng;
};

extern "C" {
	LOGGER_DECLSPEC void WriteLog(const std::string& funcName, const std::string& msg);
}