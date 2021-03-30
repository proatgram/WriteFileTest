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
  file.writeuInt16(0xFFAA, -1, true);
  std::printf("Data: 0x%x \n", file.readuInt16(-1, false));
  file.closeFile();
  return 0x00;
}
