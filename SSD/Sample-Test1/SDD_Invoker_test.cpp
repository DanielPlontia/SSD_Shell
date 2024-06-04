#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/SSD_Invoker.cpp"
#include "../SSD/SSD_HW.h"
#include "../SSD/Command.h"
#include "SSD_HW_Mock.h"
#include<vector>

using namespace std;
using namespace testing;

class writeCmdFixtrue : public testing::Test {
public:
	vector<string> userCmd = { "W", "2", "0xAAAABBBB" };
};


TEST_F(writeCmdFixtrue, writeInvoke) {

	SSD_Invoker inv(userCmd);
	inv.run();
}

//TEST_F(writeCmdFixtrue, readInvoke) {
//	SSD_HW_Mock ssdMock;
//	CMD_Read_Mock readCmdMock{ &ssdMock };
//
//	EXPECT_CALL(readCmdMock, execute).Times(1);
//
//	SSD_Invoker inv(userCmd);
//	inv.run();
//}

