#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <stdexcept>

#include "../TestShell/ssdTestShell.cpp"

using namespace std;

class ExeMock : public exeRunner {
public:
	MOCK_METHOD(void, runner, (string cmd), (override));
};

class dataReaderMock : public dataReader {
public:
	MOCK_METHOD(string, fileRead, (), ());
};

class TestShellFixture : public testing::Test {
public:
	ExeMock exeMock;
	dataReaderMock readerMock;

	TestShell shell{ &exeMock, &readerMock };
};
