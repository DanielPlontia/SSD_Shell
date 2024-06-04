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
	MOCK_METHOD(string, fileRead, (), (override));
};

TEST(ShellTest, ReadData) {
	ExeMock exeMock;
	TestShell shell(&exeMock);
	EXPECT_CALL(exeMock, runner("R 3")).Times(1);

	int address = 3;
	shell.read(3);
}

TEST(ShellTest, FullReadData) {
	ExeMock exeMock;
	dataReaderMock fileReaderMock;
	TestShell shell(&exeMock);
	EXPECT_CALL(exeMock, runner).Times(100);
	EXPECT_CALL(fileReaderMock, fileRead)
		.WillRepeatedly(testing::Return("0xff99"));

	int address = 3;
	shell.fullRead(&fileReaderMock);
}

