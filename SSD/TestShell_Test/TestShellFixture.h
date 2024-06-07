#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <stdexcept>

#include "../SSDShellLibrary/TestShell.h"

using namespace std;

class ExeMock : public exeRunner {
public:
	MOCK_METHOD(bool, runner, (string cmd), (override));
};

class dataReaderMock : public dataReader {
public:
	MOCK_METHOD(string, fileRead, (), ());
};

class TestShellFixture : public testing::Test {
public:
	testing::NiceMock<ExeMock> exeMock;
	testing::NiceMock<dataReaderMock> readerMock;

	TestShell shell{ &exeMock, &readerMock };
};
