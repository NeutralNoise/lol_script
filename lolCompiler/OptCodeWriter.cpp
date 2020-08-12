#include "OptCodeWriter.h"
#include <cstring>
#include "../Common/cpuEnums.h"
#include "../Common/ByteWriter.h"
#include "../Common/optCodeDefines.h"

void Writer::WriteNoOp(std::ofstream &stream) {
	unsigned char op = CPU_OP_CODE::NO_OP;
	WriteByte(stream, op);
}

/*

Move Opt Codes

*/

void Writer::WriteMovrtr(std::ofstream &stream, const char &reg1, const char &reg2) {

	unsigned char op[MOV_REG_TO_REG_OFFSET]{CPU_OP_CODE::MOVE_REG_TO_REG, reg1, reg2};
	WriteBytes(stream, &op[0], MOV_REG_TO_REG_OFFSET);
}

void Writer:: WriteMovrtm(std::ofstream &stream, const char &reg, const uint32 &mem) {
	unsigned char op[MOV_REG_TO_MEM_OFFSET]{CPU_OP_CODE::MOVE_REG_TO_MEM, reg};
	//WARN This offset might change. And needs to be updated when ever movrtm is changed.
#ifdef TYPE_PUNNING
	*(uint32*)&op[3] = mem;
#else
	memcpy(&op[3], (char*)mem, sizeof(mem));
#endif
	WriteBytes(stream, &op[0], MOV_REG_TO_REG_OFFSET);
}

void Writer::WriteMovmtr(std::ofstream &stream, const uint32 &mem, const char &type, const char &reg) {
	unsigned char op[MOV_MEM_TO_REG_OFFSET]{CPU_OP_CODE::MOVE_REG_TO_MEM};
	//WARN This offset might change. And needs to be updated when ever movmtr is changed.
#ifdef TYPE_PUNNING
	*(uint32*)&op[1] = mem;
#else
	memcpy(&op[1], (char*)mem, sizeof(mem));
#endif
	op[5] = type;
	op[6] = reg;
	WriteBytes(stream, &op[0], MOV_MEM_TO_REG_OFFSET);
}

void Writer::WriteMovctr(std::ofstream &stream, const char &reg, const uint32 c) {
	unsigned char op[MOV_CONST_TO_REG_OFFSET]{CPU_OP_CODE::MOVE_CON_TO_REG, reg};
#ifdef TYPE_PUNNING
	*(uint32*)&op[1] = c;
#else
	memcpy(&op[1], (char*)c, sizeof(c));
#endif
	WriteBytes(stream, &op[0], MOV_CONST_TO_REG_OFFSET);
}

void Writer::WriteMovctm(std::ofstream &stream, const uint32 &mem, const uint32 &c) {
	unsigned char op[MOV_CONST_TO_MEM_OFFSET]{CPU_OP_CODE::MOVE_CON_TO_REG};


#ifdef TYPE_PUNNING
	*(uint32*)&op[1] = mem;
	*(uint32*)&op[4] = c;
#else
	memcpy(&op[1], (char*)mem, sizeof(mem));
	memcpy(&op[4], (char*)c, sizeof(c));
#endif

	WriteBytes(stream, &op[0], MOV_CONST_TO_MEM_OFFSET);
}

void Writer::WriteMovrts(std::ofstream &stream, const char &reg, const uint32 &mem) {
	unsigned char op[MOV_REG_TO_STK]{CPU_OP_CODE::MOVE_REG_TO_STACK, reg};
	
#ifdef TYPE_PUNNING
	*(uint32*)&op[2] = mem;
#else
	memcpy(&op[2], (char*)mem, sizeof(mem));
#endif

	WriteBytes(stream, &op[0], MOV_REG_TO_STK);
}

void Writer::WriteMovstr(std::ofstream &stream, const uint32 &mem, const char &reg) {
	unsigned char op[MOV_STK_TO_REG]{CPU_OP_CODE::MOVE_REG_TO_STACK};

#ifdef TYPE_PUNNING
	*(uint32*)&op[1] = mem;
#else
	memcpy(&op[1], (char*)mem, sizeof(mem));
#endif

	op[5] = reg;
	WriteBytes(stream, &op[0], MOV_STK_TO_REG);
}

/*

Stack opt codes

*/

void Writer::WritePshreg(std::ofstream &stream, const char &reg) {
	unsigned char op[PSH_REG_TO_STK_OFFSET]{CPU_OP_CODE::PUSH_REG_TO_STACK, reg};
	WriteBytes(stream, &op[0], PSH_REG_TO_STK_OFFSET);
}

void Writer::WritePshmem(std::ofstream &stream, const uint32 &mem) {
	unsigned char op[PSH_MEM_TO_STK_OFFSET]{CPU_OP_CODE::PUSH_MEM_TO_STACK};
#ifdef TYPE_PUNNING
	*(uint32*)&op[1] = mem;
#else
	memcpy(&op[1], (char*)mem, sizeof(mem));
#endif
	WriteBytes(stream, &op[0], PSH_MEM_TO_STK_OFFSET);
}

void Writer::WritePopstk(std::ofstream &stream, const uint32 &mem) {
	unsigned char op[POP_TOP_OF_STK_OFFSET]{CPU_OP_CODE::POP_TOP_OF_STACK};
#ifdef TYPE_PUNNING
	*(uint32*)&op[1] = mem;
#else
	memcpy(&op[1], (char*)mem, sizeof(mem));
#endif
	WriteBytes(stream, &op[0], POP_TOP_OF_STK_OFFSET);
}

/*

Math otp codes

*/

void Writer::WriteAdd(std::ofstream &stream, const char &reg1, const char &reg2) {
	unsigned char op[ADD_OFFSET]{CPU_OP_CODE::ADD_REG_TO_REG};
	//TODO use regs for the math.
	WriteBytes(stream, &op[0], ADD_OFFSET);
}

void Writer::WriteSub(std::ofstream &stream, const char &reg1, const char &reg2) {
	unsigned char op[SUB_OFFSET]{CPU_OP_CODE::SUB_REG_TO_REG};
	//TODO use regs for the math.
	WriteBytes(stream, &op[0], SUB_OFFSET);
}

void Writer::WriteMul(std::ofstream &stream, const char &reg1, const char &reg2) {
	unsigned char op[MUL_OFFSET]{CPU_OP_CODE::MUL_REG_TO_REG};
	//TODO use regs for the math.
	WriteBytes(stream, &op[0], MUL_OFFSET);
}

/*

Jump opt codes

*/

void Writer::WriteJmp(std::ofstream &stream, const uint32 &mem) {
	unsigned char op[JMP_OFFSET]{CPU_OP_CODE::JMP_TO_MEM};
#ifdef TYPE_PUNNING
	*(uint32*)&op[1] = mem;
#else
	memcpy(&op[1], (char*)mem, sizeof(mem));
#endif
	WriteBytes(stream, &op[0], JMP_OFFSET);
}

void Writer::WriteJne(std::ofstream &stream, const uint32 &mem) {
	unsigned char op[JNE_OFFSET]{CPU_OP_CODE::JMP_NOT_EQUAL};
#ifdef TYPE_PUNNING
	*(uint32*)&op[1] = mem;
#else
	memcpy(&op[1], (char*)mem, sizeof(mem));
#endif
	WriteBytes(stream, &op[0], JNE_OFFSET);
}

void Writer::WriteHlt(std::ofstream &stream) {

	unsigned char op = CPU_OP_CODE::HALT_CPU;
	WriteByte(stream, op);
}