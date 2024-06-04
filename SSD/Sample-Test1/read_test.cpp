#include "SSD_HW_Mock.h"
#include "../SSD/read.cpp"

using namespace testing;

class readTestFixtrue : public testing::Test {
public:
	SSD_HW_Mock mock_ssd;
	ReadCmd read_cmd{ &mock_ssd };
};

TEST_F(readTestFixtrue, ReadCmd_Exception_When_InvalidArg) {
	std::vector<std::string> cmd_arg{ "R","100" }; // valid 0~99

	EXPECT_THROW(read_cmd.execute(cmd_arg), ReadException);
}

TEST_F(readTestFixtrue, ReadCmd_Behavior_Validation) {
	std::vector<std::string> cmd_arg{ "R","10" };

	EXPECT_CALL(mock_ssd, read).Times(1);

	read_cmd.execute(cmd_arg);
}