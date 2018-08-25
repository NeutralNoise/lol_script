#ifndef PARSE_TOKENS_H
#define PARSE_TOKENS_H
#include <vector>
#include "Token.h"

class AST; // just so we can get this moving
class ASTNode;

class ParseTokens
{
public:
	ParseTokens();
	~ParseTokens();

	void Parse(const std::vector<Token> &tokens, AST * ast);
	void Parse(const std::vector<Token> &tokens, ASTNode * perent);

//private:
	unsigned int m_tokPos;
};


#endif //PARSE_TOKENS_H
