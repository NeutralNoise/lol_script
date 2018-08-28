#ifndef AST_PARSER_H
#define AST_PARSER_H
#include <fstream>
#include "ASTNode.h"

//class ASTNode;
//ASTParser

inline unsigned int ASTParseReturn(std::ifstream &stream, ASTNode * perent) {
	//Parse a return
	if (perent->GetType() == ASTNodeType::AST_Return_Statement) {
		//Detect what kind of return statement that we need.
		if (perent->GetNodes().size() == 1) {
			std::vector<ASTNode*> nodes = perent->GetNodes();
			for (size_t i = 0; i < nodes.size(); i++) {
				if (nodes[i]->GetType() == ASTNodeType::AST_Literal) {
					//TODO check for function calls
					if (nodes[i]->GetNodes()[0]->GetToken().GetType() == TokenType::INTEGER_LITERAL) {
						//WE have a const number returning
					}
					else if (nodes[i]->GetNodes()[0]->GetToken().GetType() == TokenType::CHAR_LITERAL) {
						//WE have a const char returning
					}
					else {
						//TODO Error message about wrong return val
					}
				}
				else if (nodes[i]->GetType() == ASTNodeType::AST_Identifier) {
					//Gotta find where this thing is saved.
					//Is it on the stack or is it in memory
				}
			}
		}
		else if (perent->GetNodes().size() > 1) {
			//TODO error message for now.
			//Will have to check for binary operations
		}
		else {
			//just write hlt at the moment. should just to next thing in calling function.
			//TODO jmp not hlt
		}

		char * op = new char[sizeof(char) + sizeof(char) + sizeof(int) + sizeof(char)];
		unsigned int size = sizeof(char) + sizeof(char) + sizeof(int) + sizeof(char);
	}
}



#endif //AST_PARSER_H