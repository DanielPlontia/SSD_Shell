#pragma once

#include <string>
#include <iostream>
#include "LogFileManager.h"
#include "LogFormatter.h"
#include "ConfigMng.h"

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
	ConfigMng& getConfigMng();
private:
	LogFileManager file_mng;
	ConfigMng cfg_mng;

	Logger() = default;
	Logger(const Logger& other) = delete;
	Logger& operator=(const Logger& other) = delete;
};

extern "C" {
	LOGGER_DECLSPEC void WriteLog(const std::string& funcName, const std::string& msg);
	LOGGER_DECLSPEC void DisableConsole();
	LOGGER_DECLSPEC void EnableConsole();
}