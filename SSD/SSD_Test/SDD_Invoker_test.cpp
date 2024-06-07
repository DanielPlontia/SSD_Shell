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
	SSD_Invoker inv{ std::vector<std::string>() };
	void invoker_userCmd_Set(std::vector<std::string>& userCmd) {
		inv.userCmd = userCmd;
		inv.command_Instance = inv.getCmdInstance();
	}
};

TEST_F(InvokerFixture, readInvoke) {
	vector<string> userCmd = { "R","2" };
	invoker_userCmd_Set(userCmd);
	EXPECT_EQ(inv.run(), "");
}

TEST_F(InvokerFixture, readInvoke_invalidcmd) {
	vector<string> userCmd = { "R","100" };
	invoker_userCmd_Set(userCmd);
	EXPECT_EQ(inv.run(), "READ :validation error!");
}

TEST_F(InvokerFixture, writeInvoke) {
	vector<string> userCmd = { "W","2","0x1234ABCD" };
	invoker_userCmd_Set(userCmd);
	//EXPECT_EQ(inv.run(), "");
}

TEST_F(InvokerFixture, writeInvoke_invalidcmd) {
	vector<string> userCmd = { "W","100","0x1234ABCD" };
	invoker_userCmd_Set(userCmd);
	EXPECT_EQ(inv.run(), "WRITE :validation error!");
}

TEST_F(InvokerFixture, eraseInvoke) {
	vector<string> userCmd = { "E","2","4" };
	invoker_userCmd_Set(userCmd);
	EXPECT_EQ(inv.run(), "");
}

TEST_F(InvokerFixture, eraseInvoke_invalidcmd) {
	vector<string> userCmd = { "E","100","4" };
	invoker_userCmd_Set(userCmd);
	EXPECT_EQ(inv.run(), "ERASE :validation error!");
}

TEST_F(InvokerFixture, flushInvoke) {
	vector<string> userCmd = { "F" };
	invoker_userCmd_Set(userCmd);
	EXPECT_EQ(inv.run(), "");
}

TEST_F(InvokerFixture, flushInvoke_invalidcmd) {
	vector<string> userCmd = { "F","0x12345678"};
	invoker_userCmd_Set(userCmd);
	EXPECT_EQ(inv.run(), "FLUSH :validation error!");
}

class DISABLED_InvokerFixture : public testing::Test {
public:
	SSD_Invoker inv{std::vector<std::string>()};
	std::shared_ptr<SSD_HW_Mock> ssd_mock;
	void SetUp() override {
		ssd_mock = std::make_shared<SSD_HW_Mock>();
	}

	void invoker_userCmd_Set(std::vector<std::string>& userCmd) {
		inv.userCmd = userCmd;
		inv.command_Instance = inv.getCmdInstance();
	}
};

TEST_F(DISABLED_InvokerFixture, writeInvoke) {
	vector<string> userCmd = { "W","2","0x1234ABCD" };
	invoker_userCmd_Set(userCmd);

	EXPECT_CALL(*ssd_mock.get(), write(2, 0x1234ABCD)).Times(1);
	EXPECT_EQ(inv.run(), "");
}

TEST_F(DISABLED_InvokerFixture, readInvoke) {
	vector<string> userCmd = { "R","2" };
	invoker_userCmd_Set(userCmd);

	EXPECT_CALL(*ssd_mock.get(), read(2)).Times(1);
	EXPECT_EQ(inv.run(), "");
}

TEST(DISABLED_InvokerFixture, CMDFailInvoke) {
	vector<string> userCmd = { "r","2","0xAAAABBBB" };
	SSD_Invoker inv(userCmd);
	string errorCheck = inv.run();

	EXPECT_EQ(errorCheck, "INVALID COMMAND.");
}

TEST(DISABLED_InvokerFixture, WriteCMDFailInvoke) {

	vector<string> userCmd = { "W","101","0xAABBBB" };
	SSD_Invoker inv(userCmd);
	string errorCheck = inv.run();
	EXPECT_FALSE(errorCheck.empty());
}

TEST(DISABLED_InvokerFixture, ReadCMDFailInvoke) {

	vector<string> userCmd = { "R","101" };
	SSD_Invoker inv(userCmd);
	string errorCheck = inv.run();
	EXPECT_FALSE(errorCheck.empty());
}
