#ifndef AST_H
#define AST_H
#include <fstream>
#include <assert.h>
#include "ASTNode.h"
#include "../Common/cpuEnums.h"

//TODO This shits fucke. It needs to be removed or moved else where.
#ifdef _WIN32
//#include <Winsock2.h>
#include <stdint.h>
#undef htons
#undef htonl
#undef ntohs
#undef ntohl

#define BIG_ENDIAN 1
#define LITTLE_ENDIAN 2
#define BYTE_ODER LITTLE_ENDIAN


#if BYTE_ORDER == LITTLE_ENDIAN

uint16_t htons(uint16_t v) {
	return (v >> 8) | (v << 8);
}
uint32_t htonl(uint32_t v) {
	return htons(v >> 16) | (htons((uint16_t)v) << 16);
}

#else

inline uint16_t htons(uint16_t v) {
	return v;
}
inline uint32_t htonl(uint32_t v) {
	return v;
}

#endif

inline uint16_t ntohs(uint16_t v) {
	return htons(v);
}
inline uint32_t ntohl(uint32_t v) {
	return htonl(v);
}


#else
#include <arpa/inet.h>
#endif


//TODO write own file for these.

inline void WriteByte(std::ofstream &stream, unsigned char byte) {
	stream << byte;
}

inline void WriteBytes(std::ofstream &stream, unsigned char *byte, const size_t &size) {
	stream.write((char*)byte, size);
}

inline void ReadByte(std::ifstream &stream, unsigned char *byte) {
	stream >> *byte;
}

inline void ReadBytes(std::ifstream &stream, unsigned char *byte, const size_t &size) {
	char *c = new char[size]();
	memset(c, '\0', size);
	stream.read(c, size);
	for (size_t i = 0; i < size; i++) {
		*(byte + i) = (unsigned char)*(c + i);
	}
	
}



class AST
{
public:
	AST() { if (p_root == nullptr) p_root = new ASTNode; p_root->SetType(ASTNodeType::AST_Program); }
	~AST() {}

	ASTNode * GetRoot() { return p_root; }
	void SetRoot(ASTNode * root){ p_root = root; }

	void AddNode(ASTNode * perent, ASTNode *node) { perent->AddNode(node); }

	//This most likely shouldn't be here
	//TODO more this else where
	void WriteAST(std::ofstream &stream) {
		//we need to tell it what to do when writing a function. we will also have to keep track of where each thing is in memory.
		size_t start = 0;
		bool hasMain = false;


		unsigned long startData;
		
		startData = htonl(start);
		//TODO Test for different versions and such
		//WriteBytes(stream, (unsigned char*)&startData, sizeof(long));
		
		if (p_root->GetNodes().size()) {
			std::vector<ASTNode*> nodes = p_root->GetNodes();
			for (size_t i = 0; i < nodes.size(); i++) {
				if (nodes[i]->GetType() == ASTNodeType::AST_Function_Declaration) {
					//This is as function
					if (nodes[i]->GetNodes()[0]->GetType() == ASTNodeType::AST_Function_Identifier) {
						if (strcmp(nodes[i]->GetNodes()[0]->GetLiteral().c_str(), "main") == 0) {
							if (hasMain) {
								//TODO Error Message
							}
							else {
								hasMain = true;
							}
							//start data is where the main begines + the size of its own header.
							startData = sizeof(long);
							WriteBytes(stream, (unsigned char*)&startData, sizeof(long));
							m_fileCursor += sizeof(long);
							//This is a test to make sure we have pasred the right shit.
							assert(nodes[i]->GetNodes()[0]->GetNodes().size() == 1);
							ASTNode * block = nodes[i]->GetNodes()[0]->GetNodes()[0];
							assert(block->GetType() == ASTNodeType::AST_Block_Statement);
							std::vector<ASTNode*> blockNodes = block->GetNodes();
								for (size_t r = 0; r < blockNodes.size(); r++) {
								//This is where we parse the block to turn into byte code.
									if (blockNodes[r]->GetType() == ASTNodeType::AST_Return_Statement) {
										//each block can only have one return statment.
										//write a return statment to file.
										char * op = new char[sizeof(char) + sizeof(char) + sizeof(int) + sizeof(char)];
										if (blockNodes[r]->GetNodes().size()) {
											unsigned int size = sizeof(char) + sizeof(char) + sizeof(int) + sizeof(char);
											op = new char[size];
											m_fileCursor += size;
											*op = 136;
											*(op + 1) = (char)CPU_REG_NUM::RA_NUM;
											if (blockNodes[r]->GetNodes().size()) {
												if (blockNodes[r]->GetNodes()[0]->GetType() == ASTNodeType::AST_Literal) {
													if (blockNodes[r]->GetNodes()[0]->GetToken().GetType() == TokenType::INTEGER_LITERAL) {
														char * pend;
														*(long*)(op + 2) = strtol(blockNodes[r]->GetNodes()[0]->GetToken().GetToken().c_str(),&pend,10);
														*(op + 6) = 255;
														WriteBytes(stream, (unsigned char*)op, size);
														//TODO clear the stack and then jump back to where we where + 1.
													}
												}
												
											}

										}
										else {
											
											
											//TODO clear the stack and then jump back to where we where + 1.
											//Just halt for now.
											op = new char[sizeof(char)];
											//op = new char[sizeof(char) + sizeof(int)];
											
											*op = 255;
											WriteBytes(stream, (unsigned char*)op, sizeof(char));
										}
										
										

										break;
									}

							}

						}
					}
				}
			}
		}




		/*
		std::ifstream istream("../Documents/Examples/test1.lolc");
		
		char * testChar2 = new char[sizeof("Hello World\n")];
		memset(testChar2, '\0', sizeof("Hello World\n"));

		if (istream.is_open()) {
			ReadBytes(istream, (unsigned char*)&startData2, sizeof(long));
			ReadBytes(istream, (unsigned char*)testChar2, sizeof("Hello World\n") - 1);
			ntohl(startData2);
			std::cout << startData2 << '\n';
			int i = 0;
			while (i < strlen(testChar2)) {
				std::cout << *(testChar2 + i);
				i++;
			}
		}
		else {
			std::cout << "unable to open file" << '\n';
		}
		*/


		//stream.write((const char*)&charData[0], sizeof(long));
		//stream << htonl(startAgain);
	}

private:
	ASTNode * p_root = nullptr;
	unsigned int m_fileCursor = 0;
};

#endif //AST_H