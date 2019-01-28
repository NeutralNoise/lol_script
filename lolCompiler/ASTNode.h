#ifndef AST_NODE_H
#define AST_NODE_H
#include <vector>
#include "Token.h"

#define PRINT_NODES

#ifdef PRINT_NODES 
#include <iostream>
#endif //PRINT_NODES


enum ASTNodeType {
	AST_Program,
	AST_Variable_Declaration,
	AST_Variable_Declarator,
	AST_Function_Declaration,
	AST_Block_Statement,
	AST_Return_Statement,
	AST_Binary_Expression,
	AST_Identifier,
	AST_Variable_Identifier,
	AST_Function_Identifier,
	AST_Literal,
	AST_Call_Expression,
	AST_Arguments
};

class ASTNode
{
public:
	ASTNode() { p_perent = nullptr; }
	~ASTNode() { }
	
	ASTNode * GetPerent() { return  p_perent; }
	void SetPerent(ASTNode * perent) { this->p_perent = perent; }

	const int &GetType() { return m_type; }
	void SetType(const int &type) { this->m_type = type; }

	void AddNode(ASTNode * node) { node->p_perent = this; m_nodes.push_back(node); }
	const std::vector<ASTNode*> &GetNodes() { return m_nodes; }

	void SetToken(const Token &tok) { m_tok = tok; }
	const Token &GetToken() { return m_tok; }

	void SetLiteral(const std::string &lit) { m_literal = lit; }
	const std::string &GetLiteral() { return m_literal; }

	void Clean() {
		for (size_t i = 0; i < m_nodes.size(); i++) {
			m_nodes[i]->Clean();
			delete m_nodes[i];
		}
	}

	void SetFilePosition(const unsigned int &pos) { m_filePosition = pos; }

	const unsigned int &GetFilePosition() { return m_filePosition; }

#ifdef PRINT_NODES 
	void PrintNodes() {
		for (size_t i = 0; i < m_nodes.size(); i++) {
			std::cout << m_nodes[i]->GetLiteral() << '\n';
			m_nodes[i]->PrintNodes();
		}
	}
#endif

private:
	ASTNode * p_perent;
	Token m_tok;
	std::string m_literal;
	std::vector<ASTNode*> m_nodes;
	int m_type;
	unsigned int m_filePosition;
};

#endif //AST_NODE_H
