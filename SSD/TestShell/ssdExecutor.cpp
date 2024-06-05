#include <cstdlib>
#include <iostream>
#include <filesystem>
#include "exeRunner.h"

namespace fs = std::filesystem;

class ssdExecutor : public exeRunner {
public:
	bool runner(std::string cmd) override {
		if(check_precondition(cmd) == false) return false;

		std::string exe_run_cmd = SSD_exe_path.string() + " " + cmd;
		int exit_status = system(exe_run_cmd.c_str());
		if (exit_status != 0) {
			std::cerr << "SSD.exe not success return. return value : " << exit_status << std::endl;
			return false;
		}
		return true;
	}

private:
	fs::path SSD_exe_path = "SSD.exe";

	bool check_precondition(std::string& cmd)
	{
		if (cmd.empty()) {
			std::cerr << "SSD.exe Call Command Empty" << std::endl;
			return false;
		}

		if (fs::exists(SSD_exe_path) == false) {
			std::cerr << "SSD.exe Not Exist in same path TestShell.exe" << std::endl;
			return false;
		}
		return true;
	}
};
