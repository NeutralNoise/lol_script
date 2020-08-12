#ifndef OPT_CODE_WRITER_H_INCLUDED
#define OPT_CODE_WRITER_H_INCLUDED
#include <fstream>
#include "../Common/type_def.h"

class Writer {
public:

	/* Move */

	/**
	 * \brief Writes a NOOP VM command.
	 * 
	 * \param stream Stream to write the command too.
	*/
	static void WriteNoOp(std::ofstream &stream);

	/**
	 * \brief Writes a mov reg to reg VM command
	 * 
	 * \param stream Stream to write the command too.
	 * \param reg1 Src reg.
	 * \param reg2 Dst reg.
	*/

	static void WriteMovrtr(std::ofstream &stream, const char &reg1, const char &reg2);

	/**
	 * \brief Write a command to write data from a reg to memory.
	 * 
	 * \param stream Stream to write the command too.
	 * \param reg Reg to read from.
	 * \param mem Memory address to write too.
	*/

	//TODO add a type to this.

	static void WriteMovrtm(std::ofstream &stream, const char &reg, const uint32 &mem);

	/**
	 * \brief Write a command to write data from memory to a reg.
	 * 
	 * \param stream Stream to write the command too.
	 * \param mem The memory address to read from.
	 * \param type the type of data \see VAL_TYPE
	 * \param reg Reg to write the data too.
	*/

	static void WriteMovmtr(std::ofstream &stream, const uint32 &mem, const char &type, const char &reg);

	/**
	 * \brief Write a command to write a constant value to a reg.
	 * 
	 * \param stream Stream to write the command too.
	 * \param reg Reg to write constant too.
	 * \param c The constant to write.
	*/

	static void WriteMovctr(std::ofstream &stream, const char &reg, const uint32 c);

	/**
	 * \brief Write a command to write a constant to a memory.
	 * 
	 * \param stream Stream to write the command too.
	 * \param mem Memory address to write the constant too.
	 * \param c The constant to write.
	*/

	static void WriteMovctm(std::ofstream &stream, const uint32 &mem, const uint32 &c);

	/**
	 * \brief Write a command to write data from a reg to the stack.
	 * 
	 * \param stream Stream to write the command too.
	 * \param reg The reg to read the data from.
	 * \param mem The stack address to write the data too.
	*/

	static void WriteMovrts(std::ofstream &stream, const char &reg, const uint32 &mem);

	/**
	 * \brief Write a command to write data from the stack to a reg.
	 * 
	 * \param stream Stream to write the command too.
	 * \param mem The stack address to read the data from.
	 * \param reg The reg to write the data too.
	*/

	static void WriteMovstr(std::ofstream &stream, const uint32 &mem, const char &reg);

	/* Stack stuff */

	/**
	 * \brief Write a command to push data from a reg to the top of the stack.
	 * 
	 * \param stream Stream to write the command too.
	 * \param reg The reg to read the data from.
	*/

	static void WritePshreg(std::ofstream &stream, const char &reg);

	/**
	 * \brief Write a command to push data from memory to the top of the stack.
	 * 
	 * \param stream Stream to write the command too.
	 * \param mem The memory address to read the data from.
	*/

	static void WritePshmem(std::ofstream &stream, const uint32 &mem);

	/**
	 * \brief Write a command to pop data from the top of the stack.
	 * 
	 * \param stream Stream to write the command too.
	 * \param mem Memory address to write the poped data too.
	*/

	static void WritePopstk(std::ofstream &stream, const uint32 &mem);

	/* Math operations */

	/**
	 * \brief Write a command to proform an add operation on two regs.
	 * 
	 * \param stream Stream to write the command too.
	 * \param reg1 The first reg.
	 * \param reg2 The reg that will be added to the first reg.
	*/

	static void WriteAdd(std::ofstream &stream, const char &reg1, const char &reg2);

	/**
	 * \brief Write a command to proform a subtract operation on two regs.
	 * 
	 * \param stream Stream to write the command too.
	 * \param reg1 The first reg.
	 * \param reg2 The reg that will be subtracted from the first reg.
	*/

	static void WriteSub(std::ofstream &stream, const char &reg1, const char &reg2);

	/**
	 * \brief Write a command to proform a multiply operation on two regs.
	 * 
	 * \param stream Stream to write the command too.
	 * \param reg1 The first reg.
	 * \param reg2 The reg that the first reg will be multiplied by.
	*/

	static void WriteMul(std::ofstream &stream, const char &reg1, const char &reg2);

	/* Jumps */

	/**
	 * \brief Writes a command to jump to a memory address
	 * 
	 * \param stream Stream to write the command too.
	 * \param mem The memory address to jump too.
	*/

	static void WriteJmp(std::ofstream &stream, const uint32 &mem);

	/**
	 * \brief Writes a command to conditional jump to a memory address.
	 * 
	 * \param stream Stream to write the command too.
	 * \param mem The memory address to jump too.
	*/

	static void WriteJne(std::ofstream &stream, const uint32 &mem);

	/* Compares */

	static void WriteCmprtr(std::ofstream &stream);
	static void WriteCmprtm(std::ofstream &stream);
	static void WriteCmprtc(std::ofstream &stream);

	static void WriteHlt(std::ofstream &stream);

};
#endif