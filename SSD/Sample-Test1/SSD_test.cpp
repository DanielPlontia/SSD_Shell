#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/MySSD.cpp";

class SSDFixture : public testing::Test {
public:
	MySSD ssd;
};

TEST_F(SSDFixture, SetNandData) {
	ssd.read(0);
}