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
  }
  file.writeInt(0xFFFFFFFF, -1, false);
  file.writeInt(0xAAFEFFEF, -1, false);
  file.closeFile();
  return 0;
}
