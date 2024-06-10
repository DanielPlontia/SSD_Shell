#include "DataReader.h"
#include <fstream>

std::string SddDataReader::fileRead() {
    std::ifstream rfs("result.txt");
    if (!rfs) {
        return "Failed to open file.";
    }
    char readData[MAX_RESULT_LEN];
    rfs.getline(readData, MAX_RESULT_LEN);
    rfs.close();
    return readData;
}
