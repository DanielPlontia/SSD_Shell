#include<vector>
#include<string>
#include<algorithm>
#include <cctype>
#include "Command.h"
#include "read.cpp"
#include "write.cpp"

using std::vector;
using std::string;



class SSD_Invoker {
private:
	vector<string> userCmd;
	Command* commandInstance;

	void makeLower(string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}

	Command* getCmdInstance()
	{
		string cmdName = userCmd[0];
		
		makeLower(cmdName);

		if (cmdName == "r") return new Read();
		if(cmdName == "w") return new WriteCmd();


	}

public:
	SSD_Invoker(vector<string> userCommand)
	{
		userCmd = userCommand;
	}

	void run()
	{
		commandInstance->execute(userCmd);
	}
};