#include "DataReader.h"
#include <fstream>

std::string SddDataReader::fileRead() {
    std::ifstream rfs("result.txt");
    if (!rfs) {
        return "Failed to open file.";
    }
    char readData[100];
    rfs.getline(readData, 100);
    rfs.close();
    return readData;
}
