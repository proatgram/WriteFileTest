#include <cstdio>
#include <string>
#include <cstring>
#include <cstdint>
#include <vector>


/*
int main() {
  int data;
  std::ofstream newFileWrite;
  newFileWrite.open("inventory.dat", std::ios::app);
  newFileWrite << 0xA0 << ",";
  newFileWrite.close();
  std::ifstream newFileRead;
  newFileRead.open("inventory.dat");
  newFileRead >> data;
  std::printf("%x\n", data);
  switch (data*) {
    case ",":
      break;
  }
  newFileRead.close();
}
*/

class file {
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

    int writeRaw(const char* fileName, const uint8_t* rawArray, const uint32_t arraySize) {

        FILE* file = std::fopen(fileName, "wb");
        if (!file) {
            return EXIT_FAILURE;
        }
        for (uint32_t i = 0; i < arraySize; i++)
            printf("0x%x \n", rawArray[i]);

        fwrite(reinterpret_cast<const void*>(rawArray), 1, arraySize, file);

        fclose(file);
        return EXIT_SUCCESS;
    };
    std::vector<uint8_t>* readRaw(const char* fileName, const uint32_t numBytes) {
      FILE* file = std::fopen(fileName, "rb");
      std::vector<uint8_t> *contents = new std::vector<uint8_t>();
      
      if (!file) {
        contents->push_back(0x01);
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
    file newFile;
    newFile.writeString("example.dat", "Hello World");
    const uint8_t testArray[] = { 0x01, 0x02, 0x03 };
    newFile.writeRaw("example1.dat", testArray, sizeof(testArray));
    const uint8_t testArrayTwo[] = { 0x04, 0x05, 0x06 };
    newFile.writeRaw("example1.dat", testArrayTwo, sizeof(testArrayTwo));
    std::vector<uint8_t>* vector = newFile.readRaw("example1", 5);
    printf("%x\n",vector);
    for (int times = 0x00; times != vector->size(); times++){
      printf("0x%x\n",vector->at(times));
    }
    /*
    FILE *file = std::fopen("inventory.dat", "rb+");
    if (!file) {
      //std::pererr("file opening failed");
      return EXIT_FAILURE;
    }
    */
}
