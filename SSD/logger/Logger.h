#pragma once

#include <string>
#include <iostream>
#include "LogFileManager.h"
#include "LogFormatter.h"

#ifdef LOGGER_EXPORTS
#define LOGGER_DECLSPEC __declspec(dllexport)
#else
#define LOGGER_DECLSPEC __declspec(dllimport)
#endif

class Logger {
public:
	static Logger& getInstance() {
		static Logger instance;
		return instance;
	}

	void writelog(const std::string& funcName, const std::string& msg);
private:
	LogFileManager file_mng;

	Logger() = default;
	Logger(const Logger& other) = delete;
	Logger& operator=(const Logger& other) = delete;
};

extern "C" {
	LOGGER_DECLSPEC void WriteLog(const std::string& funcName, const std::string& msg);
}