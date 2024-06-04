#include<vector>
#include<string>
#include "Command.h"

using std::vector;
using std::string;



class SSD_Invoker {
private:
	vector<string> userCmd;
	Command* commandInstance;




public:
	SSD_Invoker(vector<string> userCommand)
	{
		userCmd = userCommand;
	}

	void run()
	{

	}
};