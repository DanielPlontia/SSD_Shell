#include<vector>
#include<string>
#include<algorithm>
#include <cctype>
#include "Command.h"
#include "read.cpp"
#include "write.cpp"
#include "SSD_HW.h"

using std::vector;
using std::string;



class SSD_Invoker {
private:
	vector<string> userCmd;
	Command* command_Instance;
	SSD_HW* SSD_Instance;

	void makeLower(string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c) { return std::tolower(c); });
	}

	SSD_HW* getSSD() 
	{

		return nullptr;
	}

	Command* getCmdInstance()
	{
		if (SSD_Instance == nullptr)
			return nullptr;

		string cmdName = userCmd[0];
		
		makeLower(cmdName);

		if (cmdName == "r") return new ReadCmd();
		if(cmdName == "w") return new WriteCmd(SSD_Instance);
		return nullptr;

	}

public:
	SSD_Invoker(vector<string> userCommand)
	{
		userCmd = userCommand;

		SSD_Instance = getSSD();

		command_Instance = getCmdInstance();
	}

	void run()
	{
		if (command_Instance == nullptr)
			return;

		command_Instance->execute(userCmd);
	}
};