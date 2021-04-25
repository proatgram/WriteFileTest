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
  file.writeFloat(0.123456f, -1, false);
  float data = file.readFloat(0, false);
  std::printf("Char in file: %f \n", data);
  file.closeFile();
  return EXIT_SUCCESS;
}
