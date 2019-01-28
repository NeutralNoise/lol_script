#include "ASTWriter.h"
#include "ASTNode.h"
#include "../Common/cpuEnums.h"
#include "AST.h"

bool CheckVeriableIsReal(ASTNode * perent, unsigned int *nodePos, unsigned int *identPos) {

	//Find the memory position of the identifer well check to make sure its real.
	ASTNode * node = perent->GetPerent();
	unsigned int identpos = 0, nodep = 0;
	bool foundSelf = false; //Its the first.
	while (1) {
		if (node == nullptr) {
			//we have reached the top.
			//TODO Error there is no identifer with this name
			break;
		}

		std::vector<ASTNode*> n = node->GetNodes();
		for (size_t t = 0; t < n.size(); t++) {
			//We don't wanna go past here because its the same one as this one. so just go up to the next level.
			if (perent == n[t]) {
				foundSelf = true;
				break;
			}

			if (n[t]->GetType() == ASTNodeType::AST_Variable_Declaration) {
				for (size_t r = 0; r < n[t]->GetNodes().size(); r++) {
					ASTNode* in = n[t]->GetNodes()[r];
					if (in->GetType() == ASTNodeType::AST_Variable_Identifier) {
						//For when we have more then 1 veriable decleared.
						for (size_t g = 0; g < perent->GetNodes().size(); g++) {
							if (in->GetLiteral() == perent->GetNodes()[g]->GetLiteral()) {
								*nodePos = t;
								*identPos = r;
								return true;
							}
						}
					}
				}
			}

		}
		node = node->GetPerent();
	}
	return foundSelf;
}

unsigned int WriteReturn(std::ofstream &stream, ASTNode * perent) {
	//OP code + reg + data/ident + hlt code
	const unsigned int size = sizeof(char) + sizeof(char) + sizeof(int); // +sizeof(char);
	//OP code + reg + valtype + data/ident
	const unsigned int identsize = sizeof(char) + sizeof(char) + sizeof(char) + sizeof(int);
	char * op = nullptr; //new char[size];

	if (perent->GetNodes().size()) {
		std::vector<ASTNode*> nodes = perent->GetNodes();
		for (size_t i = 0; i < nodes.size(); i++) {
			//TODO allow so we can call functions and do other things in return statements.
			if (nodes[i]->GetType() == ASTNodeType::AST_Literal) {
				op = new char[size];
				*op = CPU_OP_CODE::MOVE_CON_TO_REG;
				*(op + 1) = (char)CPU_REG_NUM::RA_NUM;

				//Check if we have a interger literal.
				if (nodes[i]->GetToken().GetType() == TokenType::INTEGER_LITERAL) {
					char * pend;
					*(long*)(op + 2) = strtol(nodes[i]->GetToken().GetToken().c_str(), &pend, 10);
					WriteBytes(stream, (unsigned char*)op, size);
					return size;
				}
				else if (nodes[i]->GetToken().GetType() == TokenType::CHAR_LITERAL) {

				}
				else {
					//TODO error unknown literal.
				}
				return size;
			}
			else if (nodes[i]->GetType() == ASTNodeType::AST_Identifier) {
				//Find the memory position of the identifer well check to make sure its real.
				ASTNode * node = nodes[i]->GetPerent();
				unsigned int identpos = 0, nodep = 0;
				bool foundIdent = false;
				while (1) {
					if (node == nullptr) {
						//we have reached the top.
						//TODO Error Error there is no identifer with this name
						break;
					}

					std::vector<ASTNode*> n = node->GetNodes();
					for (size_t t = 0; t < n.size(); t++) {
						//We don't wanna go past here because its the same one as this one. so just go up to the next level.
						if (nodes[i] == n[t]) {
							break;
						}

						if (n[t]->GetType() == ASTNodeType::AST_Variable_Declaration) {
							for (size_t r = 0; r < n[t]->GetNodes().size(); r++) {
								ASTNode* in = n[t]->GetNodes()[r];
								if (in->GetType() == ASTNodeType::AST_Variable_Identifier) {

									if (in->GetLiteral() == nodes[i]->GetLiteral()) {
										foundIdent = true;
										nodep = t;
										identpos = r;
										break;
									}
								}
							}
							if (foundIdent) {
								break;
							}
						}

					}
					if (foundIdent) {
						break;
					}
					node = node->GetPerent();
				}
				if (foundIdent) {
					//TODO these need to be improved to allow ptrs and shit like that.
					op = new char[identsize];
					*op = CPU_OP_CODE::MOVE_MEM_TO_REG;
					*(long*)(op + 1) = htonl(node->GetNodes()[nodep]->GetFilePosition());
					*(op + 5) = (char)VAL_TYPE::VAL;
					*(op + 6) = (char)CPU_REG_NUM::RA_NUM;
					//*(long*)(op + 3) = node->GetNodes()[nodep]->GetNodes()[identpos]->GetFilePosition();
					WriteBytes(stream, (unsigned char*)op, identsize);
					return identsize;
				}
			}
			else {
				//Unknown return type.
				//TODO error message of unknown return type.
			}
		}
	}
	else {

	}
	return 0;
}

