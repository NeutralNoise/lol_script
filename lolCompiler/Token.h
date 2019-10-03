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

/**
 * \struct Token 
 * \brief Information about a token
 * 
*/

struct Token
{
	std::string token; //!< The token string.
	TokenType type; //!< The type of token. \see TokenType
	int line; //!< The line in the file the token was found.
	int linePos; //!< The position in the line the token was found.

	/**
	 * \brief Construct a new Token object
	 * 
	*/

	Token() {
		line = 0;
		linePos = 0;
		this->token = "";
		this->type = TokenType::NONE;
	}

	/**
	 * \brief Construct a new Token object
	 * 
	 * \param token The token found.
	 * \param type The type of token found.
	*/

	Token(const std::string &token, const TokenType &type) {
		line = 0;
		linePos = 0;
		this->token = token;
		this->type = type;
	}

	/**
	 * \brief Get the Token string.
	 * 
	 * \return std::string of the token
	*/

	std::string GetToken() const {
		return token;
	}

	/**
	 * \brief Get the Type type.
	 * 
	 * \return TokenType \see TokenType
	*/

	TokenType GetType() const {
		return type;
	}

};

/**
 * \struct TokenData 
 * \brief Contains information used when looking for Tokens.
 * 
*/

struct TokenData 
{
	std::regex patten; //!< The Regex patten used to find the tokens.
	TokenType type; //!< The type of token the patten matchs.

	/**
	 * \brief Construct a new TokenData object
	 * 
	 * \param patten The patten used to find the Token
	 * \param type The TokenType the patten matchs. \see TokenType
	*/

	TokenData(const std::string &patten, const TokenType &type) {
		this->patten = std::regex(patten, std::regex_constants::ECMAScript);
		this->type = type;
	}

	/**
	 * \brief Get the Patten.
	 * 
	 * \return std::regex 
	*/

	std::regex GetPatten() const {
		return patten;
	}

	/**
	 * \brief Get the TokenType.
	 * 
	 * \return TokenType 
	*/

	TokenType GetType() const {
		return type;
	}

	/**
	 * \brief Checks if the given string matchs the patten.
	 * 
	 * \param str The string string check for the Regex patten.
	 * \return Token
	*/

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