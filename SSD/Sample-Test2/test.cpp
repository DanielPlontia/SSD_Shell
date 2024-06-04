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

TEST(ShellTest, ParseUserInputWriteCommand) {
	ExeMock exeMock;
	TestShell shell(&exeMock);

	std::string userInput = "write 3 0xffffffff";
	TestShell::inputData expected = { "write", 3, "0xffffffff" };
	TestShell::inputData actual = shell.inputStrParser(userInput);
    
	EXPECT_EQ(expected.command, actual.command);
	EXPECT_EQ(expected.dataAddr, actual.dataAddr);
	EXPECT_EQ(expected.data, actual.data);
}

TEST(ShellTest, ParseUserInputReadCommand) {
	ExeMock exeMock;
	TestShell shell(&exeMock);

	std::string userInput = "read 3";
	TestShell::inputData expected = { "read", 3, "" };
	TestShell::inputData actual = shell.inputStrParser(userInput);

	EXPECT_EQ(expected.command, actual.command);
	EXPECT_EQ(expected.dataAddr, actual.dataAddr);
	EXPECT_EQ(expected.data, actual.data);
}

TEST(ShellTest, ParseUserInputExitCommand) {
	ExeMock exeMock;
	TestShell shell(&exeMock);

	std::string userInput = "exit";
	TestShell::inputData expected = { "exit", 0, "" };
	TestShell::inputData actual = shell.inputStrParser(userInput);

	EXPECT_EQ(expected.command, actual.command);
	EXPECT_EQ(expected.dataAddr, actual.dataAddr);
	EXPECT_EQ(expected.data, actual.data);
}

TEST(ShellTest, ParseUserInputWrongCommand) {
	ExeMock exeMock;
	TestShell shell(&exeMock);

	std::string userInput = "Reed 3 0xffff";
	
	EXPECT_THROW(shell.inputStrParser(userInput) , exception);
}

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

