#pragma once

bool isRunnerMode(int argc);
int RunnerMode(char* argv[], TestShell& shell);
std::vector<std::string> split_test_scenario(std::string& line);
bool is_valid_check_of_scenario_list(std::vector<std::string>& testScenario);
