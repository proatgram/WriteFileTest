#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdint>

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
            printf("%02X ", rawArray[i]);

        fwrite(reinterpret_cast<const void*>(rawArray), 1, arraySize, file);

        fclose(file);
        return EXIT_SUCCESS;
    };

private:
};

int main() {
    file newFile;
    newFile.writeString("example.dat", "Hello World");
    const uint8_t testArray[] = { 0x01, 0x02, 0x03 };
    newFile.writeRaw("example1.dat", testArray, sizeof(testArray));

    /*
    FILE *file = std::fopen("inventory.dat", "rb+");
    if (!file) {
      //std::pererr("file opening failed");
      return EXIT_FAILURE;
    }
    */
}
