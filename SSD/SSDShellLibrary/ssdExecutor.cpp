#include <cstdlib>
#include "ssdExecutor.h"
#include "include_logger.h"

bool ssdExecutor::runner(std::string cmd) {
    if (!check_precondition(cmd)) return false;
	if (!execute_exe(cmd)) return false;
	return true;
}

bool ssdExecutor::execute_exe(std::string& cmd)
{
	std::string exe_run_cmd = SSD_exe_path.string() + " " + cmd;
	int exit_status = system(exe_run_cmd.c_str());
	if (exit_status != 0) {
		WRITE_LOG("SSD.exe not success return. return value : " + std::to_string(exit_status));
		return false;
	}
	return true;
}

bool ssdExecutor::check_precondition(std::string& cmd) {
    if (cmd.empty()) {
		WRITE_LOG("SSD.exe Call Command Empty");
        return false;
    }

    if (!fs::exists(SSD_exe_path)) {
		WRITE_LOG("SSD.exe Not Exist in same path as TestShell.exe");
		return false;
    }
    return true;
}
