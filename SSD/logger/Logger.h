#pragma once

#include <string>
#include <iostream>
#include <source_location>
#include "LogFileManager.h"
#include "LogFormatter.h"
#include "ConfigMng.h"

#ifdef LOGGER_EXPORTS
#define LOGGER_DECLSPEC __declspec(dllexport)
#else
#define LOGGER_DECLSPEC __declspec(dllimport)
#endif

#define WRITE_LOG_WITHOUT_CONSOLE(msg) WriteLog(__FUNCTION__, std::source_location::current(), msg, false);
#define WRITE_LOG(msg) WriteLog(__FUNCTION__, std::source_location::current(), msg);

class Logger {
public:
	static Logger& getInstance() {
		static Logger instance;
		return instance;
	}

	void writelog(const std::string& funcName, const std::source_location& loc, const std::string& msg, bool console_print = true);
	ConfigMng& getConfigMng();
private:
	LogFileManager file_mng;
	ConfigMng cfg_mng;

	Logger() = default;
	Logger(const Logger& other) = delete;
	Logger& operator=(const Logger& other) = delete;
};

extern "C" {
	LOGGER_DECLSPEC void WriteLog(const std::string& funcName, const std::source_location& loc, const std::string& msg, bool console_print = true);
	LOGGER_DECLSPEC void DisableConsole();
	LOGGER_DECLSPEC void EnableConsole();
}