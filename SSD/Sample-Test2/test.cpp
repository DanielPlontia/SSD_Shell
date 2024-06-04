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