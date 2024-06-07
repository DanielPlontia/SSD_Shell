#include <stdexcept>

#include "SSD_HW_Mock.h"
#include "../SSD/write.cpp"


class DISABLED_writeTestFixtrue : public testing::Test {
public:
	SSD_HW_Mock mock_ssd;
	SSD_WriteBuffer* write_buffer = SSD_WriteBuffer::getInstance().get();
	WriteCmd write_cmd{ write_buffer };
};

TEST_F(DISABLED_writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_NotMatch_ArgCount) {
	std::vector<std::string> cmd_arg{ "W","12" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg count is less 3 but Not occurred Exception" << std::endl;
}

TEST_F(DISABLED_writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_NotMatch_WriteCmd) {
	std::vector<std::string> cmd_arg{ "NotW","12","0x1234ABCD" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg 0 index is not W but Not occured Exception" << std::endl;
}

TEST_F(DISABLED_writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_Address_Range) {
	std::vector<std::string> cmd_arg{ "W","-3","0x1234ABCD" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg 1 index is not valid Address : 주소 값으로는 음수를 넣었으나 Exception이 발생하지 않았습니다." << std::endl;
	
	cmd_arg = std::vector<std::string>{ "W", "100","0x1234ABCD"};
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException)
		<< "Arg 1 index is not valid Address : 주소 값으로 100 (99 초과) 를 넣었으나 Exceptino이 발생하지 않았습니다." << std::endl;
}

TEST_F(DISABLED_writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_Address_Format) {
	std::vector<std::string> cmd_arg{ "W","AB","0x1234ABCD" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg 1 index is not valid Address : 주소 값으로는 문자값이 들어갔으나 Exception이 발생하지 않았습니다." << std::endl;
	
	cmd_arg = std::vector<std::string>{ "W", "0x12","0x1234ABCD"};
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException)
		<< "Arg 1 index is not valid Address : 주소 값으로 Hex형태의 string이 들어갔으나 Exception이 발생하지 않았습니다." << std::endl;
}

TEST_F(DISABLED_writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_Data_Length) {
	std::vector<std::string> cmd_arg{ "W","2","0x1234ABC" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg 2 index is not valid Data : Data의 Legnth를 9자리로 넣었으나 Exception이 발생하지 않았습니다." << std::endl;

	cmd_arg = std::vector<std::string>{ "W", "2", "0x1234ABCDE" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException)
		<< "Arg 2 index is not valid Data : Data의 Legnth를 11자리로 넣었으나 Exception이 발생하지 않았습니다." << std::endl;
}

TEST_F(DISABLED_writeTestFixtrue, WriteCmd_Exception_When_InvalidArg_Data_Format) {
	std::vector<std::string> cmd_arg{ "W","2","12345ABCDE" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException) 
		<< "Arg 2 index is not valid Data : Data의 시작이 0x로 시작하지 않았으나 Exception이 발생하지 않았습니다." << std::endl;

	cmd_arg = std::vector<std::string>{ "W", "2", "0xABCDEFGH" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException)
		<< "Arg 2 index is not valid Data : Data의 Hex에서 사용할 수 없는 G, H 같은 문자가 포함되어 있으나 Exception이 발생하지 않았습니다." << std::endl;

	cmd_arg = std::vector<std::string>{ "W", "2", "0xabCDEFGH" };
	EXPECT_THROW(write_cmd.execute(cmd_arg), WriteException)
		<< "Arg 2 index is not valid Data : Data의 Hex에서 소문자 알파벳이 사용되었으나 Exception이 발생하지 않았습니다." << std::endl;
}

class DISABLED_ParameterizedTestFixture : public testing::TestWithParam<std::string> {
public:
	SSD_HW_Mock mock_ssd;
	SSD_WriteBuffer* write_buffer = SSD_WriteBuffer::getInstance().get();
	WriteCmd write_cmd{ write_buffer };
};

/*
INSTANTIATE_TEST_SUITE_P(WriteCmd_NormalTest, ParameterizedTestFixture,
	testing::Values("0x1234ABCD", "0x234ABCD1", "0x34ABCD12", "0x4ABCD123", "0xABCD1234"));

TEST_P(DISABLED_writeTestFixtrue, WriteCmd_NormalTest) {

	std::string test_value = GetParam();
	std::vector<std::string> cmd_arg{ "W","2", test_value };

	EXPECT_CALL(mock_ssd, write(2, std::stoul(test_value, 0, 16))).Times(1);
	write_cmd.execute(cmd_arg);
}
*/