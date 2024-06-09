#include "SSD_HW_Mock.h"
#include "../SSD/erase.cpp"

using namespace std;
using namespace testing;


class DISABLED_eraseTestFixtrue : public testing::Test {
public:
	SSD_HW_Mock mock_ssd;
	SSD_WriteBuffer* write_buffer = SSD_WriteBuffer::getInstance().get();
	EraseCmd erase_cmd{ write_buffer };
};

TEST_F(DISABLED_eraseTestFixtrue, EraseCmd_Exception_When_InvalidArgs) {
	try {
		vector<string> cmd_arg1{ "E","1","2","XX" };
		erase_cmd.execute(cmd_arg1);
		FAIL();
	}
	catch (EraseException e) {
		cout << e.what();
	}

	try {
		vector<string> cmd_arg2{ "E","1","2","XX","XX" };
		erase_cmd.execute(cmd_arg2);
		FAIL();
	}
	catch (EraseException e) {
		cout << e.what();
	}
}

TEST_F(DISABLED_eraseTestFixtrue, EraseCmd_Exception_When_InvalidCmd) {
	try {
		vector<string> cmd_arg1{ "R","1","2" };
		erase_cmd.execute(cmd_arg1);
		FAIL();
	}
	catch (EraseException e) {
		cout << e.what();
	}

	try {
		vector<string> cmd_arg2{ "Read","1","2" };
		erase_cmd.execute(cmd_arg2);
		FAIL();
	}
	catch (EraseException e) {
		cout << e.what();
	}
}

TEST_F(DISABLED_eraseTestFixtrue, EraseCmd_Exception_When_InvalidAddressValue) {
	vector<string> cmd_arg1{ "E","ONE","TWO"};
	EXPECT_THROW(erase_cmd.execute(cmd_arg1), EraseException);

	vector<string> cmd_arg2{ "E","THREE","FIVE" };
	EXPECT_THROW(erase_cmd.execute(cmd_arg2), EraseException);
}

TEST_F(DISABLED_eraseTestFixtrue, EraseCmd_Exception_When_InvalidAddressRange) {
	vector<string> cmd_arg1{ "E","100","7"};
	EXPECT_THROW(erase_cmd.execute(cmd_arg1), EraseException);

	vector<string> cmd_arg2{ "E","200","7" };
	EXPECT_THROW(erase_cmd.execute(cmd_arg2), EraseException);
}