unsigned int WriteVeriable(std::ofstream &stream, ASTNode * perent) {
	unsigned int np;
	unsigned int ip;
	if (CheckVeriableIsReal(perent, &np, &ip)) {
		perent->SetFilePosition(stream.tellp());
		for (size_t i = 0; i < perent->GetNodes().size(); i++) {
			for (size_t r = 0; r < perent->GetNodes()[i]->GetNodes().size(); r++) {
				ASTNode * t = perent->GetNodes()[i]->GetNodes()[r];
				if (t->GetType() == ASTNodeType::AST_Literal) {
					uint32_t literalS = htonl(atoi(t->GetLiteral().c_str()));
					WriteBytes(stream, (unsigned char *)&literalS, sizeof(int));
					return sizeof(int);
				}
			}
		}
	}
	return 0;
}

unsigned int WriteReturnVariable(std::ofstream &stream, ASTNode * perent, ASTNode * node) {
	//TODO this should be done else where
	size_t size = sizeof(char) + sizeof(char) + sizeof(char) + sizeof(int);
	unsigned char * op = nullptr;
	ASTNode* tempNode = perent;
	while (tempNode != nullptr) {
		for (size_t dsds = 0; dsds < tempNode->GetNodes().size(); dsds++){
			if (tempNode->GetNodes()[dsds]->GetType() == ASTNodeType::AST_Variable_Declaration) {
				for (size_t vid = 0; vid < tempNode->GetNodes()[dsds]->GetNodes().size(); vid++) {
					ASTNode * stdfsafs = tempNode->GetNodes()[vid];
					for (size_t dsa = 0; dsa < stdfsafs->GetNodes().size(); dsa++) {
						if (stdfsafs->GetNodes()[dsa]->GetType() == ASTNodeType::AST_Variable_Identifier) {
							if (stdfsafs->GetNodes()[dsa]->GetLiteral() == node->GetLiteral()) {
								//
								std::cout << "Using Variable: " << stdfsafs->GetNodes()[dsa]->GetLiteral() << "\n";
								std::cout << "At Position: " << stdfsafs->GetFilePosition() << "\n";
								op = new unsigned char[size];
								*op = CPU_OP_CODE::MOVE_MEM_TO_REG;
								*(int*)(op + 1) = stdfsafs->GetFilePosition();
								*(op + 5) = VAL_TYPE::VAL;
								*(op + 6) = CPU_REG_NUM::RA_NUM;
								WriteBytes(stream, (unsigned char*)op, size);
								//TODO Jump to where this function was called from.
								return size;
							}
						}
					}
				}
			}
		}
		tempNode = tempNode->GetPerent();
	}
		return 0;
}