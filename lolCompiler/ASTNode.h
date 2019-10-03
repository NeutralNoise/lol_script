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

/**
 * \class ASTNode
 * \brief Defines a node for the AST
 * 
*/

class ASTNode
{
public:

	/**
	 * \brief Construct a new ASTNode object
	 * 
	*/

	ASTNode() { p_perent = nullptr; }

	/**
	 * \brief Destroy the ASTNode object
	 * 
	*/

	~ASTNode() { }
	
	/**
	 * \brief Get the Perent object
	 * 
	 * \return ASTNode* 
	*/

	ASTNode * GetPerent() { return  p_perent; }

	/**
	 * \brief Set the Perent object
	 * 
	 * \param perent The node that should be this nodes perent.
	*/

	void SetPerent(ASTNode * perent) { this->p_perent = perent; }

	/**
	 * \brief Get the Type of node this is.
	 * 
	 * \return const int& \see ASTNodeType
	*/

	const int &GetType() { return m_type; }

	/**
	 * \brief Set the Type of this node
	 * 
	 * \param type This nodes type. \see ASTNodeType
	*/

	void SetType(const int &type) { this->m_type = type; }

	/**
	 * \brief Add a node to this node.
	 * 
	 * \param node The node to add.
	*/

	void AddNode(ASTNode * node) { node->p_perent = this; m_nodes.push_back(node); }

	/**
	 * \brief Get the Nodes connected to this node.
	 * 
	 * \return const std::vector<ASTNode*>& 
	*/

	const std::vector<ASTNode*> &GetNodes() { return m_nodes; }

	/**
	 * \brief Set the Token object
	 * 
	 * \param tok The token to set.
	*/

	void SetToken(const Token &tok) { m_tok = tok; }

	/**
	 * \brief Get the Token object
	 * 
	 * \return const Token& 
	*/

	const Token &GetToken() { return m_tok; }

	/**
	 * \brief Set the string literal of this node.
	 * 
	 * \param lit The string to set as the literal.
	*/

	void SetLiteral(const std::string &lit) { m_literal = lit; }

	/**
	 * \brief Get the string literal of this node.
	 * 
	 * \return const std::string& 
	*/

	const std::string &GetLiteral() { return m_literal; }

	/**
	 * \brief Clean up any pointers.
	 * \note only use once you are done with the AST.
	*/

	void Clean() {
		for (size_t i = 0; i < m_nodes.size(); i++) {
			m_nodes[i]->Clean();
			delete m_nodes[i];
		}
	}

	/**
	 * \brief Set the position in the file this node is at.
	 * 
	 * \param pos The position to set.
	*/

	void SetFilePosition(const unsigned int &pos) { m_filePosition = pos; }

	/**
	 * \brief Get this node file position.
	 * 
	 * \return const unsigned int& 
	*/

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
	ASTNode * p_perent; //!< Where this node connects to the tree.
	Token m_tok; //!< The Token that makes up this node. \see Token
	std::string m_literal; //!< The string of this Node.
	std::vector<ASTNode*> m_nodes; //!< More node that are within this node. Used in funcs?
	int m_type; //!< The type of node this is. \see ASTNodeType
	unsigned int m_filePosition; //!< Where in the file this node starts.
};

#endif //AST_NODE_H
