#ifndef AST_H
#define AST_H

#include "ASTNode.h"

class AST
{
public:
	AST() { if (p_root == nullptr) p_root = new ASTNode; }
	~AST() {}

	ASTNode * GetRoot() { return p_root; }
	void SetRoot(ASTNode * root){ p_root = root; }

	void AddNode(ASTNode * perent, ASTNode *node) { perent->AddNode(node); }


private:
	ASTNode * p_root = nullptr;
};

#endif //AST_H