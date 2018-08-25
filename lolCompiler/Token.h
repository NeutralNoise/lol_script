#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED
#include <string>
#include <regex>

enum TokenType {
	KEYWORD,	// void int float
	IDENTIFIER, // _testFunc();
	INTEGER_LITERAL, // 1231
	STRING_LITERAL, // " * "
	CHAR_LITERAL,  // 'd'
	LEFT_BRACET, // (
	RIGHT_BRACET, // )
	LEFT_CURLY_BRACET, // {
	RIGHT_CURLY_BRACET, // }
	LEFT_BRACE, // [
	RIGHT_BRACE, // ]
	SEMI_COLON,
	COLON,
	ARROW, // ->
	ASSIGN, // =
	PLUS_OPERATOR,
	MULTI_OPERATOR,
	DEVIDE_OPERATOR,
	MINUS_OPERATOR,
	SHIFT_LEFT_OPERATOR, //<<
	SHIFT_RIGHT_OPERATOR, //>>
	AND_OPERATOR,
	AND_AND_OPERATOR, // &&
	OR_OPERATOR,  // |
	OR_OR_OPERATOR,  // ||
	DOT,			// .
	MOD_OPERATOR, // %
	GRATER_THAN, // >=
	LESS_THAN,  // <=
	EQUAL_EQUAL_OPERATOR, // ==
	NOT_EQUAL_OPERATOR, // !=
	NOT_OPERATOR, // !
	XOR_OPERATOR, // ^
	QUESTION_MARK, // ?
	INCRAMENT, // ++
	DECRAMENT, // --
	HASH, // #
	WHITE_SPACE,
	_EOF = 999,

	NONE // Not a type
};

struct Token
{
	std::string token;
	TokenType type;
	int line;
	int linePos;

	Token() {
		line = 0;
		linePos = 0;
		this->token = "";
		this->type = TokenType::NONE;
	}

	Token(const std::string &token, const TokenType &type) {
		line = 0;
		linePos = 0;
		this->token = token;
		this->type = type;
	}

	std::string GetToken() const {
		return token;
	}

	TokenType GetType() const {
		return type;
	}

};

struct TokenData 
{
	std::regex patten;
	TokenType type;

	TokenData(const std::string &patten, const TokenType &type) {
		this->patten = std::regex(patten, std::regex_constants::ECMAScript);
		this->type = type;
	}

	std::regex GetPatten() const {
		return patten;
	}

	TokenType GetType() const {
		return type;
	}

	Token CheckToken(const std::string &str) {
		auto words_begin = std::sregex_iterator(str.begin(), str.end(), patten);
		auto words_end = std::sregex_iterator();
		std::smatch match;
		for (auto i = words_begin; i != words_end; ++i) {
			match = *i;
			break;
		}

		if (words_begin == words_end) {
			return Token("", TokenType::NONE);
		}

		return Token(match.str(), type);

	}
};


#endif //TOKEN_H_INCLUDED