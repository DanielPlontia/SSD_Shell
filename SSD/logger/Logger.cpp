#include "Logger.h"

Logger _log;
void WriteLog(const std::string& funcName, const std::string& msg) {
    _log.writelog(funcName, msg);
}

Logger::Logger()
{
    fileMutex = std::make_shared<SharedMutex>("loggerMTX");
}

void Logger::writelog(const std::string& funcName, const std::string& msg) {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // localtime을 사용하여 tm 구조체로 시간 변환
    struct std::tm localTime;
    localtime_s(&localTime, &currentTime);

    // 시간 형식을 변경하여 출력
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "[%y.%m.%d %H:%M]", &localTime);

    std::string formated_str = std::format("{} {:30}: {}\n", buffer, split(funcName, "::").c_str(), msg.c_str());

    std::lock_guard<SharedMutex> lock(*fileMutex.get());

    if (!std::filesystem::exists(log_file)) {
        std::filesystem::create_directory(log_file.parent_path());
    }
    else if (std::filesystem::file_size(log_file) > 10 * 1024) //10kb 넘을떄
    {
        char newFileName[100];
        std::strftime(newFileName, sizeof(newFileName), "until_%y%m%d_%Hh_%Mm_%Ss.log", &localTime);
        std::filesystem::path newfile_fullname = log_file.parent_path() / std::string(newFileName);

        existFileList.clear();
        findLogFiles(log_file.parent_path());
        if (existFileList.size() >= 2)
        {
            for (auto now : existFileList )
            {
                if (now == log_file)
                    continue;

                std::filesystem::path oldPath = now;
                std::filesystem::rename(oldPath, now.replace_extension(".zip"));
            }
        }

        std::filesystem::rename(log_file, newfile_fullname);
    }

    std::ofstream file(log_file, std::ios::app);
    if (file.is_open()) {
        std::cout << msg << std::endl;
        file.write(formated_str.c_str(), formated_str.length());
        file.close();
    }
}

std::string Logger::split(std::string_view str, std::string_view delim) {
    auto view{ str
    | std::ranges::views::split(delim)
    | std::ranges::views::transform([](auto&& elem) {
            return std::string_view(&*elem.begin(), std::ranges::distance(elem));
    }) };

    std::vector<std::string> strings{ view.begin(), view.end() };
    return strings[1] + "()";
}

void Logger::findLogFiles(const std::filesystem::path& directory) {
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (!entry.is_directory()) {
            if (entry.path().has_extension() && entry.path().extension() == ".log") {
                existFileList.push_back(entry.path());
            }
        }
    }
}
