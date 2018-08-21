#ifndef FETCH_MOV_H
#define FETCH_MOV_H
#include "../cpu_core.h"

//Fetch the data for a reg to reg move.
void fetchMovRegToReg(cpu * c);

void fetchMoveRegToMem(cpu * c);

void fetchMoveMemToReg(cpu * c);

void fetchConstToReg(cpu * c);

void fetchConstToMem(cpu * c);

void fetchRegToStack(cpu * c);

void fetchStackToReg(cpu * c);

#endif //FETCH_MOV_H