#include <string.h>
#pragma once
struct Symbol{
	const char* string;
	int stringLength;
	int code;
};

bool symbolsSorted = false;
Symbol newSymbol(const char* string, int code){
	Symbol symbol;
	symbol.string = string;
	symbol.stringLength = strlen(string);
	symbol.code = code;
	return symbol;
}
Symbol symbols[] = {
	newSymbol("int", 1),
	newSymbol("bool", 2),

	newSymbol("(", 10),
	newSymbol(")", 11),
	newSymbol("{", 12),
	newSymbol("}", 13),

	newSymbol(";",16),
	newSymbol(",",17),


	newSymbol("if", 20),
	newSymbol("return",21),

	newSymbol("=",30),
	newSymbol("+",31),
	newSymbol("<",32),
};


// Sort symbols from longest to shortest because longer symbols can contain shorter symbols
void sortSymbols(){
	symbolsSorted = true;
	return;
	int size = sizeof(symbols) / sizeof(symbols[0]);
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size && i > j; j++){
			if(symbols[i].stringLength > symbols[j].stringLength){
				Symbol temp = symbols[i];
				symbols[i] = symbols[j];
				symbols[j] = temp;

			}
		}
	}
}

bool symbolEquals(Symbol symbol, char* string){
	if(!symbolsSorted)
		sortSymbols();
	for(int i = 0; symbol.string[i] != '\0'; i++){
		if(symbol.string[i] != string[i])
			return false;
	}
	return true;
}