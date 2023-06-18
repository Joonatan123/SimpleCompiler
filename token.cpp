#pragma once

struct Token{
	int code;

	char* codeLocation;
	int codeLength;

	void* literalData;
	int literalSize;
};
Token newToken(int code, char* cp, int codeLength){
	Token token;
	token.code = code;
	token.codeLocation = cp;
	token.codeLength = codeLength;
	return token;
}
Token newToken(int code, void* literalData, int literalSize, char* cp, int codeLength){
	Token token;
	token.code = code;
	token.literalData = literalData;
	token.literalSize = literalSize;
	token.codeLocation = cp;
	token.codeLength = codeLength;
	return token;
}
