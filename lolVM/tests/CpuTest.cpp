#include "CpuTest.h"
#include <assert.h>
#include <chrono>
#include <iostream>
#include "../../Common/cpuEnums.h"
#include "../defines.h"
#include "../../Common/optCodes.h"
#include "../fetch/fetch.h"

void TestSpacer() {
	std::cout << "\n";
	std::cout << "-------------------------------------------------------------------------------\n";
	std::cout << "\n";
}
void InTestSpacer() {
	std::cout << "-------------------------------------------------------------------------------\n";
}

CpuTest::CpuTest()
{
	c = new cpu(MB(1), MB(1));
	m_cpuPassed = false;
}

CpuTest::CpuTest(cpu * c)
{
	this->c = c;
	m_cpuPassed = true;
}


CpuTest::~CpuTest()
{
}

void CpuTest::RunTests() {

	std::cout << "Testing CPU\n";
	std::cout << "Hit enter to start the test\n";
	std::cin.get();
	TestSpacer();
	//Move Tests
	test_movrtr();
	test_movrtm();
	test_movmtr();
	test_movctr();

	//Stack Tests
	test_pshreg();
	test_pshmem();
	test_popstk();

	//Math
	test_add();
	test_sub();
	test_mul();

	//COMPARES
	test_cmprtr();
	test_cmprtm();
	//JMP
	test_jmp();
	test_jne();

	test_hlt();

	test_loop();

	free();
	std::cout << "Finished testing CPU\n";
	std::cout << "All tests passed\n";

}

void CpuTest::test_hlt() {
	hlt(c);
	assert(c->running == false);
}

void CpuTest::test_movrtr() {

	std::cout << "Testing Move <Reg> to <Reg>\n";

	c->ra = 10;
	c->rb = 15;
	c->rc = 6;
	c->rd = 4;
	c->pc = 0;

	*c->memory = (char)CPU_OP_CODE::MOVE_REG_TO_REG;
	*(c->memory + 1) = CPU_REG_NUM::RA_NUM;
	*(c->memory + 2) = CPU_REG_NUM::RB_NUM;

	*(c->memory + 3) = (char)CPU_OP_CODE::MOVE_REG_TO_REG;
	*(c->memory + 4) = CPU_REG_NUM::RC_NUM;
	*(c->memory + 5) = CPU_REG_NUM::RD_NUM;

	fetch(c);
	
	assert(c->instruction.opCode == CPU_OP_CODE::MOVE_REG_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == CPU_REG_NUM::RB_NUM);

	movrtr(c);
	c->PrintState();
	InTestSpacer();
	assert(c->ra == c->rb);


	//Test the other regs
	c->pc += offset_table[CPU_OP_CODE::MOVE_REG_TO_REG];

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::MOVE_REG_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RC_NUM);
	assert(c->instruction.second == CPU_REG_NUM::RD_NUM);

	movrtr(c);
	c->PrintState();
	InTestSpacer();
	assert(c->rc == c->rd);

	c->reset_val();
	TestSpacer();
}

void CpuTest::test_movrtm() {

	std::cout << "Testing Move <Reg> to <Mem>\n";

	c->ra = 10;
	*c->memory = (char)CPU_OP_CODE::MOVE_REG_TO_MEM;
	*(c->memory + 1) = (char)CPU_REG_NUM::RA_NUM;
	*(int32*)(c->memory + 2) = 6;

	fetch(c);
	//Make sure the fetch works
	assert(c->instruction.opCode == CPU_OP_CODE::MOVE_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 6);

	movrtm(c);
	c->PrintState();
	InTestSpacer();
	assert(c->ra == *(int32*)(c->memory + 6));
	c->reset_val();
	TestSpacer();
}

