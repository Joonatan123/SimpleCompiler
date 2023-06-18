#include "parse.cpp"
#include "generate.cpp"
#include <iostream>

#include <sstream>
#include <fstream>

void printTokens(Token* tokens){
		for(int i = 0; tokens[i].code != 0; i++){
		std::cout << std::string(tokens[i].codeLocation,tokens[i].codeLength);
		for(int j = 0; j < 20 - tokens[i].codeLength ; j++)
			std::cout << " ";
		std::cout << tokens[i].code;
		if(tokens[i].code == 99)
			std::cout << "    " << *(int*)tokens[i].literalData;
		std::cout << std::endl;
	}
}

int main(int argc, char *argv[]){
	if(argc < 2)
		throw std::runtime_error("no arguments");
	Token* tokens;

	std::string path(argv[1]);

	std::ifstream t(path);
	if(!t)
		throw std::runtime_error("could not open source file");
	std::stringstream buffer;
	buffer << t.rdbuf();
	std::string temp = buffer.str();
	char* p = (char*)malloc(temp.size() + 1);
	memcpy(p, temp.c_str(), temp.size());
	tokens = Lexical::separateTokens((char*)p);
	
	printTokens(tokens);

	Tree tree = Parse::parseTree(tokens,0,199);
	printTree(tree);

	std::string code = generate(tree);

	std::ofstream out("output.s");
    out << code;
    out.close();
}

