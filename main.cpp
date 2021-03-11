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
  file.writeInt16(0x7FFF, -1, true);
  std::printf("Int 16 in file: 0x%x \n", file.readInt16(-1, false));
  file.closeFile();
  return 0;
}