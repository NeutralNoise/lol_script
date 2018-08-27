#ifndef CPU_CORE_H_INCLUDED
#define CPU_CORE_H_INCLUDED

#include <iostream>
#include "../Common/type_def.h"
#include "../Common/optCodes.h"


struct optInstr
{

	optInstr() {
		opCode = 0;
		first = second = third = forth = 0;
	}

	unsigned char opCode;
	//Params of the opCodes.
	uint32 first, second, third, forth;
};

struct cpuOptions
{
	unsigned char version;
	unsigned char builtOn; //Was the app built on windows or linux
	uint32 pcStart; //Where does the program start. if the program doesn't have a start this is 0;

	cpuOptions() {
		version = 0;
		builtOn = 0;
		pcStart = 0;
	}

};

struct cpu
{
	//Where the program is stored
	char * memory;
	char * stackMemory;
	//Registers
	int32 ra, rb, rc, rd;

	//Program counter
	uint32 pc;
	//Stack pointer.
	uint32 stc;

	uint32 stackSize;
	uint32 memorySize;
	uint32 flags;
	bool running;
	optInstr instruction;
	cpuOptions options;
	uint32 compareFlags;

	cpu() {
		memory = nullptr;
		stackMemory = nullptr;
		stackSize = 0;
		memorySize = 0;
		ra = 0;
		rb = 0;
		rc = 0;
		rd = 0;
		pc = 0;
		stc = 0;
		flags = 0;
		compareFlags = 0;
		//You need some memory to be running
		running = false;
	}

	cpu(const uint32 &stackSize, const uint32 &memorySize) {
		std::cout << "Building CPU\n";
		std::cout << "CPU has stack size of: " << stackSize << " bytes\n";
		std::cout << "CPU has memory size of: " << memorySize << " bytes\n";

		memory = nullptr;
		stackMemory = nullptr;

		if (stackSize == 0) {
			std::cout << "Stack size has to be greater then 0\n";
		}

		if (memorySize == 0) {
			std::cout << "Memory size has to be greater then 0\n";
		}

		this->memorySize = memorySize;
		this->stackSize = stackSize;



		memory = new char[memorySize];
		stackMemory = new char[stackSize];

		ra = 0;
		rb = 0;
		rc = 0;
		rd = 0;
		pc = 0;
		stc = 0;
		flags = 0;
		compareFlags = 0;
		running = true;
	}

	cpu(char *stack, char *memory, const uint32 &stackSize, const uint32 &memorySize) {
		std::cout << "Building CPU\n";
		std::cout << "CPU has stack size of: " << stackSize << " bytes\n";
		std::cout << "CPU has memory size of: " << memorySize << " bytes\n";


		if (stackSize == 0) {
			std::cout << "Stack size has to be greater then 0\n";
		}

		if (memorySize == 0) {
			std::cout << "Memory size has to be greater then 0\n";
		}

		if (stack == nullptr) {
			std::cout << "CPU stack pointer null creating stack\n";
			stackMemory = new char[stackSize];
		}
		if (memory == nullptr) {
			std::cout << "CPU memory pointer null creating memory\n";
			stackMemory = new char[stackSize];
		}

		this->memory = memory;
		stackMemory = stack;

		this->memorySize = memorySize;
		this->stackSize = stackSize;

		ra = 0;
		rb = 0;
		rc = 0;
		rd = 0;
		pc = 0;
		stc = 0;
		flags = 0;
		compareFlags = 0;
		running = true;
	}

	void PrintState() {
		std::cout << "<REGS> " << ra << " " << rb << " " << rc << " " << rd << " " << std::endl;
		std::cout << "<INTR> " << opCodeToString((CPU_OP_CODE)instruction.opCode) << " " << instruction.first << " " << instruction.second << " " << instruction.third << " " << instruction.forth << " " << std::endl;
		std::cout << "<CMP_FLAGS> =" << (compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL) << " !=" << (compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL) << " > " << (compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN) << " < " << (compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN) << "\n";
		std::cout << "Stack Counter = " << stc << "\n";
		std::cout << "Program Counter = " << pc << "\n";
	}

	void reset() {
#ifdef _DEBUG
		std::cout << "Resetting CPU\n";
#endif //DEBUG
		if (memory != nullptr) {
			delete[] memory;
			memory = nullptr;
		}
		if (stackMemory != nullptr) {
			delete[] stackMemory;
			stackMemory = nullptr;
		}
		if (memory == nullptr) {
			memory = new char[memorySize];
		}
		else {
			//Error message about memory here.
		}
		if (stackMemory == nullptr) {
			stackMemory = new char[stackSize];
		}
		else {
			//Error message about statck memory here.
		}

		ra = 0;
		rb = 0;
		rc = 0;
		rd = 0;
		pc = 0;
		stc = 0;
		flags = 0;
		compareFlags = 0;
		instruction = optInstr();
#ifdef _DEBUG
		std::cout << "Finished resetting CPU\n";
#endif //DEBUG
	}

	void reset_val() {
		ra = 0;
		rb = 0;
		rc = 0;
		rd = 0;
		pc = 0;
		stc = 0;
		flags = 0;
		instruction = optInstr();
		compareFlags = 0;
	}

	void free() {
#ifdef _DEBUG
		std::cout << "Freeing CPU\n";
#endif //DEBUG
		if (memory != nullptr) {
			delete[] memory;
			memory = nullptr;
		}
		if (stackMemory != nullptr) {
			delete[] stackMemory;
			stackMemory = nullptr;
		}
#ifdef _DEBUG
		std::cout << "Finished Freeing CPU\n";
#endif //DEBUG
	}

};


#endif //CPU_CORE_H_INCLUDED
