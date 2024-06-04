#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/MySSD.cpp"

class SSDFixture : public testing::Test {
public:
	MySSD ssd;
};

TEST_F(SSDFixture, Read) {
	EXPECT_NO_THROW(ssd.read(0));
}

TEST_F(SSDFixture, Write) {
	EXPECT_NO_THROW(ssd.write(0, 5));
}