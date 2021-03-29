#include <cstdio>
#include <string>
#include <cstring>
#include <cstdint>
#include <vector>
#include <errno.h>
#include "rrFile.h"

int main() {
  rrFile file;
  if (file.openFile("example.dat") == EXIT_FAILURE) {
    file.createFile("example.dat");
    file.openFile("example.dat");
  }
  else {
    file.openFile("example.dat");
  }
  file.writeInt64(0x7FFFFFFFFFFFFFFF, -1, true);
  int64_t dataTest = file.readInt64(-1, false);
  if ((dataTest & 0xFFFFFFFFFFFFFFFF) == 0x7FFFFFFFFFFFFFFF) {
    std::printf("Yes, it equals 0x7FFFFFFFFFFFFFFF \n");
  }
  else {
    std::printf("No, it does not equal 0x7FFFFFFFFFFFFFFF \n");
    for(int i = 0; i < 8; i++)
    {
       printf("%02X", (uint8_t)(dataTest >> (8*i)) & 0xFF);
    }
    printf("\n");
  }
  file.closeFile();
  return 0;
}
