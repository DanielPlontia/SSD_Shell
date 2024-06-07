#pragma once

#include <string>
#include <iostream>

#ifdef LOGGER_EXPORTS
#define LOGGER_DECLSPEC __declspec(dllexport)
#else
#define LOGGER_DECLSPEC __declspec(dllimport)
#endif

class Logger {
public:
	void writelog(const std::string& funcName, const std::string& msg);
private:
};

extern "C" {
	LOGGER_DECLSPEC void WriteLog(const std::string& funcName, const std::string& msg);
}