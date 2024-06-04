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

TEST(ShellTest, ReadData) {
	ExeMock exeMock;
	EXPECT_CALL(exeMock, runner).Times(1);
	string inputData = "Read 3";
	TestShell shell(&exeMock, inputData);
}

TEST(ShellTest, WriteNormal) {
	ExeMock exeMock;
	EXPECT_CALL(exeMock, runner).Times(1);
	string inputData = "Write 3 0x10000000";
	TestShell shell(&exeMock, inputData);
}

TEST(ShellTest, FullReadData) {
	ExeMock exeMock;
	dataReaderMock fileReaderMock;
	string inputData = "FullRead";
	TestShell shell(&exeMock, inputData);
	EXPECT_CALL(exeMock, runner).Times(100);
	EXPECT_CALL(fileReaderMock, fileRead)
		.WillRepeatedly(testing::Return("0xff99"));

	int address = 3;
	shell.fullRead(&fileReaderMock);
}
