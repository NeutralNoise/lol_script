#ifndef COUNTER_JUMP_SIZE_H
#define COUNTER_JUMP_SIZE_H

const char OPCodeJmp = sizeof(char);
const char WhereJmp = sizeof(char);
const char ValTypeJmp = WhereJmp;
const char RegJmp = sizeof(unsigned int);
const char MemJmp = sizeof(unsigned int);

#endif //COUNTER_JUMP_SIZE_H
