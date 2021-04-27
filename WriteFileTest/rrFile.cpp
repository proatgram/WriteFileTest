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
	return EXIT_FAILURE;
}

int rrFile::openFile(const char* fileName) {
	m_file = std::fopen(fileName, "rb+");
	if (!m_file) {
		return EXIT_FAILURE;
	}
	else {
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
int rrFile::closeFile() {
	std::fclose(m_file);
	m_file = nullptr;
	return EXIT_SUCCESS;
}
int rrFile::removeFile(const char* fileName) {
	if (remove(fileName) != 0x00) {
		return EXIT_FAILURE;
	}
	else {
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
int rrFile::flushStream() {
	if (std::fflush(m_file) != 0x00) {
		if (std::feof(m_file) != 0x00) {
			if (std::ferror(m_file) != 0x00) {
				return EXIT_FAILURE;
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
		return EXIT_SUCCESS;
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
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
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
		return std::to_string(EXIT_FAILURE);
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
		return result;
	}
	return std::to_string(EXIT_FAILURE);
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
		return EXIT_SUCCESS;
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
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
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
		return EXIT_SUCCESS;
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
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
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
		return EXIT_SUCCESS;
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
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
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
			if ((data = std::getc(m_file)) != EOF) {
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
		return EXIT_SUCCESS;
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
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
int8_t rrFile::readInt8(const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		int8_t tmp;
		int8_t data = 0x00;
		if ((tmp = std::getc(m_file)) != EOF) {
			data = tmp;
		}
		else {
			data = INT8_MAX;
		}
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
		int8_t tmp;
		int8_t data = 0x00;
		if ((tmp = std::getc(m_file)) != EOF) {
			data = tmp;
		}
		else {
			data = INT8_MAX;
		}

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
		return EXIT_SUCCESS;
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
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
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
		int output = 0x00;
		for (uint8_t times = 0x00; times != 0x03; times++) {
			if ((data = std::getc(m_file)) != EOF) {
				output |= ((data & 0xFF) << (times * 0x08));
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
		std::fwrite(data, sizeof(int32_t), 0x01, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		int32_t buffer[1];
		buffer[0] = byte;
		const void* data = reinterpret_cast<const void*>(buffer);
		std::fwrite(data, sizeof(int32_t), 0x01, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
int32_t rrFile::readInt32(const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		int32_t data = 0x00;
		int8_t byte;
		for (uint8_t times = 0x00; times != 0x05; times++) {
			if ((byte = std::getc(m_file)) != EOF) {
				data |= ((byte & 0xFF) << (times * 0x08));
			}
		}
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
		int32_t data = 0x00;
		int8_t byte;
		for (uint8_t times = 0x00; times != 0x05; times++) {
			if ((byte = std::getc(m_file)) != EOF) {
				data |= ((byte & 0xFF) << (times * 0x08));
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return data;
	}
	return EXIT_SUCCESS;
}
int rrFile::writeInt64(const int64_t byte, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		int64_t data[1];
		data[0] = byte;
		const void* newData = reinterpret_cast<const void*>(data);
		std::fwrite(newData, sizeof(int64_t), 0x01, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		int64_t data[1];
		data[0] = byte;
		const void* newData = reinterpret_cast<const void*>(data);
		std::fwrite(newData, sizeof(int64_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
int64_t rrFile::readInt64(const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		union {
			int64_t data;
			uint8_t input[sizeof(int64_t)];
		}output;
		uint8_t tmp;

		for (uint8_t times = 0x00; times < 0x08; times++) {
			if ((tmp = std::getc(m_file)) != EOF) {
				output.input[times] = tmp;
			}
			else {
				output.data = INT64_MAX;
				break;
			}

		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return output.data;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::getc(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		union {
			int64_t data = 0x00;
			uint8_t input[sizeof(int64_t)];
		}output;
		uint8_t tmp;
		for (uint8_t times = 0x00; times < sizeof(int64_t); times++) {
			if ((tmp = std::getc(m_file)) != EOF) {
				output.input[times] = tmp;
			}
			else {
				output.data = INT64_MAX;
				break;
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return output.data;
	}
	return EXIT_FAILURE;
}
int rrFile::writeuInt8(const uint8_t byte, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		uint8_t buffer[1];
		buffer[0] = byte;
		const void* data = reinterpret_cast<const void*>(buffer);
		std::fwrite(data, sizeof(uint8_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		uint8_t buffer[1];
		buffer[0] = byte;
		const void* data = reinterpret_cast<const void*>(buffer);
		std::fwrite(data, sizeof(uint8_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
uint8_t rrFile::readuInt8(const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		uint8_t data = 0x00;
		if ((data = std::getc(m_file)) != EOF) {

		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return data;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::getc(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		uint8_t data = 0x00;
		if ((data = std::getc(m_file)) != EOF) {

		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return data;
	}
	return EXIT_FAILURE;
}
int rrFile::writeuInt16(const uint16_t data, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		uint16_t buffer[1];
		buffer[0] = data;
		const void* byte = reinterpret_cast<const void*>(buffer);
		std::fwrite(byte, sizeof(uint16_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		uint16_t buffer[1];
		buffer[0] = data;
		const void* byte = reinterpret_cast<const void*>(buffer);
		std::fwrite(byte, sizeof(uint16_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
uint16_t rrFile::readuInt16(const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		uint8_t byte;
		uint16_t data = 0x0000;
		for (uint8_t times = 0x00; times != 0x03; times++) {
			if ((byte = std::getc(m_file)) != EOF) {
				data |= ((byte & 0xFFu) << (times * 0x08u));
			}
		}
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
		uint8_t byte;
		uint16_t data = 0x0000;;
		for (uint8_t times = 0x00; times != 0x03; times++) {
			if ((byte = std::getc(m_file)) != EOF) {
				data |= ((byte & 0xFFu) << (times * 0x08u));
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return data;
	}
	return EXIT_FAILURE;
}
int rrFile::writeuInt32(const uint32_t data, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		uint32_t buffer[1];
		buffer[0] = data;
		const void* byte = reinterpret_cast<const void*>(buffer);
		std::fwrite(byte, sizeof(uint32_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		uint32_t buffer[1];
		buffer[0] = data;
		const void* byte = reinterpret_cast<const void*>(buffer);
		std::fwrite(byte, sizeof(uint32_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
uint32_t rrFile::readuInt32(const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		uint8_t byte;
		uint32_t data = 0x00000000u;
		for (uint8_t times = 0x00; times != 0x05; times++) {
			if ((byte = std::getc(m_file)) != EOF) {
				data |= ((byte & 0xFFu) << (times * 0x08u));
			}
		}
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
		uint8_t byte;
		uint32_t data = 0x00000000u;
		for (uint8_t times = 0x00; times != 0x05; times++) {
			if ((byte = std::getc(m_file)) != EOF) {
				data |= ((byte & 0xFFu) << (times * 0x08u));
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return data;
	}
	return EXIT_FAILURE;
}
int rrFile::writeuInt64(const uint64_t data, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		uint64_t buffer[1];
		buffer[0] = data;
		const void* byte = reinterpret_cast<const void*>(buffer);
		std::fwrite(byte, sizeof(uint64_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		uint64_t buffer[1];
		buffer[0] = data;
		const void* byte = reinterpret_cast<const void*>(buffer);
		std::fwrite(byte, sizeof(uint64_t), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
uint64_t rrFile::readuInt64(const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}

		union {
			uint8_t in[8];
			uint64_t output = 0x00000000000000000;
		}input;
		uint8_t byte;
		for (uint8_t times = 0x00; times < sizeof(uint64_t); times++) {
			if ((byte = std::getc(m_file)) != EOF) {
				input.in[times] = byte;
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return input.output;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		union {
			uint8_t input[sizeof(uint64_t)];
			uint64_t output = 0x000000000000000000;
		}input;
		uint8_t byte;
		for (uint8_t times = 0x00; times < sizeof(uint64_t); times++) {
			if ((byte = std::getc(m_file)) != EOF) {
				input.input[times] = byte;
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return input.output;
	}
	return EXIT_FAILURE;
}
int rrFile::writeChar(const char character, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		char buffer[1];
		buffer[0] = character;
		const void* data = reinterpret_cast<const void*>(buffer);
		std::fwrite(data, sizeof(char), 0x01, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		char buffer[1];
		buffer[0] = character;
		const void* data = reinterpret_cast<const void*>(character);
		std::fwrite(data, sizeof(char), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
char rrFile::readChar(const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		union {
			char data = 0x00;
			uint8_t input[sizeof(char)];
		}output;
		uint8_t tmp;
		for (uint8_t times = 0x00; times < sizeof(char); times++) {
			if ((tmp = std::getc(m_file)) != EOF) {
				output.input[times] = tmp;
			}
			else {
				output.data = CHAR_MAX;
				break;
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return output.data;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		union {
			char data = 0x00;
			uint8_t input[sizeof(char)];
		}output;
		uint8_t tmp;
		for (uint8_t times = 0x00; times < sizeof(char); times++) {
			if ((tmp = std::getc(m_file)) != EOF) {
				output.input[times] = tmp;
			}
			else {
				output.data = CHAR_MAX;
				break;
			}

		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return output.data;
	}
	return '0' + EXIT_FAILURE;
}

int rrFile::writeFloat(const float data, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		float buffer[1];
		buffer[0] = data;
		const void* output = reinterpret_cast<const void*>(buffer);
		std::fwrite(output, sizeof(float), 0x01, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		float buffer[1];
		buffer[0] = data;
		const void* output = reinterpret_cast<const void*>(buffer);
		std::fwrite(output, sizeof(float), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

float rrFile::readFloat(const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		union {
			float data = 0x00f;
			uint8_t input[sizeof(float)];
		}output;
		uint8_t tmp;
		for (uint8_t times = 0x00; times < sizeof(float); times++) {
			if ((tmp = std::getc(m_file)) != EOF) {
				output.input[times] = tmp;
			}
			else {
				output.data = FLT_MAX;
				break;
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return output.data;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		union {
			float data = 0x00f;
			uint8_t input[sizeof(float)];
		}output;
		uint8_t tmp;
		for (uint8_t times = 0x00; times < sizeof(float); times++) {
			if ((tmp = std::getc(m_file)) != EOF) {
				output.input[times] = tmp;
			}
			else {
				output.data = FLT_MAX;
				break;
			}

		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return output.data;
	}
	return EXIT_FAILURE;
}

int rrFile::writeDouble(const double data, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		double buffer[1];
		buffer[0] = data;
		const void* output = reinterpret_cast<const void*>(buffer);
		std::fwrite(output, sizeof(double), 0x01, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		double buffer[1];
		buffer[0] = data;
		const void* output = reinterpret_cast<const void*>(buffer);
		std::fwrite(output, sizeof(double), 1, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

double rrFile::readDouble(const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		union {
			double data = 0x00;
			uint8_t input[sizeof(double)];
		}output;
		uint8_t tmp;
		for (uint8_t times = 0x00; times < sizeof(double); times++) {
			if ((tmp = std::getc(m_file)) != EOF) {
				output.input[times] = tmp;
			}
			else {
				output.data = DBL_MAX;
				break;
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return output.data;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		union {
			double data = 0x00;
			uint8_t input[sizeof(double)];
		}output;
		uint8_t tmp;
		for (uint8_t times = 0x00; times < sizeof(double); times++) {
			if ((tmp = std::getc(m_file)) != EOF) {
				output.input[times] = tmp;
			}
			else {
				output.data = DBL_MAX;
				break;
			}

		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return output.data;
	}
	return EXIT_FAILURE;
}

int rrFile::writelDouble(const long double data, const int offset, const bool freturn) {
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		long double buffer[1];
		buffer[0] = data;
		const void* output = reinterpret_cast<const void*>(buffer);
		std::fwrite(output, sizeof(long double), 0x01, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		long double buffer[1];
		buffer[0] = data;
		const void* output = reinterpret_cast<const void*>(buffer);
		std::fwrite(output, sizeof(long double), 0x01, m_file);
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

long double rrFile::readlDouble(const int offset, const bool freturn)
{
	if (offset == -1) {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		union {
			long double data = 0x00;
			uint8_t input[sizeof(long double)];
		}output;
		uint8_t tmp;
		for (uint8_t times = 0x00; times < sizeof(long double); times++) {
			if ((tmp = std::getc(m_file)) != EOF) {
				output.input[times] = tmp;
			}
			else {
				output.data = LDBL_MAX;
				break;
			}
		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return output.data;
	}
	else {
		if (freturn == true) {
			m_returnOffset = std::ftell(m_file);
		}
		std::fseek(m_file, offset, SEEK_SET);
		union {
			long double data = 0x00;
			uint8_t input[sizeof(long double)];
		}output;
		uint8_t tmp;
		for (uint8_t times = 0x00; times < sizeof(long double); times++) {
			if ((tmp = std::getc(m_file)) != EOF) {
				output.input[times] = tmp;
			}
			else {
				output.data = LDBL_MAX;
				break;
			}

		}
		if (freturn == true) {
			std::fseek(m_file, m_returnOffset, SEEK_SET);
		}
		return output.data;
	}
	return EXIT_FAILURE;
}

int rrFile::writelInt(const long int data, const int offset, const bool freturn)
{
	return 0;
}

long int rrFile::readlInt(const int offset, const bool freturn)
{
	return 0;
}

int rrFile::writeulInt(const unsigned long int data, const int offset, const bool freturn)
{
	return 0;
}

unsigned long int rrFile::readulInt(const int offset, const bool freturn)
{
	return 0;
}

int rrFile::writellInt(const long long int data, const int offset, const bool freturn)
{
	return 0;
}

long long int rrFile::readllInt(const int offset, const int freturn)
{
	return 0;
}