void CpuTest::test_movmtr() {
	std::cout << "Testing Move <Mem> to <Reg>\n";
	std::cout << "Testing VAL\n";

	//Build up the test data.
	*c->memory = (char)CPU_OP_CODE::MOVE_MEM_TO_REG;
	*(int32*)(c->memory + 1) = 7;
	*(c->memory + 5) = (char)VAL_TYPE::VAL;
	*(c->memory + 6) = (char)CPU_REG_NUM::RA_NUM;
	*(int32*)(c->memory + 7) = 10;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::MOVE_MEM_TO_REG);
	assert(c->instruction.first == 7);
	assert(c->instruction.second == VAL_TYPE::VAL);
	assert(c->instruction.third == CPU_REG_NUM::RA_NUM);

	movmtr(c);

	c->PrintState();
	InTestSpacer();
	assert(c->ra == 10);
	c->reset_val();

	std::cout << "Testing PTR\n";

	*c->memory = (char)CPU_OP_CODE::MOVE_MEM_TO_REG;
	*(int32*)(c->memory + 1) = 7;
	*(c->memory + 5) = VAL_TYPE::PTR;
	*(c->memory + 6) = CPU_REG_NUM::RA_NUM;
	*(int32*)(c->memory + 7) = 11;
	//*(int32*)(c->memory + 11) = 5;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::MOVE_MEM_TO_REG);
	assert(c->instruction.first == 7);
	assert(c->instruction.second == VAL_TYPE::PTR);
	assert(c->instruction.third == CPU_REG_NUM::RA_NUM);

	movmtr(c);

	c->PrintState();
	InTestSpacer();
	assert(c->ra == 11);
	c->reset_val();

	std::cout << "Testing PTR_VAL\n";

	*c->memory = (char)CPU_OP_CODE::MOVE_MEM_TO_REG;
	*(int32*)(c->memory + 1) = 7;
	*(c->memory + 5) = VAL_TYPE::PTR_VAL;
	*(c->memory + 6) = CPU_REG_NUM::RA_NUM;
	*(int32*)(c->memory + 7) = 11;
	*(int32*)(c->memory + 11) = 5;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::MOVE_MEM_TO_REG);
	assert(c->instruction.first == 7);
	assert(c->instruction.second == VAL_TYPE::PTR_VAL);
	assert(c->instruction.third == CPU_REG_NUM::RA_NUM);

	movmtr(c);

	c->PrintState();
	InTestSpacer();
	assert(c->ra == 5);
	c->reset_val();

	std::cout << "Testing ADD_PTR\n";

	*c->memory = (char)CPU_OP_CODE::MOVE_MEM_TO_REG;
	*(int32*)(c->memory + 1) = 7;
	*(c->memory + 5) = VAL_TYPE::ADD_PTR;
	*(c->memory + 6) = CPU_REG_NUM::RA_NUM;
	*(int32*)(c->memory + 7) = 11;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::MOVE_MEM_TO_REG);
	assert(c->instruction.first == 7);
	assert(c->instruction.second == VAL_TYPE::ADD_PTR);
	assert(c->instruction.third == CPU_REG_NUM::RA_NUM);

	movmtr(c);

	c->PrintState();
	InTestSpacer();
	assert(c->ra == 7);
	c->reset_val();
	TestSpacer();
}

void CpuTest::test_movctr() {
	std::cout << "Testing Move <Const> to <Reg>\n";

	*c->memory = (char)CPU_OP_CODE::MOVE_CON_TO_REG;
	*(c->memory + 1) = CPU_REG_NUM::RA_NUM;
	*(int32*)(c->memory + 2) = 43;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::MOVE_CON_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 43);

	movctr(c);

	c->PrintState();
	InTestSpacer();
	assert(c->ra == 43);
	c->reset_val();
	TestSpacer();
}

void CpuTest::test_movctm() {
	std::cout << "Testing Move <Const> to <Mem>\n";
	*c->memory = (char)CPU_OP_CODE::MOVE_CON_TO_REG;
	*(int32*)(c->memory + 1) = 10;
	*(int32*)(c->memory + 5) = 43;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::MOVE_CON_TO_REG);
	assert(c->instruction.first == 10);
	assert(c->instruction.second == 43);

	movctr(c);

	c->PrintState();
	InTestSpacer();
	assert(*(uint32*)(c->memory + c->instruction.first) == 43);
	c->reset_val();
	TestSpacer();
}

//Stack Tests

