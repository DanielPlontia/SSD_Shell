#include "Logger.h"

void WriteLog(const std::string& funcName, const std::source_location& loc, const std::string& msg, bool console_print) {
    Logger::getInstance().writelog(funcName, loc, msg, console_print);
}

void DisableConsole() {
    Logger::getInstance().getConfigMng().set_console_print_opt(false);
}

void EnableConsole() {
    Logger::getInstance().getConfigMng().set_console_print_opt(true);
}

void Logger::writelog(const std::string& funcName, const std::source_location& loc, const std::string& msg, bool console_print) {
    std::string formated_str = LogFormatter::get_log_formatted(funcName, msg, loc);
    file_mng.WriteFile(formated_str);

    if (cfg_mng.is_enable_console_print_opt() == false || console_print == false) return;
    std::cout << msg << std::endl;
}

ConfigMng& Logger::getConfigMng()
{
    return cfg_mng;
}
