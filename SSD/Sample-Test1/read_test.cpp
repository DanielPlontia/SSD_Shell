#include "SSD_HW_Mock.h"
#include "../SSD/read.cpp"

using namespace testing;

class readTestFixtrue : public testing::Test {
public:
	SSD_HW_Mock mock_ssd;
	ReadCmd read_cmd{ &mock_ssd };
};

TEST_F(readTestFixtrue, ReadCmd_Exception_When_InvalidArg) {
	std::vector<std::string> cmd_arg{ "NotW","100","0x1234ABCD" }; // valid 0~99
	EXPECT_THROW(read_cmd.execute(cmd_arg), ReadException);
}