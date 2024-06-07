#pragma once
#include <string>
#include <vector>
#include <ranges>
#include <fstream>
#include <chrono>
#include <ctime>
#include "SharedMutex.h"

class LogFileManager {
public:
	bool WriteFile(const std::string& msg);
private:
	const std::filesystem::path log_file = "c:\\log\\lastest.log";
	bool backup_file();
	bool zip_file();

	std::vector<std::filesystem::path> existFileList;
	void find_log_files(const std::filesystem::path& directory);
};