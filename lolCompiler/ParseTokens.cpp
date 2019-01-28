#include "ParseTokens.h"
#include "Parsers.h"
#include "AST.h"

ParseTokens::ParseTokens()
{
	m_tokPos = 0;
}


ParseTokens::~ParseTokens()
{
}

void ParseTokens::Parse(const std::vector<Token> &tokens, AST * ast) {
	//This is where we parse the different blocks into the ast
	ASTNode * root = ast->GetRoot();

	for (m_tokPos = 0; m_tokPos < tokens.size(); m_tokPos++) {
		//Parse the tokens
		if (tokens[m_tokPos].GetType() == TokenType::KEYWORD) {
			
			Parse(tokens, root);
		}
	}

}

void ParseTokens::Parse(const std::vector<Token> &tokens, ASTNode * perent) {
	SkipWhiteSpace((size_t*)(&m_tokPos), tokens);
	//This is where we parse the different blocks into the ast
	if (tokens[m_tokPos].GetType() == TokenType::KEYWORD) {
		//Make sure we are pointing to the right part of the tokens.
		std::vector<Token> tok = tokens;
		tok.erase(tok.begin(), tok.begin() + m_tokPos);
		//TODO check for verible decl
		//TODO check for keywords like return and sizeof

		//Check if return statement.
		if (ParseReturn(&tok, perent)) {
			if (tok.size() < tokens.size()) {
				size_t dif = tokens.size() - tok.size();
				std::vector<Token> tmpTok = tokens;
				tmpTok.erase(tmpTok.begin(), tmpTok.begin() + m_tokPos);
				size_t dif2 = tokens.size() - tmpTok.size();
				if (dif != dif2) {
					m_tokPos += dif;
				}
			}
			return;
		}

		if (ParseVarible(&tok, perent)) {
			if (tok.size() < tokens.size()) {
				size_t dif = tokens.size() - tok.size();
				std::vector<Token> tmpTok = tokens;
				tmpTok.erase(tmpTok.begin(), tmpTok.begin() + m_tokPos);
				size_t dif2 = tokens.size() - tmpTok.size();
				if (dif != dif2) {
					m_tokPos += dif;
				}
			}
			return;
		}
		
		//Check if we are a function
		if (ParseFuntions(&tok, perent)) {
			//Get the difference.
			if (tok.size() < tokens.size()) {
				size_t dif = tokens.size() - tok.size();
				std::vector<Token> tmpTok = tokens;
				tmpTok.erase(tmpTok.begin(), tmpTok.begin() + m_tokPos);
				size_t dif2 = tokens.size() - tmpTok.size();
				if (dif != dif2) {
					m_tokPos += dif;
				}
			}
			return;
		}
	}
	else if (tokens[m_tokPos].GetType() == TokenType::LEFT_CURLY_BRACET) {
		// skip the curly (ew).
		m_tokPos++;
		SkipWhiteSpace((size_t*)&m_tokPos, tokens);
		//pares a block.
		Parse(tokens, perent);
		return;
	}


}