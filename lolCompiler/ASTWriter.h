#ifndef AST_WRITER_H
#define AST_WRITER_H
#include <fstream>
class ASTNode;

extern bool CheckVeriableIsReal(ASTNode * perent, unsigned int *nodePos, unsigned int *identPos);

extern unsigned int WriteReturn(std::ofstream &stream, ASTNode * perent);

extern unsigned int WriteVeriable(std::ofstream &stream, ASTNode * perent);

extern unsigned int WriteReturnVariable(std::ofstream &stream, ASTNode * perent, ASTNode * node);

#endif //AST_WRITER_H