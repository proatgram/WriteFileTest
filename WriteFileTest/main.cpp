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
	file.writelInt(10, -1, false); 
	long int data = file.readlInt(0, false);
	std::printf("Long Int in file: %ld \n", data);
	file.closeFile();
	return EXIT_SUCCESS;
}