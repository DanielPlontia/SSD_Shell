#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/SSD_Invoker.cpp"
#include "../SSD/write.cpp"
#include "../SSD/read.cpp"
#include "SSD_HW_Mock.h"
#include<vector>

using namespace std;
using namespace testing;

class CMD_Write_Mock : public WriteCmd {
public:
	MOCK_METHOD(void, execute, (const std::vector<std::string>& operation), ());

};


class CMD_Read_Mock : public ReadCmd {
public:
	MOCK_METHOD(void, execute, (const std::vector<std::string>& operation), ());

};


TEST(SSD_Invoker_Test, writeInvoke) {


}

