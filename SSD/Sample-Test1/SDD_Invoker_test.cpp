#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/SSD_Invoker.cpp"
#include "../SSD/SSD_HW.h"
#include "../SSD/Command.h"
#include "SSD_HW_Mock.h"
#include<vector>

using namespace std;
using namespace testing;



TEST(InvokeTest, CMDFailInvoke) {

	vector<string> userCmd = { "A","2","0xAAAABBBB" };
	SSD_Invoker inv(userCmd);
	string errorCheck = inv.run();

	EXPECT_EQ(errorCheck, "");
}

TEST(InvokeTest, WriteCMDFailInvoke) {

	vector<string> userCmd = { "W","101","0xAABBBB" };
	SSD_Invoker inv(userCmd);
	string errorCheck = inv.run();
	EXPECT_EQ(errorCheck, "cmd validation check Throw something");
}



TEST(InvokeTest, writeInvoke) {

	vector<string> userCmd = { "W","2","0x1234ABCD" };
	SSD_Invoker inv(userCmd);
	string errorCheck = inv.run();
	EXPECT_EQ(errorCheck, "write_instance");
}

TEST(InvokeTest, readInvoke) {

	vector<string> userCmd = { "R","2" };
	SSD_Invoker inv(userCmd);
	string errorCheck = inv.run();
	EXPECT_EQ(errorCheck, "read_instance");
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

