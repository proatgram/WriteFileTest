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
	file.writelDouble(0.1, -1, false);
	long double data = file.readlDouble(0, false);
	std::printf("Long double in file: %lf \n", data);
	file.closeFile();
	return EXIT_SUCCESS;
}
