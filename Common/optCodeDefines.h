#ifndef OPT_CODE_DEFINES_H_INCLUDED
#define OPT_CODE_DEFINES_H_INCLUDED

/*

	Move opt codes

*/
#define MOV_REG_TO_REG_OFFSET 3
#define MOV_REG_TO_MEM_OFFSET 6
#define MOV_MEM_TO_REG_OFFSET 7
#define MOV_CONST_TO_REG_OFFSET 6
#define MOV_CONST_TO_MEM_OFFSET 9
#define MOV_REG_TO_STK 6
#define MOV_STK_TO_REG 6

/*

	Stack opt codes

*/

#define PSH_REG_TO_STK_OFFSET 2
#define PSH_MEM_TO_STK_OFFSET 5
#define POP_TOP_OF_STK_OFFSET 5

/*

	Math otp codes

*/

#define ADD_OFFSET 3
#define SUB_OFFSET 3
#define MUL_OFFSET 3

/*

	Jump opt codes

*/

#define JMP_OFFSET 5
#define JNE_OFFSET 5

#endif //OPT_CODE_DEFINES_H_INCLUDED