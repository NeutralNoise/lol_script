#include "Parsers.h"
#include "ASTNode.h"
#include "Token.h"
#include "ParseTokens.h"

//skip white space.
void SkipWhiteSpace(size_t * i, const std::vector<Token> &toks) {
	while (toks[*i].GetType() == TokenType::WHITE_SPACE) {
		*i += 1;
	}
}


bool ShouldParseFunc(const std::vector<Token> &toks) {
		for (size_t i = 0; i < toks.size(); i++) {
			if (toks[i].GetType() == TokenType::KEYWORD) {
				i++;
				SkipWhiteSpace(&i, toks);
				//TODO check to make sure the right thing is being returned and not struct or sizeof
				if (toks[i].GetType() == TokenType::IDENTIFIER) {
					i++;
					SkipWhiteSpace(&i, toks);
					if (toks[i].GetType() == TokenType::LEFT_BRACET) {
						i++;
						SkipWhiteSpace(&i, toks);
						if (toks[i].GetType() == TokenType::CHAR_LITERAL || toks[i].GetType() == TokenType::INTEGER_LITERAL || toks[i].GetType() == TokenType::IDENTIFIER) {
							//We are calling a constructor
							return false;
						}
						if (toks[i].GetType() == TokenType::RIGHT_BRACET) {
							//TODO we chould still be calling a constructor
							//We will just say that we are defining a function now.
							return true;
						}
						else {
							//TODO error message
							return false;
						}
					}
					else {
						//TODO error message
						return false;
					}
				}
				else {
					//TODO error message
					return false;
				}
				
			}
		}
		
	return false;
}

bool ParseFuntions(std::vector<Token> * toks, ASTNode * ast) {
	if (ast != nullptr) {
		//check if we should parse this as a function.
		if (ShouldParseFunc(*toks)) {
			ASTNode * newNode = new ASTNode;
			newNode->SetType(ASTNodeType::AST_Function_Declaration);
			

			for (size_t i = 0; i < toks->size(); i++) {
				if (toks->operator[](i).GetType() == TokenType::KEYWORD) {
					//We will only store the start token.
					//TODO Nodes can have more then one token pls
					newNode->SetToken(toks->operator[](i));
					std::string lit = toks->operator[](i).GetToken();
					for (size_t t = i + 1; toks->operator[](i).GetType() != TokenType::RIGHT_BRACET; t++) {
						lit += toks->operator[](t).GetToken();
						i = t;
					}
					//other wise we end up on the RIGHT_BRACET
					i++;
					newNode->SetLiteral(lit);
					ASTNode * block = new ASTNode;
					block->SetType(ASTNodeType::AST_Block_Statement);
					newNode->AddNode(block);
					//TODO nested blocks pls.
					i++;
					SkipWhiteSpace(&i, *toks);
					std::string blockLit = toks->operator[](i).GetToken();
					size_t end = 0;
					for (size_t t = i + 1; toks->operator[](t).GetType() != TokenType::RIGHT_CURLY_BRACET; t++) {
						blockLit += toks->operator[](t).GetToken();
						end = t + 1;
					}
					blockLit += toks->operator[](end).GetToken();
					
					i++;
					block->SetLiteral(blockLit);
					//TODO parse a block statement
					ParseTokens parser;
					std::vector<Token> blockToks = *toks;
					blockToks.erase(blockToks.begin(), blockToks.begin() + i);
					parser.Parse(blockToks, block);

					//Eat what we have used this is done at the end so the tokenizer knows where it is upto
					toks->erase(toks->begin(), toks->begin() + i);
					//Add the node to the perent node.
					ast->AddNode(newNode);
					return true;
				}
			}
		}
	}
	return false;
}