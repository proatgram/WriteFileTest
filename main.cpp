#include <cstdio>
#include <string>
#include <cstring>
#include <cstdint>
#include <vector>
#include <errno.h>


class rrFile {
public:

    int writeString(const char* fileName, const std::string& string) {

      const void* buffer = reinterpret_cast<const void*>(string.c_str());

      FILE* file = std::fopen(fileName, "w");

      if (!file) {
        return EXIT_FAILURE;
      }
      std::fwrite(buffer, sizeof(char), string.size(), file);
      std::fclose(file);
      return EXIT_SUCCESS;
    };

    std::string readString(const char* fileName) {
      FILE* file = std::fopen(fileName, "r");
      if (!file) {
      std::string EXIT_FAIL = std::to_string(EXIT_FAILURE);
      return EXIT_FAIL;
      }
      
    }
    int writeRaw(const char* fileName, const uint8_t* rawArray, const uint32_t arraySize) {

      FILE* file = std::fopen(fileName, "wb");
      if (!file) {
        return EXIT_FAILURE;
      }
        
      fwrite(reinterpret_cast<const void*>(rawArray), 1, arraySize, file);

      std::fclose(file);
      return EXIT_SUCCESS;
    };

    std::vector<uint8_t>* readRaw(const char* fileName, const uint32_t numBytes) {
      FILE* file = std::fopen(fileName, "rb");
      std::vector<uint8_t> *contents = new std::vector<uint8_t>();
      
      if (!file) {
        contents->push_back(EXIT_FAILURE);
        contents->push_back(errno);
        return contents;
      }
      
      int byte;
      while ((byte = std::getc(file)) != EOF ) {
        contents->push_back(byte);
      }
      if (ferror(file)) {
        contents->push_back(EXIT_FAILURE);
        contents->push_back(errno);
        return contents;
      }
      else if (feof(file)) {
        contents->push_back(EOF);
        std::fclose(file);
        return contents;
      }
      std::fclose(file);
      return contents;
    }
private:
};

int main() {
  rrFile newFile;

  newFile.writeString("example.dat", "Hello World");

  const uint8_t testArray[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

  newFile.writeRaw("example1.dat", testArray, sizeof(testArray));

  std::vector<uint8_t>* vector = newFile.readRaw("example1.dat", 5);

  for (int times = 0x00; times != vector->size(); times++){


    printf("0x%x\n",(vector->at(times)));


  }

  return 0;
  
}