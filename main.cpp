#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <string>
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

  int writeString(const char * fileName, const std::string& string) {

    const void* buffer = reinterpret_cast<const void*>(string.c_str());

    FILE *file = std::fopen(fileName, "w+");

    if(!file) {
      return EXIT_FAILURE;
    }
    std::fwrite(buffer, sizeof(char),string.size() , file);
    std::fclose(file);
    return EXIT_SUCCESS;
  };
  int writeRaw(const char * fileName, const int rawArray[]) {
    
    FILE *file = std::fopen(fileName, "wb+");

    for (int times = 0; times != 2; times++) {
      int data = rawArray[times];
      printf("%d",data);
      void* buffer = (void*)data;
      //const void* buffer = reinterpret_cast<const void*>(data);
      std::fwrite(buffer, sizeof(int), sizeof(rawArray), file);
    }

    //std::fwrite(buffer, sizeof(int), 2, file);
    //std::fclose(file);
    return EXIT_SUCCESS;
  };

private:  


};

int main() {
  file newFile;
  newFile.writeString("example.dat", "Hello World");
  int testArray[] = {0x01,0x02};
  newFile.writeRaw("example.dat",testArray);

  /*
  FILE *file = std::fopen("inventory.dat", "rb+");
  if (!file) {
    //std::pererr("file opening failed");
    return EXIT_FAILURE;
  }
  */
}
