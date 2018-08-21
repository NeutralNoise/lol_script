#include <iostream>
#include <regex>
#include <string>
#include "Tokenizer.h"

int main(int argc, char** argv) {
	
	Tokenizer tokens;

	std::string test = "int32 _hello = 43;";

	Token tok("", TokenType::ASSIGN);
	int current_pos = 0;
	int current_size = test.size();

	while (tok.GetType() != TokenType::NONE) {
		tok = tokens.nextToken(&test, 1, current_pos);
		current_pos += tok.token.size();
		std::cout << tok.GetToken() << " LINE: " << tok.line << " POS: " << tok.linePos << std::endl;
	}

	std::cin.get();

	return 0;
}