void CpuTest::test_pshreg() {

	std::cout << "Testing Push Reg To Stack\n";

	c->ra = 45;
	*c->memory = (char)CPU_OP_CODE::PUSH_REG_TO_STACK;
	*(c->memory + 1) = (char)CPU_REG_NUM::RA_NUM;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::PUSH_REG_TO_STACK);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);

	pshreg(c);

	//The size of an int or ptr is 4;
	assert(c->stc == 4);
	//we don't have to jump any where because what we need is at the start of the stack.
	assert(*(int32*)(c->stackMemory) == c->ra);

	c->PrintState();
	InTestSpacer();
	c->reset_val();
	TestSpacer();
}

void CpuTest::test_pshmem() {

	std::cout << "Testing Push Mem To Stack\n";
	std::cout << "Testing Push VAL to Stack\n";

	*c->memory = (char)CPU_OP_CODE::PUSH_MEM_TO_STACK;
	*(c->memory + 1) = (char)VAL_TYPE::VAL;
	*(uint32*)(c->memory + 2) = 6;
	*(uint32*)(c->memory + 6) = 64;

	fetch(c);
	assert(c->instruction.opCode == CPU_OP_CODE::PUSH_MEM_TO_STACK);
	assert(c->instruction.first == VAL_TYPE::VAL);
	assert(c->instruction.second == 6);
	
	pshmem(c);

	assert(c->stc == 4);
	assert(*(uint32*)c->stackMemory == 64);

	c->PrintState();
	InTestSpacer();
	c->reset_val();

	std::cout << "Testing Push PTR to Stack\n";

	*c->memory = (char)CPU_OP_CODE::PUSH_MEM_TO_STACK;
	*(c->memory + 1) = (char)VAL_TYPE::PTR;
	*(uint32*)(c->memory + 2) = 6;
	*(uint32*)(c->memory + 6) = 64;

	fetch(c);
	assert(c->instruction.opCode == CPU_OP_CODE::PUSH_MEM_TO_STACK);
	assert(c->instruction.first == VAL_TYPE::PTR);
	assert(c->instruction.second == 6);

	pshmem(c);
	assert(c->stc == 4);
	assert(*(uint32*)c->stackMemory == 6);

	c->PrintState();
	InTestSpacer();
	c->reset_val();

	std::cout << "Testing Push PRT_VAL to Stack\n";

	*c->memory = (char)CPU_OP_CODE::PUSH_MEM_TO_STACK;
	*(c->memory + 1) = (char)VAL_TYPE::PTR_VAL;
	*(uint32*)(c->memory + 2) = 6;
	*(uint32*)(c->memory + 6) = 64;

	fetch(c);
	assert(c->instruction.opCode == CPU_OP_CODE::PUSH_MEM_TO_STACK);
	assert(c->instruction.first == VAL_TYPE::PTR_VAL);
	assert(c->instruction.second == 6);

	pshmem(c);

	assert(c->stc == 4);
	assert(*(uint32*)c->stackMemory == 64);


	c->PrintState();
	InTestSpacer();
	c->reset_val();

	std::cout << "Testing Push ADD_PTR to Stack\n";

	*c->memory = (char)CPU_OP_CODE::PUSH_MEM_TO_STACK;
	*(c->memory + 1) = (char)VAL_TYPE::ADD_PTR;
	*(uint32*)(c->memory + 2) = 6;
	*(uint32*)(c->memory + 6) = 10;
	*(uint32*)(c->memory + 10) = 64;

	fetch(c);
	assert(c->instruction.opCode == CPU_OP_CODE::PUSH_MEM_TO_STACK);
	assert(c->instruction.first == VAL_TYPE::ADD_PTR);
	assert(c->instruction.second == 6);

	pshmem(c);

	assert(c->stc == 4);
	assert(*(uint32*)c->stackMemory == 6);

	c->PrintState();
	InTestSpacer();
	c->reset_val();

	TestSpacer();
}

void CpuTest::test_popstk() {

	std::cout << "Testing Pop Stack\n";

	*c->memory = (char)CPU_OP_CODE::POP_TOP_OF_STACK;
	c->stc = 4;
	fetch(c);
	assert(c->instruction.opCode == CPU_OP_CODE::POP_TOP_OF_STACK);
	popstk(c);
	assert(c->stc == 0);
	c->PrintState();
	InTestSpacer();
	c->reset_val();
	TestSpacer();
}

