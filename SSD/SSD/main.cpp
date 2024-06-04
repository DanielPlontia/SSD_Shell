#include "SSD_HW.h"
#include "Command.h"
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;
int main(int argc, char *argv[]) {
	vector<string> command;
	for (int i = 0; i < argc; i++) {
		command.push_back(argv[i]);
	}
	if (argc > 4) throw std::invalid_argument("Too Much Argument");
	if (command[1] != "R" || command[1] != "W") throw std::invalid_argument("Invalid Operation");
	Invoker invoker{ command };
}