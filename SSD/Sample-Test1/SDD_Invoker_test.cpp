#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

#define private public

#include "../SSD/SSD_Invoker.cpp"
#include "../SSD/SSD_HW.h"
#include "../SSD/Command.h"
#include "SSD_HW_Mock.h"

using namespace std;
using namespace testing;

class InvokerFixture : public testing::Test {
public:
	SSD_Invoker inv{std::vector<std::string>()};
	SSD_HW_Mock ssd_mock;
	void SetUp() override {
		inv.SSD_Instance = &ssd_mock;
	}

	void invoker_userCmd_Set(std::vector<std::string>& userCmd) {
		inv.userCmd = userCmd;
		inv.command_Instance = inv.getCmdInstance();
	}
};

TEST_F(InvokerFixture, writeInvoke) {
	vector<string> userCmd = { "W","2","0x1234ABCD" };
	invoker_userCmd_Set(userCmd);

	EXPECT_CALL(ssd_mock, write(2, 0x1234ABCD)).Times(1);
	EXPECT_EQ(inv.run(), "");
}

TEST_F(InvokerFixture, readInvoke) {
	vector<string> userCmd = { "R","2" };
	invoker_userCmd_Set(userCmd);

	EXPECT_CALL(ssd_mock, read(2)).Times(1);
	EXPECT_EQ(inv.run(), "");
}

TEST(InvokeTest, CMDFailInvoke) {
	vector<string> userCmd = { "r","2","0xAAAABBBB" };
	SSD_Invoker inv(userCmd);
	string errorCheck = inv.run();

	EXPECT_EQ(errorCheck, "INVALID COMMAND.");
}

TEST(InvokeTest, WriteCMDFailInvoke) {

	vector<string> userCmd = { "W","101","0xAABBBB" };
	SSD_Invoker inv(userCmd);
	string errorCheck = inv.run();
	EXPECT_FALSE(errorCheck.empty());
}

TEST(InvokeTest, ReadCMDFailInvoke) {

	vector<string> userCmd = { "R","101" };
	SSD_Invoker inv(userCmd);
	string errorCheck = inv.run();
	EXPECT_FALSE(errorCheck.empty());
}
