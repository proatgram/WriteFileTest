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
    
  }
  return EXIT_SUCCESS;
}
int rrFile::writeString(const std::string& string, const int offset, const bool freturn) {
	const uint8_t zero = 0x00;
	const void* buffer = reinterpret_cast<const void*>(string.c_str());
	const void* determine = reinterpret_cast<const void*>(&zero);
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fwrite(buffer, sizeof(char), string.size(), m_file);
		std::fwrite(determine, sizeof(uint8_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
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
			m_returnOffset = std::ftell(m_file);
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
			m_returnOffset = std::ftell(m_file);
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
			m_returnOffset = std::ftell(m_file);
		}
		std::fwrite(reinterpret_cast<const void*>(rawArray), sizeof(int8_t), arraySize, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
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
			m_returnOffset = std::ftell(m_file);
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
			m_returnOffset = std::ftell(m_file);
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
			m_returnOffset = std::ftell(m_file);
		}
    int buffer[1];
    buffer[0] = byte;
    const void* data = reinterpret_cast<const void*>(buffer);
    std::fwrite(data, sizeof(int), 1, m_file);
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
	}
  else {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    std::fseek(m_file, offset, SEEK_SET);
    int buffer[1];
    buffer[0] = byte;
    const void* data = reinterpret_cast<const void*>(buffer);
    std::fwrite(data, sizeof(int), 1, m_file);
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
  }
	return EXIT_SUCCESS;
}
int rrFile::readInt(const int offset, const bool freturn) {
  if (offset == -1) {
    if (freturn) {
      m_returnOffset = std::ftell(m_file);
    }
    int8_t data; 
    int output = 0;
    for (uint8_t times = 0x00; times != 0x05; times++) {
      if ((data = std::getc(m_file)) != EOF) {
        output |= ((data & 0xFF) << (times * 8));
      }
    }
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
    return output;
  }
  else {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    std::fseek(m_file, offset, SEEK_SET);
    int8_t data;
    int output = 0;
    for (uint8_t times = 0x00; times != 0x05; times++) {
      if((data = std::getc(m_file)) != EOF) {
        output |= ((data & 0xFF) << (times * 8));
      }
    }
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
    return output;
  }
}
int rrFile::writeInt8(const int8_t byte, const int offset, const bool freturn) {
  if (offset == -1) {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    int8_t buffer[1];
    buffer[0] = byte;
    const void* data = reinterpret_cast<const void*>(buffer);
    std::fwrite(data, sizeof(int8_t), 1, m_file);
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
  }
  else {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    std::fseek(m_file, offset, SEEK_SET);
    int8_t buffer[1];
    buffer[0] = byte;
    const void* data = reinterpret_cast<const void*>(buffer);
    std::fwrite(data, sizeof(int8_t), 1, m_file);
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
  }
  return EXIT_SUCCESS;
}
int8_t rrFile::readInt8(const int offset, const bool freturn) {
  if (offset == -1) {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    int8_t data = 0x00;
    if ((data = std::getc(m_file)) != EOF)
    ;
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
    return data;
  }
  else {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    std::fseek(m_file, offset, SEEK_SET);
    int8_t data = 0x00;
    if ((data = std::getc(m_file)) != EOF)
    ;
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
    return data;
  }
  return EXIT_SUCCESS;
}
int rrFile::writeInt16(const int16_t byte, const int offset, const bool freturn) {
  if (offset == -1) {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    int16_t buffer[1];
    buffer[0] = byte;
    const void* data = reinterpret_cast<const void*>(buffer);
    std::fwrite(data, sizeof(int16_t), 1, m_file);
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
  }
  else {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    std::fseek(m_file, offset, SEEK_SET);
    int16_t buffer[1];
    buffer[0] = byte;
    const void* data = reinterpret_cast<const void*>(buffer);
    std::fwrite(data, sizeof(int16_t), 1, m_file);
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
      
    }
  }
  return EXIT_SUCCESS;
}
int16_t rrFile::readInt16(const int offset, const bool freturn) {
  if (offset == -1) {
    int16_t data; 
    int output = 0;
    for (uint8_t times = 0x00; times != 0x03; times++) {
      if ((data = std::getc(m_file)) != EOF) {
        output |= ((data & 0xFF) << (times * 8));
      }
    }
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
    return output;
  }
  else {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    std::fseek(m_file, offset, SEEK_SET);
    int16_t data;
    int output = 0;
    for (uint8_t times = 0x00; times != 0x03; times++) {
      if((data = std::getc(m_file)) != EOF) {
        output |= ((data & 0xFF) << (times * 8));
      }
    }
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
    return output;
  }
}
int rrFile::writeInt32(const int32_t byte, const int offset, const bool freturn) {
  if (offset == -1) {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    int32_t buffer[1];
    buffer[0] = byte;
    const void* data = reinterpret_cast<const void*>(buffer);
    std::fwrite(data, sizeof(int32_t), 1, m_file);
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
  }
  else {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    std::fseek(m_file, offset, SEEK_SET);
    int32_t buffer[1];
    buffer[0] = byte;
    const void* data = reinterpret_cast<const void*>(buffer);
    std::fwrite(data, sizeof(int32_t), 1, m_file);
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
  }
  return EXIT_SUCCESS;
}
int32_t rrFile::readInt32(const int offset, const bool freturn) {
  if (offset == -1) {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    int32_t data = 0x00;
    int8_t byte = 0x00;
    for (uint8_t times = 0x00; times != 5; times++) {
      if((byte = std::getc(m_file)) != EOF) {
        data |= ((data & 0xFF) << (times * 8));
      }
    }
    if (freturn ==  true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
    return data;
  }
  else {
    if (freturn == true) {
      m_returnOffset = std::ftell(m_file);
    }
    std::fseek(m_file, offset, SEEK_SET);
    int32_t data = 0x00;
    int8_t byte = 0x00;
    for (uint8_t times = 0x00; times != 0x05; times++) {
      if ((byte = std::getc(m_file)) != EOF) {
        data |= ((data & 0xFF) << (times * 8));
      }
    }
    if (freturn == true) {
      std::fseek(m_file, m_returnOffset, SEEK_SET);
    }
  }
  return EXIT_SUCCESS;
}