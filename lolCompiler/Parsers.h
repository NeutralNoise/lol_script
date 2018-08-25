#ifndef PARSERS_H
#define PARSERS_H
#include <vector>

class ASTNode;
struct Token;

extern bool ShouldParseFunc(const std::vector<Token> &toks);

extern bool ParseFuntions(std::vector<Token> * toks, ASTNode * ast);


#endif //PARSERS_H