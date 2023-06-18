#pragma once
#include <iostream>

#include "symbol.cpp"
#include "token.cpp"

namespace Lexical{
bool isIgnored(char c){
	return c == ' ' || c == '\n' || c == '\t';
}
bool isNumeral(char c){
	return (c >= 48) && (c <= 57);
}
bool isAlphabet(char c){
	return (c >= 65) && (c <= 90) || ((c >= 97) && (c <= 122));
}
bool isUnderScore(char c){
	return c == 95;
}
bool isAlphaNum(char c){
	return isAlphabet(c) || isNumeral(c) || isUnderScore(c);
}
//return index of the symbol in the symbols array. -1 when not found
int isSymbol(char* cp){
	for(int i = 0; i < sizeof(symbols) / sizeof(symbols[0]); i++){
		if(symbolEquals(symbols[i], cp)){
			return i;
		}
	}
	return -1;
}
int identifierLength(char* cp){
	for(int i = 0;;i++){
		if(!isAlphaNum(cp[i]))
			return i;
	}
}
bool identifierEquals(char* id1, char* id2){
	for(int i = 0;; i++){
		if(!isAlphaNum(id1[i]) && !isAlphaNum(id2[i]))
			return true;
		if(id1[i] != id2[i])
			return false; 
	}
}
int countIgnored(char* cp){
	for(int i = 0;; i++){
		if(!isIgnored(cp[i]))
			return i;
	}
}
int stringToInt(char* cp){
	int buffer[10];
	int index = 0;
	for(;cp[index] >= 48 && cp[index] <= 57; index++)
		buffer[index] = cp[index] - 48;
	index--;
	int sum = 0;
	int multiplier = 1;
	for(;index >= 0; index--){
		sum += buffer[index] * multiplier;
		multiplier = multiplier * 10;
	}
	return sum;
}
Token* separateTokens(char *program){
	Token *tokens = new Token[1024];
	int tokenCounter = 0;

	char** identifiers = new char*[1024];
	int* identifierCodes = new int[1024];
	int identifierCount = 0;
	int nextIdentifierCode = 200;
	for(char* cp = program; *cp != '\0';){
		int symbol_i = isSymbol(cp);
		if(symbol_i != -1){
			tokens[tokenCounter++] = newToken(symbols[symbol_i].code, cp, symbols[symbol_i].stringLength);
			cp += symbols[symbol_i].stringLength;
			continue;
		}

		char c = *cp;

		if(isAlphabet(c)){
			int identifierCode = 0;
			identifiers[identifierCount] = cp;
			for(int i = 0; i < identifierCount; i++){
				if(identifierEquals(cp, identifiers[i])){
					identifierCode = identifierCodes[i];
					break;
				}
			}
			if(identifierCode == 0)
				identifierCode = nextIdentifierCode++;
			identifierCodes[identifierCount] = identifierCode;

			tokens[tokenCounter++] = newToken(identifierCode, cp, identifierLength(cp));

			identifierCount++;

			cp += identifierLength(cp);
		}
		else if(isNumeral(c)){
			tokens[tokenCounter++] = newToken(99, new int(stringToInt(cp)), sizeof(int), cp, identifierLength(cp));
			cp += identifierLength(cp);
		}
		else if(isIgnored(c))
			cp++;
		else{
			std::cout << "Invalid char: " << *cp << '\n';
			throw std::invalid_argument("");
		}
	}
	return tokens;
}
}
