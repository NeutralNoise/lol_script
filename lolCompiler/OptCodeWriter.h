#ifndef OPT_CODE_WRITER_H_INCLUDED
#define OPT_CODE_WRITER_H_INCLUDED
#include <fstream>
#include "../Common/type_def.h"

class Writer {
public:
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
	static void WriteMovrtm(std::ofstream &stream, const char &reg, const uint32 &mem);
	static void WriteMovmtr(std::ofstream &stream, const uint32 &mem, const char &type, const char &reg);
	static void WriteMovctr(std::ofstream &stream, const char &reg, const uint32 c);
	static void WriteMovctm(std::ofstream &stream, const uint32 &mem, const uint32 &c);
	static void WriteMovrts(std::ofstream &stream, const char &reg, const uint32 &mem);
	static void WriteMovstr(std::ofstream &stream, const uint32 &mem, const char &reg);

	static void WritePshreg(std::ofstream &stream, const char &reg);
	static void WritePshmem(std::ofstream &stream, const uint32 &mem);
	static void WritePopstk(std::ofstream &stream, const uint32 &mem);

	static void WriteAdd(std::ofstream &stream, const char &reg1, const char &reg2);
	static void WriteSub(std::ofstream &stream, const char &reg1, const char &reg2);
	static void WriteMul(std::ofstream &stream, const char &reg1, const char &reg2);

	static void WriteJmp(std::ofstream &stream, const uint32 &mem);
	static void WriteJne(std::ofstream &stream, const uint32 &mem);

	static void WriteCmprtr(std::ofstream &stream);
	static void WriteCmprtm(std::ofstream &stream);
	static void WriteCmprtc(std::ofstream &stream);

	static void WriteHlt(std::ofstream &stream);

};
#endif