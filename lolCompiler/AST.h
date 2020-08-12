#ifndef AST_H
#define AST_H
#include <fstream>
#include <assert.h>
#include "ASTNode.h"
#include "../Common/cpuEnums.h"
#include "../Common/ByteWriter.h"
#include "ASTWriter.h"

//TODO This shits fucke. It needs to be removed or moved else where.
//TODO This needs to do a lot more work.
#ifdef _WIN32
//#include <Winsock2.h>
#include <stdint.h>
#include <string> 
#undef htons
#undef htonl
#undef ntohs
#undef ntohl
//This needs to better support other endianness
#define BIG_ENDIAN 1
#define LITTLE_ENDIAN 2
#define WINDOWS_ENDIAN 3
//#define BYTE_ORDER LITTLE_ENDIAN
#define BYTE_ORDER WINDOWS_ENDIAN


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


/**
 * \class AST
 * \brief Abstract Syntax Tree
 * 
*/

class AST
{
public:

	/**
	 * \brief Construct a new AST object
	 * 
	*/

	AST() { if (p_root == nullptr) p_root = new ASTNode; p_root->SetType(ASTNodeType::AST_Program); }

	/**
	 * \brief Destroy the AST object
	 * 
	*/

	~AST() {}

	/**
	 * \brief Get the Root of the tree.
	 * 
	 * \return ASTNode* 
	*/

	ASTNode * GetRoot() { return p_root; }

	/**
	 * \brief Set the Root object
	 * 
	 * \param root The node where the tree strarts.
	*/

	void SetRoot(ASTNode * root){ p_root = root; }

	/**
	 * \brief Add a node to the tree.
	 * 
	 * \param perent Where does this node connect to the rest of the tree.
	 * \param node The node to add to the tree.
	*/

	void AddNode(ASTNode * perent, ASTNode *node) { perent->AddNode(node); }

	//This most likely shouldn't be here
	//TODO move this else where
	//TODO break this up so that each type of node has its own write funtion. CHECK ASTWriter.h

	/**
	 * \brief Write the AST to an out stream
	 * 
	 * \param stream The string to write the AST too.
	*/

