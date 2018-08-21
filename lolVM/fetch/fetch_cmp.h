#ifndef FETCH_CMP_H
#define FETCH_CMP_H
#include "../cpu_core.h"

void fetchCmpRegToReg(cpu * c);

void fetchCmpRegToMem(cpu * c);

void fetchCmpRegToCon(cpu * c);

#endif //FETCH_CMP_H