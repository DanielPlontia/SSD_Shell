#include <stdexcept>

#include "SSD_HW_Mock.h"
#include "../SSD/write.cpp"

class writeTestFixtrue : public testing::Test {
public:
	SSD_HW_Mock mock_ssd;
	WriteCmd write_cmd{ &mock_ssd };
};

TEST_F(writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_NotMatch_ArgCount) {
	std::vector<std::string> cmd_arg{ "W","12" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg count is less 3 but Not occurred Exception" << std::endl;
}

TEST_F(writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_NotMatch_WriteCmd) {
	std::vector<std::string> cmd_arg{ "NotW","12","0x1234ABCD" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg 0 index is not W but Not occured Exception" << std::endl;
}

TEST_F(writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_Address_Range) {
	std::vector<std::string> cmd_arg{ "W","-3","0x1234ABCD" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg 1 index is not valid Address : �ּ� �����δ� ������ �־����� Exception�� �߻����� �ʾҽ��ϴ�." << std::endl;
	
	cmd_arg = std::vector<std::string>{ "W", "100","0x1234ABCD"};
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException)
		<< "Arg 1 index is not valid Address : �ּ� ������ 100 (99 �ʰ�) �� �־����� Exceptino�� �߻����� �ʾҽ��ϴ�." << std::endl;
}

TEST_F(writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_Address_Format) {
	std::vector<std::string> cmd_arg{ "W","AB","0x1234ABCD" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg 1 index is not valid Address : �ּ� �����δ� ���ڰ��� ������ Exception�� �߻����� �ʾҽ��ϴ�." << std::endl;
	
	cmd_arg = std::vector<std::string>{ "W", "0x12","0x1234ABCD"};
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException)
		<< "Arg 1 index is not valid Address : �ּ� ������ Hex������ string�� ������ Exception�� �߻����� �ʾҽ��ϴ�." << std::endl;
}

TEST_F(writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_Data_Length) {
	std::vector<std::string> cmd_arg{ "W","2","0x1234ABC" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg 2 index is not valid Data : Data�� Legnth�� 9�ڸ��� �־����� Exception�� �߻����� �ʾҽ��ϴ�." << std::endl;

	cmd_arg = std::vector<std::string>{ "W", "2", "0x1234ABCDE" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException)
		<< "Arg 2 index is not valid Data : Data�� Legnth�� 11�ڸ��� �־����� Exception�� �߻����� �ʾҽ��ϴ�." << std::endl;
}

TEST_F(writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_Data_Format) {
	std::vector<std::string> cmd_arg{ "W","2","12345ABCDE" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg 2 index is not valid Data : Data�� ������ 0x�� �������� �ʾ����� Exception�� �߻����� �ʾҽ��ϴ�." << std::endl;

	cmd_arg = std::vector<std::string>{ "W", "2", "0xABCDEFGH" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException)
		<< "Arg 2 index is not valid Data : Data�� Hex���� ����� �� ���� G, H ���� ���ڰ� ���ԵǾ� ������ Exception�� �߻����� �ʾҽ��ϴ�." << std::endl;

	cmd_arg = std::vector<std::string>{ "W", "2", "0xabCDEFGH" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException)
		<< "Arg 2 index is not valid Data : Data�� Hex���� �ҹ��� ���ĺ��� ���Ǿ����� Exception�� �߻����� �ʾҽ��ϴ�." << std::endl;
}

class ParameterizedTestFixture : public testing::TestWithParam<std::string> {
public:
	SSD_HW_Mock mock_ssd;
	WriteCmd write_cmd{ &mock_ssd };
};
INSTANTIATE_TEST_CASE_P(WriteCmd_NormalTest, ParameterizedTestFixture,
	testing::Values("0x1234ABCD", "0x234ABCD1", "0x34ABCD12", "0x4ABCD123", "0xABCD1234"));

TEST_P(ParameterizedTestFixture, WriteCmd_NormalTest) {
	std::string test_value = GetParam();
	std::vector<std::string> cmd_arg{ "W","2", test_value };

	EXPECT_CALL(mock_ssd, write(2, std::stoul(test_value, 0, 16))).Times(1);
	write_cmd.execute(cmd_arg);
}