//Math
void CpuTest::test_add() {
	std::cout << "Testing ADD <Reg> to <Reg>\n";

	*c->memory = (char)CPU_OP_CODE::ADD_REG_TO_REG;
	c->ra = 5;
	c->rb = 15;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::ADD_REG_TO_REG);

	add(c);

	c->PrintState();
	InTestSpacer();
	assert(c->ra == 20);
	c->reset_val();
	TestSpacer();
}

void CpuTest::test_sub() {
	std::cout << "Testing SUB <Reg> to <Reg>\n";

	*c->memory = (char)CPU_OP_CODE::SUB_REG_TO_REG;
	c->ra = 15;
	c->rb = 5;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::SUB_REG_TO_REG);

	sub(c);

	c->PrintState();
	InTestSpacer();
	assert(c->ra == 10);
	c->reset_val();
	TestSpacer();
}

void CpuTest::test_mul() {
	std::cout << "Testing MUL <Reg> to <Reg>\n";

	*c->memory = (char)CPU_OP_CODE::MUL_REG_TO_REG;
	c->ra = 2;
	c->rb = 15;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::MUL_REG_TO_REG);

	mul(c);

	c->PrintState();
	InTestSpacer();
	assert(c->ra == 30);
	c->reset_val();
	TestSpacer();
}


//compare
void CpuTest::test_cmprtr() {
	std::cout << "Testing cmp <REG> <REG> \n";

	std::cout << "Testing EQUAL\n";
	*c->memory = (char)CPU_OP_CODE::CMP_REG_TO_REG;
	*(c->memory + 1) = CPU_REG_NUM::RA_NUM;
	*(c->memory + 2) = CPU_REG_NUM::RB_NUM;
	*(c->memory + 3) = (char)CPU_OP_CODE::CMP_REG_TO_REG;
	*(c->memory + 4) = CPU_REG_NUM::RC_NUM;
	*(c->memory + 5) = CPU_REG_NUM::RD_NUM;
	//Test equals
	c->ra = 10;
	c->rb = 10;
	c->rc = 20;
	c->rd = 20;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == CPU_REG_NUM::RB_NUM);

	cmprtr(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_REG];
	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RC_NUM);
	assert(c->instruction.second == CPU_REG_NUM::RD_NUM);

	cmprtr(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	c->reset_val();

	//Not equal
	std::cout << "Testing NOT EQUAL\n";

	*c->memory = (char)CPU_OP_CODE::CMP_REG_TO_REG;
	*(c->memory + 1) = CPU_REG_NUM::RA_NUM;
	*(c->memory + 2) = CPU_REG_NUM::RB_NUM;
	*(c->memory + 3) = (char)CPU_OP_CODE::CMP_REG_TO_REG;
	*(c->memory + 4) = CPU_REG_NUM::RC_NUM;
	*(c->memory + 5) = CPU_REG_NUM::RD_NUM;
	//Test equals
	c->ra = 5;
	c->rb = 10;
	c->rc = 204;
	c->rd = 20;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == CPU_REG_NUM::RB_NUM);

	cmprtr(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_REG];
	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RC_NUM);
	assert(c->instruction.second == CPU_REG_NUM::RD_NUM);

	cmprtr(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	c->reset_val();

	//Grater than
	std::cout << "Testing Greater than\n";

	*c->memory = (char)CPU_OP_CODE::CMP_REG_TO_REG;
	*(c->memory + 1) = CPU_REG_NUM::RA_NUM;
	*(c->memory + 2) = CPU_REG_NUM::RB_NUM;
	*(c->memory + 3) = (char)CPU_OP_CODE::CMP_REG_TO_REG;
	*(c->memory + 4) = CPU_REG_NUM::RC_NUM;
	*(c->memory + 5) = CPU_REG_NUM::RD_NUM;
	//Test equals
	c->ra = 15;
	c->rb = 10;
	c->rc = 204;
	c->rd = 20;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == CPU_REG_NUM::RB_NUM);

	cmprtr(c);
	c->PrintState();
	InTestSpacer();

	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));
	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_REG];
	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RC_NUM);
	assert(c->instruction.second == CPU_REG_NUM::RD_NUM);

	cmprtr(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));
	c->reset_val();

	//Less Than
	std::cout << "Testing Greater than\n";

	*c->memory = (char)CPU_OP_CODE::CMP_REG_TO_REG;
	*(c->memory + 1) = CPU_REG_NUM::RA_NUM;
	*(c->memory + 2) = CPU_REG_NUM::RB_NUM;
	*(c->memory + 3) = (char)CPU_OP_CODE::CMP_REG_TO_REG;
	*(c->memory + 4) = CPU_REG_NUM::RC_NUM;
	*(c->memory + 5) = CPU_REG_NUM::RD_NUM;
	//Test equals
	c->ra = 13;
	c->rb = 15;
	c->rc = 20;
	c->rd = 200;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == CPU_REG_NUM::RB_NUM);

	cmprtr(c);
	c->PrintState();
	InTestSpacer();

	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));
	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_REG];
	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_REG);
	assert(c->instruction.first == CPU_REG_NUM::RC_NUM);
	assert(c->instruction.second == CPU_REG_NUM::RD_NUM);

	cmprtr(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));
	c->reset_val();
	TestSpacer();
}

