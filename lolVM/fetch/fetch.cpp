#include "fetch.h"
#include "../cpuEnums.h"
#include "fetch_includes.h"

void fetch(cpu * c) {

	//c->instruction.opCode = *(c->memory + c->pc);
	switch (*(unsigned char*)(c->memory + c->pc))
	{
	case CPU_OP_CODE::JMP_TO_MEM:
		c->instruction.opCode = CPU_OP_CODE::JMP_TO_MEM;
		fetchJmp(c);
		break;
	case CPU_OP_CODE::JMP_NOT_EQUAL:
		c->instruction.opCode = CPU_OP_CODE::JMP_NOT_EQUAL;
		fetchJne(c);
		break;
	case CPU_OP_CODE::ADD_REG_TO_REG:
		c->instruction.opCode = CPU_OP_CODE::ADD_REG_TO_REG;
		break;
	case CPU_OP_CODE::SUB_REG_TO_REG:
		c->instruction.opCode = CPU_OP_CODE::SUB_REG_TO_REG;
		break;
	case CPU_OP_CODE::MUL_REG_TO_REG:
		c->instruction.opCode = CPU_OP_CODE::MUL_REG_TO_REG;
		break;
	case CPU_OP_CODE::CMP_REG_TO_REG:
		c->instruction.opCode = CPU_OP_CODE::CMP_REG_TO_REG;
		fetchCmpRegToReg(c);
		break;
	case CPU_OP_CODE::CMP_REG_TO_MEM:
		c->instruction.opCode = CPU_OP_CODE::CMP_REG_TO_MEM;
		fetchCmpRegToMem(c);
		break;
	case CPU_OP_CODE::CMP_REG_TO_CON:
		c->instruction.opCode = CPU_OP_CODE::CMP_REG_TO_CON;
		fetchCmpRegToCon(c);
		break;
	case CPU_OP_CODE::MOVE_REG_TO_REG:
		c->instruction.opCode = CPU_OP_CODE::MOVE_REG_TO_REG;
		fetchMovRegToReg(c);
		break;
	case CPU_OP_CODE::MOVE_REG_TO_MEM:
		c->instruction.opCode = CPU_OP_CODE::MOVE_REG_TO_MEM;
		fetchMoveRegToMem(c);
		break;
	case CPU_OP_CODE::MOVE_MEM_TO_REG:
		c->instruction.opCode = CPU_OP_CODE::MOVE_MEM_TO_REG;
		fetchMoveMemToReg(c);
		break;
	case CPU_OP_CODE::MOVE_CON_TO_REG:
		c->instruction.opCode = CPU_OP_CODE::MOVE_CON_TO_REG;
		fetchConstToReg(c);
		break;
	case CPU_OP_CODE::MOVE_CON_TO_MEM:
		c->instruction.opCode = CPU_OP_CODE::MOVE_CON_TO_MEM;
		fetchConstToMem(c);
		break;
	case CPU_OP_CODE::PUSH_REG_TO_STACK:
		c->instruction.opCode = CPU_OP_CODE::PUSH_REG_TO_STACK;
		fetchStackRegPush(c);
		break;
	case CPU_OP_CODE::PUSH_MEM_TO_STACK:
		c->instruction.opCode = CPU_OP_CODE::PUSH_MEM_TO_STACK;
		fetchStackMemPush(c);
		break;
	case CPU_OP_CODE::POP_TOP_OF_STACK:
		c->instruction.opCode = CPU_OP_CODE::POP_TOP_OF_STACK;
		//fetchStackRegPush(c);
		break;
	default:
		c->instruction.opCode = CPU_OP_CODE::HALT_CPU;
		break;
	}

}