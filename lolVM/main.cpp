#include <iostream>
#include "cpu_core.h"
#include "fetch/fetch.h"
#include "../Common/optCodes.h"
#include "defines.h"
#include "tests/CpuTest.h"
#include <assert.h>

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
	while (c.running)
	{
		fetch(&c);
		//run the opt code
		optable[c.instruction.opCode](&c);
		c.pc += offset_table[c.instruction.opCode];

	}

	c.free();
#endif
	std::cin.get();

	return 0;
}