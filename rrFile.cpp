#include "rrFile.h"
#include <cstdio>
#include <string>
#include <cstdint>
#include <vector>
#include <errno.h>

int rrFile::createFile(const char* fileName) {
    FILE* newFile = std::fopen(fileName, "wb+");
    if (!newFile) {
		return EXIT_FAILURE;
    }
    else {
		std::fclose(newFile);
		return EXIT_SUCCESS;
     }
}

int rrFile::openFile(const char* fileName) {
	m_file = std::fopen(fileName, "rb+");
	if (!m_file) {
		return EXIT_FAILURE;
	}
	else {
		return EXIT_SUCCESS;
	}
	
}
int rrFile::closeFile() {
	std::fclose(m_file);
	m_file = nullptr;
	return EXIT_SUCCESS;
}
int rrFile::removeFile(const char *fileName) {
  if (remove(fileName) != 0x00) {
    return EXIT_FAILURE;
  }
  else {
    return EXIT_SUCCESS;
  }
}
int rrFile::flushStream() {
  if (std::fflush(m_file) != 0x00) {
    if (std::feof(m_file) != 0x00) {
      if (std::ferror(m_file) != 0x00) {
        return 0x01;
      }
      return EOF;
    }
    return 0x02;
  }
  return EXIT_SUCCESS;
}
int rrFile::writeString(const std::string& string, const int offset, const bool freturn) {
	const uint8_t zero = 0x00;
	const void* buffer = reinterpret_cast<const void*>(string.c_str());
	const void* determine = reinterpret_cast<const void*>(&zero);
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = ftell(m_file);
		}
		std::fwrite(buffer, sizeof(char), string.size(), m_file);
		std::fwrite(determine, sizeof(uint8_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	else {
		if (freturn == true) {
			m_returnOffset = ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		std::fwrite(buffer, sizeof(char), string.size(), m_file);
		std::fwrite(determine, sizeof(uint8_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	return 0x00;
}
std::string rrFile::readString(const int offset, const bool freturn) {
	std::string result;
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = ftell(m_file);
		}
		int byte;
		while ((byte = std::getc(m_file)) != 0x00 && std::feof(m_file) == 0x00) {
			char output = static_cast<char>(byte);
			result += output;
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	else {
		if (freturn == true) {
			m_returnOffset = ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		int byte;
		while ((byte = std::getc(m_file)) != 0x00 && std::feof(m_file) == 0x00) {
			char output = static_cast<char>(byte);
			result += output;
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	return result;
}
int rrFile::writeByteStream(const int8_t* rawArray, const uint32_t arraySize, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = ftell(m_file);
		}
		std::fwrite(reinterpret_cast<const void*>(rawArray), sizeof(int8_t), arraySize, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	else {
		if (freturn == true) {
			m_returnOffset = ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		std::fwrite(reinterpret_cast<const void*>(rawArray), sizeof(int8_t), arraySize, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	return EXIT_SUCCESS;
}
int rrFile::readByteStream(std::vector<int8_t>& vectorName, const uint32_t numBytes, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = ftell(m_file);
		}
		int byte;
		for (uint32_t times = 0x00; times != numBytes; times++) {
			if ((byte = std::getc(m_file)) != EOF) {
				vectorName.push_back(byte);
			}
			else {
				break;
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	else {
		if (freturn == true) {
			m_returnOffset = ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		int byte;
		for (uint32_t times = 0x00; times != numBytes; times++) {
			if ((byte = std::getc(m_file)) != EOF) {
				vectorName.push_back(byte);
			}
			else {
				break;
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	return EXIT_SUCCESS;
}
int rrFile::writeInt(const int byte, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = ftell(m_file);
		}
		std::fwrite(reinterpret_cast<const void*>(byte), sizeof(int), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	else {
		if (freturn == true) {
			m_returnOffset = ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		std::fwrite(reinterpret_cast<const void*>(byte), sizeof(int), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	return EXIT_SUCCESS;
}
