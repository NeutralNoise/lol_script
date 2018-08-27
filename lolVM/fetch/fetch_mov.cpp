#include "fetch_mov.h"
#include "fetch_stack.h"

void fetchMovRegToReg(cpu * c) {
	c->instruction.first = *(c->memory + c->pc + 1);
	c->instruction.second = *(c->memory + c->pc + 2);
}

void fetchMoveRegToMem(cpu * c) {
	c->instruction.first = *(c->memory + c->pc + 1);
	c->instruction.second = *(uint32*)(c->memory + c->pc + 2);
}

void fetchMoveMemToReg(cpu * c) {
	c->instruction.first = *(uint32*)(c->memory + c->pc + 1);
	c->instruction.second = *(c->memory + c->pc + 5);
	c->instruction.third = *(c->memory + c->pc + 6);
}

void fetchConstToReg(cpu * c) {
	c->instruction.first = *(c->memory + c->pc + 1);
	c->instruction.second = *(int*)(c->memory + c->pc + 2);
}

void fetchConstToMem(cpu * c) {
	c->instruction.first = *(uint32*)(c->memory + c->pc + 1);
	c->instruction.second = *(int32*)(c->memory + c->pc + 5);
}

void fetchRegToStack(cpu * c) {
	//Does the same thing.
	fetchStackRegPush(c);
}

void fetchStackToReg(cpu * c) {
	//what reg to put it in.
	c->instruction.first = (char)*(c->memory + c->pc + 1);
	//where we are getting the data from in the stack.
	c->instruction.second = *(uint32*)(c->memory + c->pc + 2);
}
