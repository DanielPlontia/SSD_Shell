#include "Logger.h"

void WriteLog(const std::string& funcName, const std::string& msg) {
    Logger::getInstance().writelog(funcName, msg);
}

void DisableConsole() {
    Logger::getInstance().getConfigMng().set_console_print_opt(false);
}

void EnableConsole() {
    Logger::getInstance().getConfigMng().set_console_print_opt(true);
}

void Logger::writelog(const std::string& funcName, const std::string& msg) {
    std::string formated_str = LogFormatter::get_log_formatted(funcName, msg);
    file_mng.WriteFile(formated_str);

    if (cfg_mng.is_enable_console_print_opt() == false) return;
    std::cout << msg << std::endl;
}

ConfigMng& Logger::getConfigMng()
{
    return cfg_mng;
}
