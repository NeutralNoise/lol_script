#ifndef Tokenizer_H_INCLUDE
#define Tokenizer_H_INCLUDE
#include "Token.h"
#include <vector>
#include <iostream>

/** 
 * \class Tokenizer
 * \brief Checks strings for tokens.
 * 
*/

class Tokenizer
{
public:

	/**
	 * \brief Construct a new Tokenizer object
	 * 
	*/

	Tokenizer();

	/**
	 * \brief Destroy the Tokenizer object
	 * 
	*/

	~Tokenizer();
	

	//Why is this here.....

	/**
	 * \brief Looks for a token in the given string.
	 * 
	 * \param str The string to look for the token in.
	 * \param line The current line within the file.
	 * \param pos The position in the line.
	 * \return Token
	*/

	Token nextToken(std::string *str, const int &line, const int pos) {
		if (m_pushBack) {
			m_pushBack = false;
			return m_lastToken;
		}

		if (str->empty()) {
			m_lastToken = Token("", TokenType::NONE);
			return m_lastToken;
		}
		Token rtn;
		for (size_t i = 0; i < m_pattenData.size(); i++) {
			rtn = m_pattenData[i].CheckToken(*str);
			if (rtn.GetType() != TokenType::NONE) {
				break;
			}
		}

		if (rtn.GetType() == TokenType::NONE) {
			return Token();
		}

		//Do a little bit of processing here.
		if (rtn.token.size() + 1 <= str->size()) {
			
		}

		str->erase(str->begin(), str->begin() + rtn.token.size());

		rtn.line = line;
		rtn.linePos = pos;

		m_lastToken = rtn;

		return rtn;
	}


private:
	std::vector<TokenData> m_pattenData; //!< Tokens to look for.
	Token m_lastToken; //!< The last token that was found.
	bool m_pushBack; //!< What?

};



#endif