void CpuTest::test_cmprtm() {
	std::cout << "Testing cmp <REG> <MEM> \n";

	//Build up a test program
	*c->memory = (char)CPU_OP_CODE::CMP_REG_TO_MEM;
	*(c->memory + 1) = CPU_REG_NUM::RA_NUM;
	*(c->memory + 2) = VAL_TYPE::VAL;
	*(int32*)(c->memory + 3) = 28;
	*(int32*)(c->memory + 28) = 70;
	*(c->memory + 7) = (char)CPU_OP_CODE::CMP_REG_TO_MEM;
	*(c->memory + 8) = CPU_REG_NUM::RA_NUM;
	*(c->memory + 9) = VAL_TYPE::PTR;
	*(int32*)(c->memory + 10) = 32;
	*(int32*)(c->memory + 32) = 36;
	*(c->memory + 14) = (char)CPU_OP_CODE::CMP_REG_TO_MEM;
	*(c->memory + 15) = CPU_REG_NUM::RA_NUM;
	*(c->memory + 16) = VAL_TYPE::PTR_VAL;
	*(int32*)(c->memory + 17) = 32;
	*(c->memory + 21) = (char)CPU_OP_CODE::CMP_REG_TO_MEM;
	*(c->memory + 22) = CPU_REG_NUM::RA_NUM;
	*(c->memory + 23) = VAL_TYPE::ADD_PTR;
	*(int32*)(c->memory + 24) = 32;
	*(int32*)(c->memory + 36) = 70;

	c->ra = 70;

	std::cout << "Testing EQUALS \n";
	std::cout << "Testing VAL\n";
	//Testing VAL

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 70);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	//TESTING PTR
	std::cout << "Testing PTR\n";
	c->ra = 36;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 36);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	std::cout << "Testing PTR_VAL\n";
	c->ra = 70;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 70);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	std::cout << "Testing ADD_PTR\n";
	c->ra = 32;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 32);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];
	//We can just use the same program again but just change the value of ra.

	std::cout << "Testing NOT EQUALS\n";
	std::cout << "Testing GREATER THAN\n";
	std::cout << "Testing VAL\n";
	c->pc = 0;
	//Testing VAL

	c->ra = 72;
	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 70);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	//TESTING PTR
	std::cout << "Testing PTR\n";
	c->ra = 38;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 36);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	std::cout << "Testing PTR_VAL\n";
	c->ra = 76;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 70);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	std::cout << "Testing ADD_PTR\n";
	c->ra = 38;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 32);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	//We can just use the same program again but just change the value of ra.

	std::cout << "Testing NOT EQUALS\n";
	std::cout << "Testing LESS THAN\n";
	std::cout << "Testing VAL\n";
	c->pc = 0;
	//Testing VAL

	c->ra = 68;
	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 70);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	//TESTING PTR
	std::cout << "Testing PTR\n";
	c->ra = 34;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 36);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	std::cout << "Testing PTR_VAL\n";
	c->ra = 2;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 70);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	std::cout << "Testing ADD_PTR\n";
	c->ra = 3;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::CMP_REG_TO_MEM);
	assert(c->instruction.first == CPU_REG_NUM::RA_NUM);
	assert(c->instruction.second == 32);

	cmprtm(c);
	c->PrintState();
	InTestSpacer();
	assert(CPU_COMPARE_FLAGS::CMP_EQUAL != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_NOT_EQUAL == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_NOT_EQUAL));
	assert(CPU_COMPARE_FLAGS::CMP_LESS_THAN == (c->compareFlags & CPU_COMPARE_FLAGS::CMP_LESS_THAN));
	assert(CPU_COMPARE_FLAGS::CMP_GRATER_THAN != (c->compareFlags & CPU_COMPARE_FLAGS::CMP_GRATER_THAN));

	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_MEM];

	c->reset_val();
	TestSpacer();
}

