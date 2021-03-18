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
  file.writeInt32(0x7FFFFFFF, -1, false);
  std::printf("Int 16 in file: 0x%x \n", file.readInt32(0, false));
  file.closeFile();
  return 0;
}