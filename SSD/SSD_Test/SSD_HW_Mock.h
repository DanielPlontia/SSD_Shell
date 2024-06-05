#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../SSD/SSD_HW.h"

using namespace testing;

class SSD_HW_Mock : public SSD_HW {
public:
	MOCK_METHOD(void, write, (int, unsigned int), (override));
	MOCK_METHOD(void, read, (int), (override));
};
