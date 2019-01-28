#include <iostream>
#include <regex>
#include <string>
#include "Tokenizer.h"
#include <vector>
#include <fstream>
#include "ParseTokens.h"
#include "AST.h"
#include "ASTParser.h"

//Check for key words
//TODO find a better place for this :D
void CheckTokenKeywords(const std::vector<std::string> &key, std::vector<Token> *toks) {
	for (size_t i = 0; i < toks->size(); i++) {
		for (size_t k = 0; k < key.size(); k++) {
			if (strcmp(key[k].c_str(), toks->operator[](i).GetToken().c_str()) == 0) {
				toks->at(i).type = TokenType::KEYWORD;
				break;
			}
		}
	}
}

int main(int argc, char** argv) {

	Tokenizer tokens;
	ParseTokens parser;
	AST ast;
	std::string fileName = "../../Documents/Examples/test2.lol";

	std::ifstream file(fileName);
	std::vector<std::string> test;
	std::cout << "Loading File!\n";
	if (file.is_open()) {
		std::cout << fileName << std::endl;
		std::string tmpLine;
		while (std::getline(file, tmpLine)) {
			test.push_back(tmpLine);
		}
	}

	std::cout << "Generating Tokens!\n";
	int current_pos = 0;
	int current_size = test.size();
	std::vector<Token> tokenVec;
	for (size_t i = 0; i < test.size(); i++) {
		Token tok("", TokenType::ASSIGN);
		while (tok.GetType() != TokenType::NONE) {
			tok = tokens.nextToken(&test[i], (i + 1), current_pos);
			current_pos += tok.token.size();
			if (tok.GetType() != TokenType::WHITE_SPACE && tok.GetType() != TokenType::NONE) {
				std::cout << tok.GetToken() << " LINE: " << tok.line << " POS: " << tok.linePos << std::endl;
			}
			if (tok.GetType() != TokenType::NONE) {
				tokenVec.push_back(tok);
			}
		}
	}

	std::vector<std::string> keyWords;
	//TODO load these from a file or something.
	keyWords.push_back("void");
	keyWords.push_back("int");
	keyWords.push_back("return");
	CheckTokenKeywords(keyWords, &tokenVec);
	std::cout << "Generating AST!\n";
	parser.Parse(tokenVec, &ast);
	std::cout << "TOKENS:\n";
	ASTNode * root = ast.GetRoot();
	root->PrintNodes();
	std::cout << "Writing binary file!\n";
	//std::ofstream ofile("../Documents/Examples/test1.lolc");
	std::ofstream ofile("../Documents/Examples/test2.lolc");
	/*
	if (ofile.is_open()) {
		//WriteByte(ofile, 't');

		unsigned char writeTest[12] = { 'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '\n' };

		WriteBytes(ofile, &writeTest[0], sizeof("Hello World\n") - 1);
	}
	*/
	ast.WriteAST(ofile);


	//Convert ast to binary
	std::cout << "Done!\n";
	std::cin.get();

	return 0;
}
