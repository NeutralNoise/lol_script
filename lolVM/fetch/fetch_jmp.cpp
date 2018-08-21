#include "fetch_jmp.h"

void fetchJmp(cpu * c) {
	c->instruction.first = *(uint32*)(c->memory + c->pc + 1);
}

void fetchJne(cpu * c) {
	c->instruction.first = *(uint32*)(c->memory + c->pc + 1);
}