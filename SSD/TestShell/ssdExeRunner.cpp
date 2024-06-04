#include <cstdlib>
#include <iostream>

#include "exeRunner.h"

class ssdExeRunner : public exeRunner {
public:
	void runner(std::string cmd) {
		// exe calling  byr cmd
		std::string exe_run_cmd = "SSD.exe " + cmd;
		int exit_status = system(exe_run_cmd.c_str());
		if (exit_status != 0) {
			std::cerr << "SSD.exe not success return. return value : " << exit_status << std::endl;
		}
	}
};
