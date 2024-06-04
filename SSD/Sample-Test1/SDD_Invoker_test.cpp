#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/SSD_Invoker.cpp"
#include "../SSD/write.cpp"
#include "../SSD/read.cpp"
#include "SSD_HW_Mock.h"
#include<vector>

using namespace std;
using namespace testing;

class CMD_Write_Mock : public Command {
public:
	MOCK_METHOD(void, execute, (const std::vector<std::string>& operation), ());

private:
	MOCK_METHOD(bool, check_validation, (), ());
	MOCK_METHOD(void, do_action, (), ());
};


class CMD_Read_Mock : public Command {
public:
	MOCK_METHOD(void, execute, (const std::vector<std::string>& operation), ());

private:
	MOCK_METHOD(bool, check_validation, (), ());
	MOCK_METHOD(void, do_action, (), ());
};

class writeCmdFixtrue : public testing::Test {
public:
	vector<string> userCmd = { "W", "2", "0xAAAABBBB" };
	CMD_Write_Mock writeCmdMock;
};


TEST_F(writeCmdFixtrue, writeInvoke) {
	CMD_Write_Mock writeCmdMock;

	EXPECT_CALL(writeCmdMock, execute).Times(1);
}

