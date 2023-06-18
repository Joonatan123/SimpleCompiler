#include "token.cpp"
#include <string>

#pragma once

struct Syntax
{
    int code;
    int *tokens;
};
Syntax newSyntax(int code, int *tokens)
{
    Syntax syntax;
    syntax.code = code;
    syntax.tokens = tokens;
    return syntax;
}
enum SyntaxEnum
{
    FUNCTION = 100,
    FUNC_ARGS,
    FUNC_ARG,
    CMD_BLOCK,
    CMD_LIST,
    COMMAND,
    DECL_ST,
    ASSING_ST,
    IF_ST,
    RETURN_ST,
    FUNC_CALL,
    CALL_ARGS,
    CALL_ARG,
    VALUE,
    VALUE_,
    OPERATION,
    OPERATOR,
    LITERAL,
    VARIABLE,

    FUNCTION_LIST,
    PROGRAM = 199,
};
Syntax syntax[] = {
    newSyntax(PROGRAM, new int[10]{FUNCTION_LIST}),

    newSyntax(FUNCTION_LIST, new int[10]{FUNCTION, FUNCTION_LIST}),
    newSyntax(FUNCTION_LIST, new int[10]{0}),

    newSyntax(FUNCTION, new int[10]{1, 200, 10, FUNC_ARGS, CMD_BLOCK}), // function

    newSyntax(FUNC_ARGS, new int[10]{FUNC_ARG, 17, FUNC_ARGS}), // function arguments
    newSyntax(FUNC_ARGS, new int[10]{FUNC_ARG, 11}),
    newSyntax(FUNC_ARGS, new int[10]{11}),

    newSyntax(FUNC_ARG, new int[10]{1, 200}),

    newSyntax(CMD_BLOCK, new int[10]{12, CMD_LIST}), // command block

    newSyntax(CMD_LIST, new int[10]{COMMAND, CMD_LIST}), // command list
    newSyntax(CMD_LIST, new int[10]{13}),

    newSyntax(COMMAND, new int[10]{DECL_ST}), // command
    newSyntax(COMMAND, new int[10]{IF_ST}),
    newSyntax(COMMAND, new int[10]{RETURN_ST}),
    newSyntax(COMMAND, new int[10]{FUNC_CALL, 16}),
    newSyntax(COMMAND, new int[10]{ASSING_ST}),

    newSyntax(DECL_ST, new int[10]{1, 200, 16}),

    newSyntax(ASSING_ST, new int[10]{200, 30, VALUE, 16}),

    newSyntax(IF_ST, new int[10]{20, 10, VALUE, 11, CMD_BLOCK}),
    newSyntax(IF_ST, new int[10]{20, 10, VALUE, 11, COMMAND}),

    newSyntax(RETURN_ST, new int[10]{21, VALUE, 16}),

    newSyntax(FUNC_CALL, new int[10]{200, 10, CALL_ARGS}),

    newSyntax(CALL_ARGS, new int[10]{CALL_ARG, 17, CALL_ARGS}),
    newSyntax(CALL_ARGS, new int[10]{CALL_ARG, 11}),
    newSyntax(CALL_ARGS, new int[10]{11}),

    newSyntax(CALL_ARG, new int[10]{VALUE}),

    newSyntax(VALUE, new int[10]{FUNC_CALL}),
    newSyntax(VALUE, new int[10]{OPERATION}),
    newSyntax(VALUE, new int[10]{VALUE_}),

    newSyntax(VALUE_, new int[10]{VARIABLE}),
    newSyntax(VALUE_, new int[10]{LITERAL}),

    newSyntax(OPERATION, new int[10]{VALUE_, OPERATOR, VALUE}),

    newSyntax(OPERATOR, new int[10]{31}),
    newSyntax(OPERATOR, new int[10]{32}),

    newSyntax(LITERAL, new int[10]{99}),

    newSyntax(VARIABLE, new int[10]{200}),

    newSyntax(0, new int[10]{99}),
};
/*
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
*/
Syntax *getSyntax(int code, int *length)
{
    Syntax *output;
    int i = 0;
    for (i = 0; i < sizeof(syntax) / sizeof(Syntax); i++)
    {
        if (syntax[i].code == code)
        {
            output = &(syntax[i]);
            break;
        }
    }
    for (int j = 0;; j++)
    {
        if (syntax[i + j].code != code)
        {
            *length = j;
            break;
        }
    }
    return output;
}
bool synEquals(Token token, int code)
{
    if (token.code >= 200 && code >= 200)
        return true;
    return token.code == code;
}
std::string syntaxToString(SyntaxEnum s)
{
    switch (s)
    {
    case FUNCTION:
        return "FUNCTION";
    case FUNC_ARGS:
        return "FUNC_ARGS";
    case FUNC_ARG:
        return "FUNC_ARG";
    case CMD_BLOCK:
        return "CMD_BLOCK";
    case CMD_LIST:
        return "CMD_LIST";
    case COMMAND:
        return "COMMAND";
    case DECL_ST:
        return "DECL_ST";
    case ASSING_ST:
        return "ASSING_ST";
    case IF_ST:
        return "IF_ST";
    case RETURN_ST:
        return "RETURN_ST";
    case FUNC_CALL:
        return "FUNC_CALL";
    case CALL_ARGS:
        return "CALL_ARGS";
    case CALL_ARG:
        return "CALL_ARG";
    case VALUE:
        return "VALUE";
    case VALUE_:
        return "VALUE_";
    case OPERATION:
        return "OPERATION";
    case OPERATOR:
        return "OPERATOR";
    case LITERAL:
        return "LITERAL";
    case VARIABLE:
        return "VARIABLE";

    case FUNCTION_LIST:
        return "FUNCTION_LIST";
    case PROGRAM:
        return "PROGRAM";
    }
}