#include "SSD_HW_Mock.h"
#include "../SSD/flush.cpp"

using namespace std;
using namespace testing;


class DISABLED_flushTestFixtrue : public testing::Test {
public:
	SSD_HW_Mock mock_ssd;
	SSD_WriteBuffer* write_buffer = SSD_WriteBuffer::getInstance().get();
	FlushCmd flush_cmd{ write_buffer };
};

TEST_F(DISABLED_flushTestFixtrue, FlushCmd_Exception_When_InvalidArgs) {
	try {
		vector<string> cmd_arg1{ "F","XX" };
		flush_cmd.execute(cmd_arg1);
		FAIL();
	}
	catch (FlushException e) {
		cout << e.what();
	}

	try {
		vector<string> cmd_arg2{ "F","10","XX" };
		flush_cmd.execute(cmd_arg2);
		FAIL();
	}
	catch (FlushException e) {
		cout << e.what();
	}
}

TEST_F(DISABLED_flushTestFixtrue, FlushCmd_Exception_When_InvalidCmd) {
	try {
		vector<string> cmd_arg1{ "W","10","0x12345678" };
		flush_cmd.execute(cmd_arg1);
		FAIL();
	}
	catch (FlushException e) {
		cout << e.what();
	}

	try {
		vector<string> cmd_arg2{ "Write","10","0x12345678"};
		flush_cmd.execute(cmd_arg2);
		FAIL();
	}
	catch (FlushException e) {
		cout << e.what();
	}
}
