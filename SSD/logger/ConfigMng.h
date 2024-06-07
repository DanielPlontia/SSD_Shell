#pragma once

#include <string>
#include <vector>
#include <ranges>
#include <fstream>
#include <chrono>
#include <ctime>
#include <mutex>
#include <filesystem>

class ConfigMng {
public:
	ConfigMng();
	void set_console_print_opt(bool dis_enable);
	bool is_enable_console_print_opt();
private:
	std::filesystem::path config_file;
};