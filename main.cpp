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
  int8_t array[] = { 0x00, 0x01, 0x02, 0x03 };
  std::vector<int8_t> testVector;
  file.openFile("example.dat");
  file.writeString("Test Hello World!", -1, false);
  file.writeString("Another Test.", -1, false);
  file.writeByteStream(array, sizeof(array)/sizeof(array[0]), -1, false);
  file.closeFile();
  file.openFile("example.dat");
  printf("First string in file: %s\n", file.readString(-1, false).c_str());
  printf("Second string in file: %s\n", file.readString(-1, false).c_str());
  file.readByteStream(testVector, 4, -1, false);
  for (uint times = 0x00; times != testVector.size(); times++) {
    printf("Data in the file: 0x%x At position: 0x%x \n", testVector.at(times), times);
  }

  file.closeFile();
  return 0;
}
