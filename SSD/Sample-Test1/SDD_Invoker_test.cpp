#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/SSD_Invoker.cpp"
#include "../SSD/write.cpp"
#include<vector>

using namespace std;
using namespace testing;

public CMD_Mock : public WriteCmd{
public:
	MOCK_METHOD(void, execute,(const std::vector<std::string>& operation),());
}