	void WriteAST(std::ofstream &stream) {
		//we need to tell it what to do when writing a function. we will also have to keep track of where each thing is in memory.
		size_t start = 0;
		bool hasMain = false;


		unsigned long startData;
		
		startData = sizeof(long);
		//Account for the header.
		m_fileCursor = sizeof(long);
		//TODO Test for different versions and such
		WriteBytes(stream, (unsigned char*)&startData, sizeof(long));
		
		if (p_root->GetNodes().size()) {
			std::vector<ASTNode*> nodes = p_root->GetNodes();
			for (size_t i = 0; i < nodes.size(); i++) {

				if (nodes[i]->GetType() == ASTNodeType::AST_Variable_Declaration) {
					//Check if the variable has already been decleard.
					ASTNode * node = nodes[i]->GetPerent();
					while (1) {
						if (node == nullptr) {
							//we have reached the top.
							break;
						}
						std::vector<ASTNode*> n = p_root->GetNodes();
						for (size_t t = 0; t < n.size(); t++) {
							//We don't wanna go past here because its the same one as this one. so just go up to the next level.
							if (nodes[i] == n[t]) {
								node = node->GetPerent();
								break;
							}
							if (n[t]->GetType() == ASTNodeType::AST_Variable_Declaration) {
								for (size_t r = 0; r < n[t]->GetNodes().size(); r++) {
									if (n[t]->GetNodes()[r]->GetType() == ASTNodeType::AST_Variable_Identifier) {
										for (size_t j = 0; j < nodes[i]->GetNodes().size(); j++) {
											if (nodes[i]->GetNodes()[j]->GetType() == ASTNodeType::AST_Variable_Identifier) {
												if (n[t]->GetNodes()[r]->GetLiteral() == nodes[i]->GetNodes()[j]->GetLiteral()) {
													//TODO error message about haveing a var with the same name in the same scope.
													std::cout << "Can't have 2 vars with the same naem!\n";
													return;
												}
											}
											else {
												//TODO Error Message
												//Expected ASTNodeType::AST_Variable_Identifier
											}
											
										}
										
									}
								}
							}
						}
						node = node->GetPerent();
					}
					//Check if we have a literal defining the vars if there are more then one decleard here.
					if (nodes[i]->GetNodes().size()) {
						std::vector<ASTNode*> n = nodes[i]->GetNodes();
						for (size_t t = 0; t < n.size(); t++) {
							std::vector<ASTNode*> nlit = nlit[t]->GetNodes();
							for (size_t d = 0; d < nlit.size(); d++) {
								//TODO allow identifiers be assiend to identifiers.
								//We can assume that every thing here is a literal for now.
								nlit[d]->SetFilePosition(m_fileCursor);
								m_fileCursor += sizeof(int);
								uint32_t literalS = htonl(atoi(nlit[d]->GetLiteral().c_str()));
								WriteBytes(stream, (unsigned char *)&literalS, sizeof(int));
							}
						}
					}
				}

				if (nodes[i]->GetType() == ASTNodeType::AST_Function_Declaration) {
					//TODO this should call this function recursivly.
					//This is as function
					if (nodes[i]->GetNodes()[0]->GetType() == ASTNodeType::AST_Function_Identifier) {
						if (strcmp(nodes[i]->GetNodes()[0]->GetLiteral().c_str(), "main") == 0) {
							if (hasMain) {
								//TODO Error Message
							}
							else {
								hasMain = true;
							}

							//m_fileCursor += sizeof(long);
							//This is a test to make sure we have pasred the right shit.
							assert(nodes[i]->GetNodes()[0]->GetNodes().size() == 1);
							ASTNode * block = nodes[i]->GetNodes()[0]->GetNodes()[0];
							assert(block->GetType() == ASTNodeType::AST_Block_Statement);
							std::vector<ASTNode*> blockNodes = block->GetNodes();
							//This should maybe be created on the stack.
								for (size_t r = 0; r < blockNodes.size(); r++) {

									if (blockNodes[r]->GetType() == ASTNodeType::AST_Variable_Declaration) {
										unsigned int ret = WriteVeriable(stream, blockNodes[r]);
										if (ret == 0) {
											//TODO Error Message not able to write var.
										}
										else  {
											m_fileCursor += ret;
										}
									}

								//This is where we parse the block to turn into byte code.
									if (blockNodes[r]->GetType() == ASTNodeType::AST_Return_Statement) {
										//start data is where the main begines + the size of its own header.
										startData = m_fileCursor;
										//stream.seekp(0);
										//WriteBytes(stream, (unsigned char*)&startData, sizeof(long));
										stream.seekp(m_fileCursor);

										//each block can only have one return statment.
										//write a return statment to file.
										char * op = nullptr;//new char[sizeof(char) + sizeof(char) + sizeof(int) + sizeof(char)];
										if (blockNodes[r]->GetNodes().size()) {
											unsigned int size = sizeof(char) + sizeof(char) + sizeof(char) + sizeof(int);
											//op = new char[size];

											for (size_t f = 0; f < blockNodes[r]->GetNodes().size(); f++) {
												if (blockNodes[r]->GetNodes()[f]->GetType() == ASTNodeType::AST_Identifier) {
													//Find the deleration of the var
													/*
													ASTNode* tempNode = blockNodes[r]->GetNodes()[f]->GetPerent();
													while (tempNode != nullptr) {
														for (size_t dsds = 0; dsds < tempNode->GetNodes().size(); dsds++){
															if (tempNode->GetNodes()[dsds]->GetType() == ASTNodeType::AST_Variable_Declaration) {
																for (size_t vid = 0; vid < tempNode->GetNodes()[dsds]->GetNodes().size(); vid++) {
																	ASTNode * stdfsafs = tempNode->GetNodes()[vid];
																	for (size_t dsa = 0; dsa < stdfsafs->GetNodes().size(); dsa++) {
																		if (stdfsafs->GetNodes()[dsa]->GetType() == ASTNodeType::AST_Variable_Identifier) {
																			if (stdfsafs->GetNodes()[dsa]->GetLiteral() == blockNodes[r]->GetNodes()[f]->GetLiteral()) {
																				//
																				std::cout << "Using Variable: " << stdfsafs->GetNodes()[dsa]->GetLiteral() << "\n";
																				std::cout << "At Position: " << stdfsafs->GetFilePosition() << "\n";
																				op = new char[size];
																				*op = CPU_OP_CODE::MOVE_MEM_TO_REG;
																				*(int*)(op + 1) = stdfsafs->GetFilePosition();
																				*(op + 5) = VAL_TYPE::VAL;
																				*(op + 6) = CPU_REG_NUM::RA_NUM;
																				WriteBytes(stream, (unsigned char*)op, size);
																				m_fileCursor += size;
																			}
																		}
																	}
																}
															}
														}
														tempNode = tempNode->GetPerent();
													}
													*/
													m_fileCursor += WriteReturnVariable(stream, blockNodes[r]->GetNodes()[f]->GetPerent(), blockNodes[r]->GetNodes()[f]);

												}
												else {
													size = WriteReturn(stream, blockNodes[r]);

													m_fileCursor += size;
												}
											}


											/*
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
											*/
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
	}

private:
	ASTNode * p_root = nullptr; //!< The start of the AST.
	unsigned int m_fileCursor = 0; //!< Where we are currently looking in the opened file.
};

#endif //AST_H