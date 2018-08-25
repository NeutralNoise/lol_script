#include "Parsers.h"
#include "ASTNode.h"
#include "Token.h"
#include "ParseTokens.h"


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
					
					block->SetLiteral(blockLit);
					//TODO parse a block statement
					ParseTokens parser;
					std::vector<Token> blockToks = *toks;
					blockToks.erase(blockToks.begin(), blockToks.begin() + i);
					parser.Parse(blockToks, block);
					i += parser.m_tokPos;
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

bool ShouldParseVar(const std::vector<Token> &toks) {
	if (toks.size() == 0) {
		return false;
	}
	size_t skip = 0;
	SkipWhiteSpace(&skip, toks);
	for (size_t i = skip; i < toks.size(); i++) {
		if (toks[i].GetType() == TokenType::KEYWORD) {
			SkipWhiteSpace(&i, toks);
			if (toks[i].GetType() == TokenType::IDENTIFIER) {
				SkipWhiteSpace(&i, toks);
				if (toks[i].GetType() == TokenType::SEMI_COLON || toks[i].GetType() == TokenType::ASSIGN) {
					return true;
				}
				else {
					//TODO error message
					return false;
				}
			}
			else {
				return false;
			}
		}
		return false;
	}
	
	return false;
}

extern bool ParseVarible(std::vector<Token> * toks, ASTNode * ast) {

	if (ShouldParseVar(*toks)) {
		size_t skip = 0;
		SkipWhiteSpace(&skip, *toks);
		for (size_t i = skip; i < toks->size(); i++) {
			if ((*toks)[i].GetType() == TokenType::KEYWORD) {

				ASTNode* varDecl = new ASTNode;
				varDecl->SetType(ASTNodeType::AST_Variable_Declaration);
				varDecl->SetToken(toks->operator[](i));
				varDecl->SetLiteral(toks->operator[](i).GetToken());
				SkipWhiteSpace(&i, *toks);

				if ((*toks)[i].GetType() == TokenType::IDENTIFIER) {

					ASTNode * ident = new ASTNode;
					ident->SetType(ASTNodeType::AST_Variable_Identifier);
					varDecl->SetToken(toks->operator[](i));
					varDecl->SetLiteral(toks->operator[](i).GetToken());
					SkipWhiteSpace(&i, *toks);

					//Check if this is the end or if we have some more work todo.

					if ((*toks)[i].GetType() == TokenType::SEMI_COLON || (*toks)[i].GetType() == TokenType::ASSIGN) {
						if ((*toks)[i].GetType() == TokenType::SEMI_COLON) {
							std::string lit;
							size_t start = skip + 1;
							SkipWhiteSpace(&start, *toks);
							for (size_t r = start; r <= i; r++) {
								lit += toks->operator[](r).GetToken();
							}

							ASTNode * var = new ASTNode;
							var->SetType(ASTNodeType::AST_Variable_Declarator);
							var->SetLiteral(lit);
							var->AddNode(ident);

							varDecl->AddNode(var);
							ast->AddNode(varDecl);
							toks->erase(toks->begin(), toks->begin() + i);
							return true;
						}
						//TODO += -= *= /= <<= >>=
						else if ((*toks)[i].GetType() == TokenType::ASSIGN) {
							SkipWhiteSpace(&i, *toks);
							if ((*toks)[i].GetType() == TokenType::CHAR_LITERAL || (*toks)[i].GetType() == TokenType::INTEGER_LITERAL) {
								SkipWhiteSpace(&i, *toks);
								if ((*toks)[i].GetType() == TokenType::SEMI_COLON) {
									ASTNode* varDecl = new ASTNode;
									varDecl->SetType(ASTNodeType::AST_Variable_Declaration);
									ASTNode * var = new ASTNode;
									var->SetType(ASTNodeType::AST_Variable_Declarator);
									varDecl->AddNode(var);
									ASTNode * lit = new ASTNode;
									ident->SetType(ASTNodeType::AST_Variable_Identifier);
									lit->SetType(ASTNodeType::AST_Literal);
									var->AddNode(ident);
									var->AddNode(lit);
									toks->erase(toks->begin(), toks->begin() + i);
									return true;
								}
								else {
									//TODO error message
								}
							}
							else if ((*toks)[i].GetType() == TokenType::IDENTIFIER) {
								ASTNode* varDecl = new ASTNode;
								varDecl->SetType(ASTNodeType::AST_Variable_Declaration);
								ASTNode * var = new ASTNode;
								var->SetType(ASTNodeType::AST_Variable_Declarator);
								varDecl->AddNode(var);
								ASTNode * lit = new ASTNode;
								ident->SetType(ASTNodeType::AST_Variable_Identifier);
								lit->SetType(ASTNodeType::AST_Identifier);
								var->AddNode(ident);
								var->AddNode(lit);
								toks->erase(toks->begin(), toks->begin() + i);
								return true;
							}
						}
					}
					delete ident;
				}
				delete varDecl;
			}
		}
	}

	return false;
}

extern bool ShouldParseReturn(const std::vector<Token> &toks) {
	if (toks.size() <= 0) {
		return false;
	}

	size_t skip = 0;
	SkipWhiteSpace(&skip, toks);

	if (toks[skip].GetType() == TokenType::KEYWORD) {
		if (strcmp(toks[skip].GetToken().c_str(), "return") == 0) {
			return true;
		}
	}
	return false;
}

extern bool ParseReturn(std::vector<Token> * toks, ASTNode * ast) {
	if (ShouldParseReturn(*toks)) {
		size_t skip = 0;
		SkipWhiteSpace(&skip, *toks);

		std::string lit;
		//Get the literal;
		for (size_t i = skip; i < toks->size(); i++) {
			if (toks->operator[](i).GetType() == TokenType::SEMI_COLON) {
				lit += toks->operator[](i).GetToken();
				break;
			}
			else {
				lit += toks->operator[](i).GetToken();
			}
		}

		ASTNode * statement = new ASTNode;
		statement->SetType(ASTNodeType::AST_Return_Statement);
		statement->SetLiteral(lit);
		skip++;
		SkipWhiteSpace(&skip, *toks);
		if (toks->operator[](skip).GetType() == TokenType::CHAR_LITERAL || toks->operator[](skip).GetType() == TokenType::INTEGER_LITERAL) {
			ASTNode * ident = new ASTNode;
			ident->SetType(ASTNodeType::AST_Literal);
			ident->SetToken(toks->operator[](skip));
			ident->SetLiteral(toks->operator[](skip).GetToken());
			statement->AddNode(ident);
		}
		else if (toks->operator[](skip).GetType() == TokenType::IDENTIFIER) {
			ASTNode * ident = new ASTNode;
			ident->SetType(ASTNodeType::AST_Identifier);
			ident->SetToken(toks->operator[](skip));
			ident->SetLiteral(toks->operator[](skip).GetToken());
			statement->AddNode(ident);
		}
		else {
			//TODO error checking
		}

		skip++;
		SkipWhiteSpace(&skip, *toks);
		if (toks->operator[](skip).GetType() == TokenType::SEMI_COLON) {
			ast->AddNode(statement);
			toks->erase(toks->begin(), toks->begin() + skip);
			return true;
		}
		else {
			//TODO error checking
		}
		
	}
	return false;
}