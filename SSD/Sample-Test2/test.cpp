#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include "../TestShell/ssdTestShell.cpp"

using namespace std;

class ExeMock : public exeRunner {
public:
	MOCK_METHOD(void, runner, (string cmd), (override));
};

TEST(ShellTest, ReadData) {
	ExeMock exeMock;
	TestShell shell(&exeMock);
	EXPECT_CALL(exeMock, runner).Times(1);

	int address = 3;
	shell.read(3);
}
TEST(ShellTest, WriteData) {
	ExeMock exeMock;
	TestShell shell(&exeMock);
	EXPECT_CALL(exeMock, runner).Times(1);

	int address = 3;
	string data = "0x10000000";
	shell.write(address, data);
}