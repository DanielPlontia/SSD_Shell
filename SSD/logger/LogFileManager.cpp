#include "LogFileManager.h"
#include "SharedMutex.h"

LogFileManager::LogFileManager() : log_file{ "c:\\log\\lastest.log" }
{
    fileMutex = std::make_shared<SharedMutex>("loggerMTX");
}

void LogFileManager::WriteFile(const std::string& msg)
{
    std::lock_guard<SharedMutex> lock(*fileMutex.get());
    make_log_directory();
    manage_file_size();
    write_file(msg);
}

void LogFileManager::write_file(const std::string& msg)
{
    std::ofstream file(log_file, std::ios::app);
    if (file.is_open()) {
        file.write(msg.c_str(), msg.length());
        file.close();
    }
}

void LogFileManager::make_log_directory()
{
    if (std::filesystem::exists(log_file))
        return;

    std::filesystem::create_directory(log_file.parent_path());
}

void LogFileManager::manage_file_size()
{
    if (std::filesystem::file_size(log_file) <= MAX_LOG_SIZE)
        return;

    zip_file();
    backup_file();
}

void LogFileManager::backup_file()
{
    char newFileName[100];
    std::tm cur_time = get_cur_time();
    std::strftime(newFileName, sizeof(newFileName), "until_%y%m%d_%Hh_%Mm_%Ss.log", &cur_time);
    std::filesystem::path renamed_fullpath = log_file.parent_path() / std::string(newFileName);
    std::filesystem::rename(log_file, renamed_fullpath);
	return;
}

void LogFileManager::zip_file()
{
    auto existFileList = find_log_files(log_file.parent_path());    
    if (existFileList.size() < 2) return;

    for (auto& file_name : existFileList)
    {
        if (file_name == log_file)
            continue;

        std::filesystem::path oldPath = file_name;
        std::filesystem::rename(oldPath, file_name.replace_extension(".zip"));
    }
    return;
}

std::vector<std::filesystem::path> LogFileManager::find_log_files(const std::filesystem::path& directory)
{
    std::vector<std::filesystem::path> existFileList;
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_directory()) continue;
        
        if (entry.path().has_extension() && entry.path().extension() == ".log") {
            existFileList.push_back(entry.path());
        }
    }
    return existFileList;
}

std::tm LogFileManager::get_cur_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime;
    localtime_s(&localTime, &currentTime);
    return localTime;
}
