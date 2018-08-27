#include <iostream>
#include "cpu_core.h"
#include "fetch/fetch.h"
#include "../Common/optCodes.h"
#include "defines.h"
#include "tests/CpuTest.h"
#include <fstream>
#include <assert.h>
#include <string.h>


void ReadByte(std::ifstream &stream, unsigned char *byte) {
	stream >> *byte;
}

void ReadBytes(std::ifstream &stream, unsigned char *byte, const size_t &size) {
	char *c = new char[size]();
	memset(c, '\0', size);
	stream.read(c, size);
	for (size_t i = 0; i < size; i++) {
		*(byte + i) = (unsigned char)*(c + i);
	}

}


int main(int argc, char ** argv) {

	//Do some checks to make sure our veriable sizes are ok

	assert(sizeof(char) == 1);
	assert(sizeof(uint32) == 4);
	assert(sizeof(uint64) == 8);
	assert(sizeof(float) == 4);
	assert(sizeof(double) == 8);

#ifdef __TEST_CPU
	CpuTest testCPU;
	testCPU.RunTests();
#else
	cpu c(MB(1), MB(1));

	//TODO This doesn't work on linux
	std::ifstream file("../Documents/Examples/test1.lolc", std::ios::binary | std::ios::in);
	std::cout << "Opening binary file!\n";
	if (file.is_open()) {
		ReadBytes(file, (unsigned char*)&c.pc, sizeof(unsigned int));

		for (size_t i = c.pc; !file.eof(); i++) {
			ReadByte(file, (unsigned char*)(c.memory + i));
		}
	}
	else {
		std::cout << "Failed opening binary file!\n";
	}
	while (c.running)
	{
		fetch(&c);
		//run the opt code
		optable[c.instruction.opCode](&c);
		c.pc += offset_table[c.instruction.opCode];

	}
	c.PrintState();
	c.free();
#endif
	std::cin.get();

	return 0;
}
