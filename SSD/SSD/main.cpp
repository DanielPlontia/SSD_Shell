#include "SSD_Invoker.cpp"
#include <vector>
#include <string>

using namespace std;
int main(int argc, char *argv[]) {
	vector<string> command;
	for (int i = 0; i < argc; i++) {
		command.push_back(argv[i]);
	}
	Invoker invoker{ command };
	invoker.run();
}