
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

    int removeFile(const char* fileName);

    int flushStream();

    int writeString(const std::string& string, const int offset, const bool freturn);

    std::string readString(const int offet, const bool freturn);

    int writeByteStream(const int8_t* rawArray, const uint32_t arraySize, const int offset, const bool freturn);

    int readByteStream(std::vector<int8_t>& vectorName, const uint32_t numBytes, const int offset, const bool freturn);

    int writeInt(const int byte, const int offset, const bool freturn);

    int readInt(const int offset, const bool freturn);

    int writeInt8(const int8_t byte, const int offset, const bool freturn);

    int8_t readInt8(const int offset, const bool freturn);

    int writeInt16(const int16_t byte, const int offset, const bool freturn);

    int16_t readInt16(const int  offset, const bool freturn);

    int writeInt32(const int32_t byte, const int offset, const bool freturn);
    
    int32_t readInt32(const int offset, const bool freturn);

    int writeInt64(const int64_t byte, const int offset, const bool freturn);

    int64_t readInt64(const int offset, const bool freturn);

    int writeuInt8(const uint8_t byte, const int offset, const bool freturn);

    uint8_t readuInt8(const int offset, const bool freturn);

    int writeuInt16(const uint16_t byte, const int offset, const bool freturn);

    uint16_t readuInt16(const int offset, const bool freturn);

    int writeuInt32(const uint32_t byte, const int offset, const bool freturn);

    uint32_t readuInt32(const int offset, const bool freturn);

    int writeuInt64(const uint64_t byte, const int offset, const bool freturn);

    uint64_t readuInt64(const int offset, const bool freturn);

    int writeChar(const char* character, const int offset, const bool freturn);

    char readChar(const int offset, const bool freturn);

    int writeFloat(const float data, const int offset, const bool freturn);

    float readFloat(const int offset, const bool freturn);

    int writeDouble(const double data, const int offset, const bool freturn);

    double readDouble(const int offset, const bool freturn);

    int writelDouble(const long double data, const int offset, const bool freturn);

    long double readldouble(const int offset, const bool freturn);

    int writelInt(const long int data, const int offset, const bool freturn);

    long int readlInt(const int offset, const bool freturn);

    int writeulInt(const unsigned long int data, const int offset, const bool freturn);

    unsigned long int readulInt(const int offset, const bool freturn);

    int writellInt(const long long int data, const int offset, const bool freturn);

    long long int readllInt(const int offset, const int freturn);



private:
  int m_returnOffset;
  FILE* m_file;
};
#endif
