#include "fetch_cmp.h"

void fetchCmpRegToReg(cpu * c) {
	c->instruction.first = *(c->memory + c->pc + 1);
	c->instruction.second = *(c->memory + c->pc + 2);
}

void fetchCmpRegToMem(cpu * c) {
	c->instruction.first = *(c->memory + c->pc + 1);

	char type = *(c->memory + c->pc + 2);

	switch (type)
	{
	case VAL_TYPE::VAL:
		c->instruction.second = *(int32*)(c->memory + *(int32*)(c->memory + c->pc + 3));
		break;
	case VAL_TYPE::PTR:
		c->instruction.second = *(int32*)(c->memory + *(int32*)(c->memory + c->pc + 3));
		break;
	case VAL_TYPE::PTR_VAL:
		c->instruction.second = *(int32*)(c->memory + (*(int32*)(c->memory + (*(int32*)(c->memory + c->pc + 3)))));
		break;
	case VAL_TYPE::ADD_PTR:
		c->instruction.second = *(int32*)(c->memory + c->pc + 3);
		break;
	default:
		break;
	}
}

void fetchCmpRegToCon(cpu * c) {
	c->instruction.first = *(c->memory + c->pc + 1);
	c->instruction.second = *(int32*)(c->memory + c->pc + 2);
}