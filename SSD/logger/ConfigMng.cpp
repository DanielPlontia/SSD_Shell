#include "ConfigMng.h"

ConfigMng::ConfigMng() : config_file{"c:\\log\\config.txt"}
{
}

void ConfigMng::set_console_print_opt(bool dis_enable)
{
    make_log_directory();
    std::string console_opt = dis_enable ? "enable" : "disable";
    std::ofstream file(config_file, std::ios::trunc);
    if (file.is_open()) {
        file.write(console_opt.c_str(), console_opt.length());
        file.close();
    }
}

bool ConfigMng::is_enable_console_print_opt()
{
    std::ifstream config(config_file);
    if (config.is_open()) {
        std::string console_opt;
        if (std::getline(config, console_opt)) {
            config.close();
            if (console_opt == "disable") return false;
        }
    } 
    config.close();
    return true;
}

void ConfigMng::make_log_directory()
{
    if (std::filesystem::exists(config_file))
        return;

    std::filesystem::create_directory(config_file.parent_path());
}
