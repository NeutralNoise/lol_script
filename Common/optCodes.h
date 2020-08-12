#ifndef OPT_CODDES_H
#define OPT_CODDES_H
#include <string>
//#include "cpu_core.h"
#include "type_def.h"
#include "cpuEnums.h"

struct cpu;

//we Don't wanna do anything with the cpu.
void nop(cpu * c);

//Move register to register
void movrtr(cpu * c);
//Move register to memory
void movrtm(cpu * c);
//Move memory to register
void movmtr(cpu * c);
//Move const to register
void movctr(cpu * c);
//Move const to memory
void movctm(cpu * c);
//Move register to stack
void movrts(cpu * c);
//Move stack to register
void movstr(cpu * c);

//Stack stuff
void pshreg(cpu * c);
void pshmem(cpu * c);
void popstk(cpu * c);

//MATH STUFF!
void add(cpu * c);
void sub(cpu * c);
void mul(cpu * c);

//jmps
void jmp(cpu * c);
void jne(cpu * c);

//compare
void cmprtr(cpu  *c);
void cmprtm(cpu  *c);
void cmprtc(cpu  *c);



//stop the cpu
void hlt(cpu * c);

//4 after add, sub and mul are resurved for furture use. As is address 3B + 4 for div

//TODO this should be moved some where to shut up cygwin g++
// table of opcodes
static void(*optable[256])(cpu*) = {
	/*      | 0 |  1 |  2 |  3 |  4 |  5    |  6    |  7    |  8    |  9    |  A    |  B    |  C |  D |  E |  F |      */
	/* 0 */  nop, jmp, jne, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, add	, nop, nop, nop, nop, /* 0 */
	/* 1 */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, sub	, nop, nop, nop, nop, /* 1 */
	/* 2 */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, mul	, nop, nop, nop, nop, /* 2 */
	/* 3 */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, nop	, nop, nop, nop, nop, /* 3 */
	/* 4 */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, nop	, nop, nop, nop, nop, /* 4 */
	/* 5 */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, nop	, nop, nop, nop, nop, /* 5 */
	/* 6 */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, nop	, nop, nop, nop, nop, /* 6 */
	/* 7 */  nop, nop, nop, nop, nop, cmprtr, cmprtm, cmprtc, nop   , nop   , nop   , nop	, nop, nop, nop, nop, /* 7 */
	/* 8 */  nop, nop, nop, nop, nop, movrtr, movrtm, movmtr, movctr, movctm, movrts, movstr, nop, nop, nop, nop, /* 8 */
	/* 9 */  nop, nop, nop, nop, nop, pshreg, pshmem, popstk, nop   , nop   , nop	, nop	, nop, nop, nop, nop, /* 9 */
	/* A */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, nop	, nop, nop, nop, nop, /* A */
	/* B */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, nop	, nop, nop, nop, nop, /* B */
	/* C */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, nop	, nop, nop, nop, nop, /* C */
	/* D */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, nop	, nop, nop, nop, nop, /* D */
	/* E */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, nop	, nop, nop, nop, nop, /* E */
	/* F */  nop, nop, nop, nop, nop, nop   , nop   , nop   , nop   , nop   , nop	, nop	, nop, nop, nop, hlt, /* F */
};

const uint32 offset_table[256] = {
	/*      | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F |      */
	/* 0 */   1,  5,  5,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 0 */
	/* 1 */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 1 */
	/* 2 */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 2 */
	/* 3 */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 3 */
	/* 4 */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 4 */
	/* 5 */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 5 */
	/* 6 */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 6 */
	/* 7 */   1,  1,  1,  1,  1,  3,  7,  6,  1,  1,  1,  1,  1,  1,  1,  1, /* 7 */
	/* 8 */   1,  1,  1,  1,  1,  3,  6,  7,  6,  9,  6,  6,  1,  1,  1,  1, /* 8 */
	/* 9 */   1,  1,  1,  1,  1,  2,  6,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* 9 */
	/* A */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* A */
	/* B */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* B */
	/* C */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* C */
	/* D */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* D */
	/* E */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* E */
	/* F */   1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, /* F */

};

static std::string opCodeToString(const CPU_OP_CODE &op) {
	switch (op) {
	case CPU_OP_CODE::NO_OP:
		return "nop";
	case CPU_OP_CODE::JMP_TO_MEM:
		return "jmp";
	case CPU_OP_CODE::JMP_NOT_EQUAL:
		return "jne";
	case CPU_OP_CODE::ADD_REG_TO_REG:
		return "add";
	case CPU_OP_CODE::SUB_REG_TO_REG:
		return "sub";
	case CPU_OP_CODE::MUL_REG_TO_REG:
		return "mul";
	case CPU_OP_CODE::CMP_REG_TO_REG:
		return "cmprtr";
	case CPU_OP_CODE::CMP_REG_TO_MEM:
		return "cmprtm";
	case CPU_OP_CODE::CMP_REG_TO_CON:
		return "cmprtc";
	case CPU_OP_CODE::MOVE_REG_TO_REG:
		return "movrtr";
	case CPU_OP_CODE::MOVE_REG_TO_MEM:
		return "movrtm";
	case CPU_OP_CODE::MOVE_MEM_TO_REG:
		return "movmtr";
	case CPU_OP_CODE::MOVE_CON_TO_REG:
		return "movctr";
	case CPU_OP_CODE::MOVE_CON_TO_MEM:
		return "movctm";
	case CPU_OP_CODE::PUSH_REG_TO_STACK:
		return "pshreg";
	case CPU_OP_CODE::PUSH_MEM_TO_STACK:
		return "pshmem";
	case CPU_OP_CODE::POP_TOP_OF_STACK:
		return "popstk";
	case CPU_OP_CODE::HALT_CPU:
		return "hlt";
	default:
		return "Unknown op code: " + std::to_string((int32)op);
	}
	//We shouldn't get here.
	return "Unknown op code: " + std::to_string((int32)op);
}

void RunOpCode(cpu * c);

static uint32 OpCodeSize(const CPU_OP_CODE &op) {
	switch (op) {
	case CPU_OP_CODE::NO_OP:
		return 1;
	case CPU_OP_CODE::JMP_TO_MEM:
		return 5;
	case CPU_OP_CODE::JMP_NOT_EQUAL:
		return 5;
	case CPU_OP_CODE::ADD_REG_TO_REG:
		return 1;
	case CPU_OP_CODE::SUB_REG_TO_REG:
		return 1;
	case CPU_OP_CODE::MUL_REG_TO_REG:
		return 1;
	case CPU_OP_CODE::CMP_REG_TO_REG:
		return 3;
	case CPU_OP_CODE::CMP_REG_TO_MEM:
		return 7;
	case CPU_OP_CODE::CMP_REG_TO_CON:
		return 6;
	case CPU_OP_CODE::MOVE_REG_TO_REG:
		return 3;
	case CPU_OP_CODE::MOVE_REG_TO_MEM:
		return 6;
	case CPU_OP_CODE::MOVE_MEM_TO_REG:
		return 7;
	case CPU_OP_CODE::MOVE_CON_TO_REG:
		return 6;
	case CPU_OP_CODE::MOVE_CON_TO_MEM:
		return 9;
	case CPU_OP_CODE::PUSH_REG_TO_STACK:
		return 2;
	case CPU_OP_CODE::PUSH_MEM_TO_STACK:
		return 6;
	case CPU_OP_CODE::POP_TOP_OF_STACK:
		return 1;
	case CPU_OP_CODE::HALT_CPU:
		return 1;
	default:
		return -1;
	}
	//We shouldn't get here.
	return -1;
}

#endif //OPT_CODDES_H
