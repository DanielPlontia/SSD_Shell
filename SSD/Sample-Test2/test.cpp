#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <stdexcept>

#include "../TestShell/ssdTestShell.cpp"

using namespace std;

class ExeMock : public exeRunner {
public:
	MOCK_METHOD(void, runner, (string cmd), (override));
};

class dataReaderMock : public dataReader {
public:
	MOCK_METHOD(string, fileRead, (), ());
};

class TestShellFixture : public testing::Test {
public:
	ExeMock exeMock;
	dataReaderMock readerMock;

	TestShell shell{ &exeMock, &readerMock };
};

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
