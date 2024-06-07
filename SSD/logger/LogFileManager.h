#pragma once
#include <string>
#include <vector>
#include <ranges>
#include <fstream>
#include <chrono>
#include <ctime>
#include <mutex>
#include <filesystem>

#define KB 1024
#define MAX_LOG_SIZE 10 * KB

class SharedMutex;
class LogFileManager {
public:
	LogFileManager();
	void WriteFile(const std::string& msg);

private:
	void write_file(const std::string& msg);
	void make_log_directory();
	void manage_file_size();
	void backup_file();
	void zip_file();
	std::vector<std::filesystem::path> find_log_files(const std::filesystem::path& directory);
	std::tm get_cur_time();

	std::shared_ptr<SharedMutex> fileMutex;
	const std::filesystem::path log_file;
};