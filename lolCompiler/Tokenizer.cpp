#include "Tokenizer.h"


Tokenizer::Tokenizer()
{


	m_pattenData.push_back(TokenData("^(_?)*([a-zA-Z][a-zA-Z0-9]*)", TokenType::IDENTIFIER));
	m_pattenData.push_back(TokenData(R"(^((-)?[0-9]+))", TokenType::INTEGER_LITERAL));
	m_pattenData.push_back(TokenData("^(\".*\")", TokenType::STRING_LITERAL));
	m_pattenData.push_back(TokenData("^(\'.*\')", TokenType::CHAR_LITERAL));
	m_pattenData.push_back(TokenData("^(\\+\\+)", TokenType::INCRAMENT));
	m_pattenData.push_back(TokenData("^(\\-\\-)", TokenType::DECRAMENT));
	m_pattenData.push_back(TokenData("^(==)", TokenType::EQUAL_EQUAL_OPERATOR));
	m_pattenData.push_back(TokenData("^(!=)", TokenType::NOT_EQUAL_OPERATOR));
	m_pattenData.push_back(TokenData("^(>=)", TokenType::GRATER_THAN));
	m_pattenData.push_back(TokenData("^(<=)", TokenType::LESS_THAN));
	m_pattenData.push_back(TokenData("^(\\|\\|)", TokenType::OR_OR_OPERATOR));
	m_pattenData.push_back(TokenData("^(&&)", TokenType::AND_AND_OPERATOR));
	m_pattenData.push_back(TokenData("^(->)", TokenType::ARROW));
	m_pattenData.push_back(TokenData("^(\\()", TokenType::LEFT_BRACET));
	m_pattenData.push_back(TokenData("^(\\))", TokenType::RIGHT_BRACET));
	m_pattenData.push_back(TokenData("^(\\{)", TokenType::LEFT_CURLY_BRACET));
	m_pattenData.push_back(TokenData("^(\\})", TokenType::RIGHT_CURLY_BRACET));
	m_pattenData.push_back(TokenData("^(\\[)", TokenType::LEFT_BRACE));
	m_pattenData.push_back(TokenData("^(\\])", TokenType::RIGHT_BRACE));
	m_pattenData.push_back(TokenData("^(;)", TokenType::SEMI_COLON));
	m_pattenData.push_back(TokenData("^(:)", TokenType::COLON));
	m_pattenData.push_back(TokenData("^(\\+)", TokenType::PLUS_OPERATOR));
	m_pattenData.push_back(TokenData("^(\\-)", TokenType::MINUS_OPERATOR));
	m_pattenData.push_back(TokenData("^(\\/)", TokenType::DEVIDE_OPERATOR));
	m_pattenData.push_back(TokenData("^(<<)", TokenType::SHIFT_LEFT_OPERATOR));
	m_pattenData.push_back(TokenData("^(>>)", TokenType::SHIFT_RIGHT_OPERATOR));
	m_pattenData.push_back(TokenData("^(&)", TokenType::AND_OPERATOR));
	m_pattenData.push_back(TokenData("^(\\|)", TokenType::OR_OPERATOR));
	m_pattenData.push_back(TokenData("^(\\.)", TokenType::DOT));
	m_pattenData.push_back(TokenData("^(\\%)", TokenType::MOD_OPERATOR));
	m_pattenData.push_back(TokenData("^(!)", TokenType::NOT_OPERATOR));
	m_pattenData.push_back(TokenData("^(\\^)", TokenType::XOR_OPERATOR));
	m_pattenData.push_back(TokenData("^(#)", TokenType::HASH));
	m_pattenData.push_back(TokenData("^(=)", TokenType::ASSIGN));
	m_pattenData.push_back(TokenData("^(\\?)", TokenType::QUESTION_MARK));
	m_pattenData.push_back(TokenData(R"(^( ?|\t?|\n?|\r)*)", TokenType::WHITE_SPACE));


	m_pushBack = false;

}


Tokenizer::~Tokenizer()
{
}
