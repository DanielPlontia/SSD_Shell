#include "SSD_HW_Mock.h"
#include "../SSD/read.cpp"

using namespace std;
using namespace testing;

/*
class readTestFixtrue : public testing::Test {
public:
	SSD_HW_Mock mock_ssd;
	SSD_WriteBuffer* write_buffer = SSD_WriteBuffer::getInstance().get();
	ReadCmd read_cmd{ &mock_ssd, write_buffer };
};

TEST_F(readTestFixtrue, ReadCmd_Exception_When_InvalidArgs) {
	try {
		vector<string> cmd_arg1{ "R","10", "XX" };
		read_cmd.execute(cmd_arg1);
		FAIL();
	}
	catch(ReadException e) {
		cout << e.what();
	}

	try {
		vector<string> cmd_arg2{ "R","10", "XX", "XX" };
		read_cmd.execute(cmd_arg2);
		FAIL();
	}
	catch (ReadException e) {
		cout << e.what();
	}
}

TEST_F(readTestFixtrue, ReadCmd_Exception_When_InvalidCmd) {
	try {
		vector<string> cmd_arg1{ "W","10" };
		read_cmd.execute(cmd_arg1);
		FAIL();
	}
	catch (ReadException e) {
		cout << e.what();
	}

	try {
		vector<string> cmd_arg2{ "Read","10" };
		read_cmd.execute(cmd_arg2);
		FAIL();
	}
	catch (ReadException e) {
		cout << e.what();
	}
}

TEST_F(readTestFixtrue, ReadCmd_Exception_When_InvalidAddressValue) {
	vector<string> cmd_arg1{ "R","TEN" };
	EXPECT_THROW(read_cmd.execute(cmd_arg1), ReadException);

	vector<string> cmd_arg2{ "R","SEVEN" };
	EXPECT_THROW(read_cmd.execute(cmd_arg2), ReadException);
}

TEST_F(readTestFixtrue, ReadCmd_Exception_When_InvalidAddressRange) {
	vector<string> cmd_arg1{ "R","100" };
	EXPECT_THROW(read_cmd.execute(cmd_arg1), ReadException);

	vector<string> cmd_arg2{ "R","200" };
	EXPECT_THROW(read_cmd.execute(cmd_arg2), ReadException);
}

TEST_F(readTestFixtrue, ReadCmd_Behavior_Read_Method) {
	vector<string> cmd_arg1{ "R","7" };
	EXPECT_CALL(mock_ssd, read);
	read_cmd.execute(cmd_arg1);

	vector<string> cmd_arg2{ "R","10" };
	EXPECT_CALL(mock_ssd, read).Times(4);
	read_cmd.execute(cmd_arg2);
	read_cmd.execute(cmd_arg2);
	read_cmd.execute(cmd_arg2);
	read_cmd.execute(cmd_arg2);
}
*/