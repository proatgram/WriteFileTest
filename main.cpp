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
  std::printf("Data written: 0x%x\n", file.readInt(0, false));
  file.closeFile();
  return 0;
}
