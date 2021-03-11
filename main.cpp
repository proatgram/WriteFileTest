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
  file.writeInt(0xAABBCCDD, -1, false);
  std::printf("Data: 0x%x \n", file.readInt(0, false));
  file.writeInt8(0x7F, -1, true);
  int8_t data = (file.readInt8(-1, false) & 0xFF);
  printf("Int8 Data: 0x%x \n", data);
  file.closeFile();
  return 0;
}
