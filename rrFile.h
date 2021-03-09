#include <cstdio>
#include <string>
#include <cstdint>
#include <vector>
#include <errno.h>

#ifndef __RRFILE_H__
#define __RRFILE_H__

class rrFile {
public:
    int createFile(const char* fileName);

    int openFile(const char* fileName);

    int closeFile();

    int writeString(const std::string& string, const int offset, const bool freturn);

    std::string readString(const int offet, const bool freturn);

    int writeByteStream(const int8_t* rawArray, const uint32_t arraySize, const int offset, const bool freturn);

    int readByteStream(std::vector<int8_t>& vectorName, const uint32_t numBytes, const int offset, const bool freturn);

private:
  int m_returnOffset;
  FILE* m_file;
};
#endif
