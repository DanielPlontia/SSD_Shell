#include "SSD_HW_Mock.h"
#include "../SSD/write.cpp"

class writeTestFixtrue : public testing::Test {
public:
	SSD_HW_Mock mock_ssd;
	WriteCmd write_cmd{ &mock_ssd };
};

TEST_F(writeTestFixtrue, WriteCmd_Exception_When_InvalidArg) {
	std::vector<std::string> cmd_arg{ "NotW","12","0x1234ABCD" };

}