#ifndef Tokenizer_H_INCLUDE
#define Tokenizer_H_INCLUDE
#include "Token.h"
#include <vector>
#include <iostream>
class Tokenizer
{
public:
	Tokenizer();
	~Tokenizer();
	

	//Why is this here.....
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
		/*
		size_t spacepos = str->find_first_of(" ");

		if (spacepos == std::string::npos) {
			str->erase(str->begin(), str->begin() + rtn.token.size());
		}
		else {
			//Make sure there is a space after last token.
			//If not then only remove up untill the next token.
			if (spacepos > (rtn.token.size() + 1)) {
				str->erase(str->begin(), str->begin() + rtn.token.size());
			}
			else {
				str->erase(str->begin(), str->begin() + rtn.token.size() + 1);
			}
		}
		*/
		rtn.line = line;
		rtn.linePos = pos;

		m_lastToken = rtn;

		return rtn;
	}


private:
	std::vector<TokenData> m_pattenData;
	Token m_lastToken;
	bool m_pushBack;

};



#endif