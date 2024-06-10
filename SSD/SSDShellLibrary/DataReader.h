#pragma once
#include <string>

#define MAX_RESULT_LEN 100

class dataReader {
public:
    virtual std::string fileRead() = 0;
};

class SddDataReader : public dataReader {
public:
    std::string fileRead();
};
