#ifndef PARSERS_H
#define PARSERS_H
#include <vector>
#include "Token.h"

class ASTNode;

//skip white space.
inline void SkipWhiteSpace(unsigned int * i, const std::vector<Token> &toks) {
	while (toks[*i].GetType() == TokenType::WHITE_SPACE) {
		*i += 1;
	}
}

extern bool ShouldParseFunc(const std::vector<Token> &toks);

extern bool ParseFuntions(std::vector<Token> * toks, ASTNode * ast);

extern bool ShouldParseVar(const std::vector<Token> &toks);

extern bool ParseVarible(std::vector<Token> * toks, ASTNode * ast);

extern bool ShouldParseReturn(const std::vector<Token> &toks);

extern bool ParseReturn(std::vector<Token> * toks, ASTNode * ast);

#endif //PARSERS_H