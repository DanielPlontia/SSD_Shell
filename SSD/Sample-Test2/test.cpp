
#include "TestShellFixture.h"

TEST_F(TestShellFixture, ReadData) {
	EXPECT_CALL(exeMock, runner).Times(1);
	string inputData = "read 3";

	shell.TestExecute(inputData);
}

TEST_F(TestShellFixture, WriteNormal) {
	EXPECT_CALL(exeMock, runner).Times(1);
	string inputData = "write 3 0x10000000";

	shell.TestExecute(inputData);
}

TEST_F(TestShellFixture, FullReadData) {
	string inputData = "fullread";

	EXPECT_CALL(exeMock, runner).Times(100);
	EXPECT_CALL(readerMock, fileRead)
		.WillRepeatedly(testing::Return("0xff99"));

	int address = 3;
	shell.fullRead();
}

TEST_F(TestShellFixture, testApp1) {
	string inputData = "testapp1";

	EXPECT_CALL(readerMock, fileRead)
		.WillRepeatedly(testing::Return("0x12345678"));
	EXPECT_CALL(exeMock, runner).Times(200);
	shell.TestExecute(inputData);

}
