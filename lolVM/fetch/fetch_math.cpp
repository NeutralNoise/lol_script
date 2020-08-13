#include "fetch_math.h"



void fetchAdd(cpu * c) {
	c->instruction.first = *(c->memory + c->pc + 1);
	c->instruction.second = *(c->memory + c->pc + 2);
}

void fetchSub(cpu * c) {
	c->instruction.first = *(c->memory + c->pc + 1);
	c->instruction.second = *(c->memory + c->pc + 2);
}

void fetchMul(cpu * c) {
	c->instruction.first = *(c->memory + c->pc + 1);
	c->instruction.second = *(c->memory + c->pc + 2);
}
