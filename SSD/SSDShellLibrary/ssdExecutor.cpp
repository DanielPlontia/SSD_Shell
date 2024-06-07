#include "ssdExecutor.h"
#include <cstdlib>

bool ssdExecutor::runner(std::string cmd) {
    if (!check_precondition(cmd)) return false;
	if (check_precondition(cmd) == false) return false;
	if (execute_exe(cmd) == false) return false;
	return true;
}

bool ssdExecutor::execute_exe(std::string& cmd)
{
	std::string exe_run_cmd = SSD_exe_path.string() + " " + cmd;
	int exit_status = system(exe_run_cmd.c_str());
	if (exit_status != 0) {
		std::cerr << "SSD.exe not success return. return value : " << exit_status << std::endl;
		return false;
	}
	return true;
}

bool ssdExecutor::check_precondition(std::string& cmd) {
    if (cmd.empty()) {
        std::cerr << "SSD.exe Call Command Empty" << std::endl;
        return false;
    }

    if (!fs::exists(SSD_exe_path)) {
        std::cerr << "SSD.exe Not Exist in same path as TestShell.exe" << std::endl;
        return false;
    }
    return true;
}
