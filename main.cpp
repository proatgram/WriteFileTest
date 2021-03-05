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
        return EXIT_FAILURE;
      }
      
    }
    int writeRaw(const char* fileName, const uint8_t* rawArray, const uint32_t arraySize) {

        FILE* file = std::fopen(fileName, "wb");
        if (!file) {
            return EXIT_FAILURE;
        }
        
        

        fwrite(reinterpret_cast<const void*>(rawArray), 1, arraySize, file);

        fclose(file);
        return EXIT_SUCCESS;
    };
    std::vector<uint8_t>* readRaw(const char* fileName, const uint32_t numBytes) {
      FILE* file = std::fopen(fileName, "rb");
      std::vector<uint8_t> *contents = new std::vector<uint8_t>();
      
      if (!file) {
        contents->push_back(0x01);
        printf("Error opening the file errno: (%d: %s)\n", 
          errno, strerror(errno));
        return contents;
      }
      
      int byte;
      while ((byte = std::getc(file)) != EOF ) {
        contents->push_back(byte);
      }
      if (ferror(file)) {
        contents->push_back(0x02);
        return contents;
      }
      else if (feof(file)) {
        contents->push_back(0x03);
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
    const uint8_t testArray[] = { 0x01, 0x02, 0x03 };
    newFile.writeRaw("example1.dat", testArray, sizeof(testArray));
    std::vector<uint8_t>* vector = newFile.readRaw("example1.dat", 5);
    for (int times = 0x00; times != vector->size(); times++){
      printf("0x%x\n",(vector->at(times)));
    }
    /*
    FILE *file = std::fopen("inventory.dat", "rb+");
    if (!file) {
      //std::pererr("file opening failed");
      return EXIT_FAILURE;
    }
    */
}
