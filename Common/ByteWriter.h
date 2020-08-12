#ifndef BYTE_WRITER_H_INCLUDED
#define BYTE_WRITER_H_INCLUDED
#include <fstream>


inline void WriteByte(std::ofstream &stream, unsigned char byte) {
	stream << byte;
}

inline void WriteBytes(std::ofstream &stream, unsigned char *byte, const size_t &size) {
	stream.write((char*)byte, size);
}

inline void ReadByte(std::ifstream &stream, unsigned char *byte) {
	stream >> *byte;
}

inline void ReadBytes(std::ifstream &stream, unsigned char *byte, const size_t &size) {
	char *c = new char[size]();
	memset(c, '\0', size);
	stream.read(c, size);
	for (size_t i = 0; i < size; i++) {
		*(byte + i) = (unsigned char)*(c + i);
	}

}

#endif //BYTE_WRITER_H_INCLUDED