//Jumping

void CpuTest::test_jmp() {
	std::cout << "Testing jmp <MEM> \n";

	*c->memory = (char)CPU_OP_CODE::JMP_TO_MEM;
	*(uint32*)(c->memory + 1) = 10;

	fetch(c);

	assert(c->instruction.opCode == CPU_OP_CODE::JMP_TO_MEM);
	assert(c->instruction.first == 10);

	jmp(c);
	c->pc += offset_table[CPU_OP_CODE::JMP_TO_MEM];
	c->PrintState();
	InTestSpacer();
	assert(c->pc == 10);
	c->reset_val();
	TestSpacer();
}

void CpuTest::test_jne() {
	std::cout << "Testing jne <MEM> \n";

	*c->memory = (char)CPU_OP_CODE::CMP_REG_TO_REG;
	*(c->memory + 1) = CPU_REG_NUM::RA_NUM;
	*(c->memory + 2) = CPU_REG_NUM::RB_NUM;
	*(c->memory + 3) = (char)CPU_OP_CODE::JMP_NOT_EQUAL;
	*(uint32*)(c->memory + 4) = 60;
	c->ra = 50;
	c->rb = 64;

	fetch(c);
	cmprtr(c);
	c->pc += offset_table[CPU_OP_CODE::CMP_REG_TO_REG];

	fetch(c);
	jne(c);
	c->pc += offset_table[CPU_OP_CODE::JMP_NOT_EQUAL];

	c->PrintState();
	InTestSpacer();
	assert(c->pc == 60);
	c->reset_val();
	TestSpacer();
}

void CpuTest::test_loop() {
	std::cout << "Testing a simple loop \n";


	*c->memory = (char)CPU_OP_CODE::MOVE_CON_TO_REG;
	*(c->memory + 1) = CPU_REG_NUM::RA_NUM;
	*(uint32*)(c->memory + 2) = 0;
	*(c->memory + 6) = (char)CPU_OP_CODE::MOVE_CON_TO_REG;
	*(c->memory + 7) = (char)CPU_REG_NUM::RB_NUM;
	*(uint32*)(c->memory + 8) = 1;
	*(c->memory + 12) = (char)CPU_OP_CODE::CMP_REG_TO_CON;
	*(c->memory + 13) = (char)CPU_REG_NUM::RA_NUM;
	//*(uint32*)(c->memory + 14) = 1000000000;
	*(uint32*)(c->memory + 14) = 1000000;
	*(c->memory + 18) = (char)CPU_OP_CODE::ADD_REG_TO_REG;
	*(c->memory + 19) = (char)CPU_OP_CODE::JMP_NOT_EQUAL;
	*(uint32*)(c->memory + 20) = 6;
	*(c->memory + 24) = (char)CPU_OP_CODE::HALT_CPU;

	uint32 instr_ran = 0;
	c->running = true;

	auto start = std::chrono::system_clock::now();

	while (c->running)
	{
		fetch(c);
		//run the opt code
		optable[c->instruction.opCode](c);
		//RunOpCode(c);
		c->pc += offset_table[c->instruction.opCode];
		instr_ran++;

	}

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << instr_ran << " Instructions ran.\n";
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

	int y = 8;
	int g = 54;

	start = std::chrono::system_clock::now();

	for (uint32 i = 0; i != 1000000; i++) {
		if (y == g) {
			//std::cout << "Y Matchs G\n";
			y = g / 7;
		}
		if (y != g) {
			y += (g / 6);
		}
		if (y > g) {
			y = g / 2;
		}
	}

	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;
	std::cout << "C++ loop\n";
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

}