
#include "dmfile.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "gtest.h"

TEST(dmfiletest,dmfiletest )
{
    for (size_t i = 0; i < 10000; i++)
    {
        std::string strFileName = __FILE__;
        std::string s = DMLoadFile(strFileName);

        DMWriteFile(strFileName+ std::string(".TMP"), s);
    }
}

std::string LoadFile(const std::string& fileName) {
    std::ifstream inFile(fileName);
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    return buffer.str();
}

void WriteFile(const std::string& fileName, const std::string& content) {
    std::ofstream outFile(fileName);
    outFile << content;
}

TEST(iostreamtest,iostreamtest )
{
    for (size_t i = 0; i < 10000; i++)
    {
        std::string strFileName = __FILE__;
        std::string s = LoadFile(strFileName);
        WriteFile(strFileName + std::string(".TMP2"), s);
    }
}
