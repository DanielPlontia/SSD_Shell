#pragma once
#include <string>

class dataReader {
public:
    virtual std::string fileRead() = 0;
};

class SddDataReader : public dataReader {
public:
    std::string fileRead();
};
