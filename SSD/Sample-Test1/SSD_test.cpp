#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../SSD/MySSD.cpp"

class SSDFixture : public testing::Test {
public:
	MySSD ssd;

	std::string nand_file = "./nand.txt";
	std::string result_file = "./result.txt";
};

TEST_F(SSDFixture, Read) {
	EXPECT_NO_THROW(ssd.read(0));

	std::ifstream file;
	file.open(result_file);
	EXPECT_TRUE(file.is_open());
	std::string line;
	std::getline(file, line);
	EXPECT_EQ(0, std::stoi(line, 0, 16));
	file.close();
}

TEST_F(SSDFixture, Write) {
	EXPECT_NO_THROW(ssd.write(0, 5));
	ssd.read(0);

	std::ifstream file;
	file.open(result_file);
	EXPECT_TRUE(file.is_open());
	std::string line;
	std::getline(file, line);
	EXPECT_EQ(5, std::stoi(line, 0, 16));

	EXPECT_NO_THROW(ssd.write(0, 0));
}