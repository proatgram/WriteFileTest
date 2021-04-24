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
  file.writeChar('C', -1, false);
  char data = file.readChar(-1, true);
  std::printf("Char in file: %c", data);
  file.closeFile();
  return EXIT_SUCCESS;
}
