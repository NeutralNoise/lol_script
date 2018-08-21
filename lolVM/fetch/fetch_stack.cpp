#include "fetch_stack.h"


void fetchStackRegPush(cpu * c) {
  c->instruction.first = *(c->memory + c->pc + 1);
}

void fetchStackMemPush(cpu * c) {
  c->instruction.first = *(c->memory + c->pc + 1);
  c->instruction.second = *(uint32*)(c->memory + c->pc + 2);
}

void fetchStackPop(cpu * c) {
  //We don't have to do anything here.....
}
