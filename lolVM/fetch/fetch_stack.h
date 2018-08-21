#ifndef FETCH_STACK_H
#define FETCH_STACK_H
#include "../cpu_core.h"

void fetchStackRegPush(cpu * c);
void fetchStackMemPush(cpu * c);
void fetchStackPop(cpu * c);

#endif //FETCH_STACK_H
