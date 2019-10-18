#include <iostream>
#include "cpu_core.h"
#include "fetch/fetch.h"
#include "../Common/optCodes.h"
#include "defines.h"
#include "tests/CpuTest.h"
#include <fstream>
#include <assert.h>
#include <string.h>
#include "../Common/ErrorMessage.h"

//TODO WHAT THE FUCK IS THIS DOING HERE!!!!
ErrorHandlerCom * ErrorHandlerCom::p_instance = nullptr;

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


void OnPrint(const ErrorMessage &msg) {
	std::cout << msg.msg << "\n";
}

void OnFatel(const ErrorMessage &msg) {
	std::cin.get();
	exit(6);
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

	EHC::InitErrorHandler(&OnPrint, &OnFatel);

	cpu c(MB(1), MB(1));

	//TODO This doesn't work on linux
	//TODO Clean this shit up
	//../../Documents/Examples/test1.lolc
	std::ifstream file;
#if 0
	#if defined(_WIN32) || defined(__CYGWIN__)
		#ifdef __CYGWIN__
			std::cout << "../../Documents/Examples/test1.lolc\n";
			file.open("../../Documents/Examples/test1.lolc", std::ios::binary | std::ios::in);
		#else
			std::cout << "../Documents/Examples/test1.lolc\n";
			file.open("../Documents/Examples/test1.lolc", std::ios::binary | std::ios::in);
		#endif
	#elif __linux__
		std::cout << "../../Documents/Examples/test1.lolc\n";
		file.open("../../Documents/Examples/test1.lolc", std::ios::binary | std::ios::in);
	#endif
#endif
	#if defined(_WIN32) || defined(__CYGWIN__)
	#ifdef __CYGWIN__
			std::cout << "../../Documents/Examples/test2.lolc\n";
			file.open("../../Documents/Examples/test2.lolc", std::ios::binary | std::ios::in);
	#else
			std::cout << "../Documents/Examples/test2.lolc\n";
			file.open("../Documents/Examples/test2.lolc", std::ios::binary | std::ios::in);
	#endif
	#elif __linux__
			std::cout << "../../Documents/Examples/test2.lolc\n";
			file.open("../../Documents/Examples/test2.lolc", std::ios::binary | std::ios::in);
	#endif
	//TODO Check file size.
	//TODO Create File systems.
	//TODO move this to a different folder.
	std::cout << "Opening binary file!\n";
	if (file.is_open()) {
		ReadBytes(file, (unsigned char*)&c.pc, sizeof(unsigned int));
		for (size_t i = c.pc; !file.eof(); i++) {
			ReadByte(file, (unsigned char*)(c.memory + i));
		}
		//TODO this is a shit idea.
		c.pc += 4;
	}
	else {
		std::cout << "Failed opening binary file!\n";
	}

	std::cout << "Finished loading binary file!\n";

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
