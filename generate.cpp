#include <sstream>
#include <fstream>
#include <iostream>
#include "tree.cpp"
#include "syntax.cpp"
#include "table.cpp"
#pragma once

void callGenerate(Tree tree, std::stringstream *code, int *labelCount, Table *table);

void generate(Tree tree, std::stringstream *code, int *labelCount, Table *table)
{
    switch (tree.code)
    {
    case FUNCTION:
    {
        std::string fnName(tree.children[1].token.codeLocation, tree.children[1].token.codeLength);
        if (fnName == "main")
        {
            (*code) << "_start:\t\n";
            Table table = Table();
            callGenerate(tree, code, labelCount, &table);
            (*code) << "\n\t\tmov\t$60, %rax  # system call 60 is exit\n"
                    << "\t\txor\t%rdi, %rdi\n"
                    << "\t\tsyscall\n";
            break;
        }
        (*code) << fnName;
        (*code) << ":\t\n"
                << "\t\tpushq\t%rbp\n"
                << "\t\tmovq\t%rsp, %rbp\n"

                << "\t\tpushq\t%rsi\n"
                << "\t\tpushq\t%rdi\n"
                << "\t\tpushq\t%rbx # end of function prologue\n\n"
                << "\t\tpushq\t%r15\n"
                << "\t\tmovq\t%rsp, %r15\n";

        Table table = Table();
        callGenerate(tree, code, labelCount, &table);

        (*code) << "\n\t\tmovq\t%r15,%rsp # start of function epilogue\n"
                << "\t\tpopq\t%r15\n"
                << "\t\tpopq\t%rbx\n"
                << "\t\tpopq\t%rdi\n"
                << "\t\tpopq\t%rsi\n"

                << "\t\tmovq\t%rbp, %rsp\n" // clears stack automatically
                << "\t\tpopq\t%rbp\n"
                << "\t\tret # end of function\n\n";
        printTable(&table);
        break;
    }
    case RETURN_ST:
    {
        (*code) << "\t\t\t# Return statement\n";
        generate(tree.children[1], code, labelCount, table);
        (*code) << "\n\t\tpopq\t%rbx # start of function epilogue\n"
                << "\t\tpopq\t%rdi\n"
                << "\t\tpopq\t%rsi\n"

                << "\t\tmovq\t%rbp, %rsp\n" // clears stack automatically
                << "\t\tpopq\t%rbp\n"
                << "\t\tret # end of return\n\n";
        break;
    }
    case LITERAL:
    {
        int value = *(int *)tree.children[0].token.literalData;
        (*code) << "\t\tmovq\t$" << value
                << ", %rax # load literal to rax\n";
        break;
    }
    case VARIABLE:
    {
        int offset = getVariableOffset(table, tree.children[0].token.code);
        (*code) << "\t\tmovq\t" << offset << "(%rbp), %rax # load variable\n";
        break;
    }
    case DECL_ST:
    {
        tableAddVariable(table, tree.children[1].token.code);
        (*code) << "\t\tsubq\t$8, %rsp # allocate to stack\n";
        break;
    }
    case FUNC_ARG:
    {
        tableAddArgument(table, tree.children[1].token.code);
        break;
    }
    case OPERATION:
    {
        (*code) << "\t\tpushq\t%rbx\n";
        generate(tree.children[2], code, labelCount, table);
        (*code) << "\t\tmovq\t%rax, %rbx # mov for operation\n";
        if (tree.children[1].children[0].token.code == 31) //+
        {
            generate(tree.children[0], code, labelCount, table);
            (*code) << "\t\taddq\t%rbx, %rax\n"; /////////////////////////////////////////////////////////to do operation
        }
        if (tree.children[1].children[0].token.code == 32) //<
        {
            generate(tree.children[0], code, labelCount, table);
            (*code) << "\t\tcmpq\t%rbx, %rax\n"
                    << "\t\tmov\t$1,%r14\n"
                    << "\t\tcmovl\t%r14,%rax\n"
                    << "\t\tmov\t$0,%r14\n"
                    << "\t\tcmovge\t%r14,%rax\n";
        }
        (*code) << "\t\tpopq\t%rbx\n";
        break;
    }
    case FUNC_CALL:
    {
        (*code) << "\t\tpushq\t%r15\n"
                << "\t\tmovq\t%rsp, %r15 # push rsp for funtion call\n";
        callGenerate(tree, code, labelCount, table);

        std::string name = std::string(tree.children[0].token.codeLocation, tree.children[0].token.codeLength);
        (*code) << "\t\tcall\t" << name << "\n";

        (*code) << "\t\tmovq\t%r15, %rsp # remove call arguments from stack\n"
                << "\t\tpopq\t%r15\n";

        break;
    }
    case CALL_ARGS:{
        if(tree.children[0].token.code == 11)
            break;
        if(tree.children[1].token.code == 11)
            generate(tree.children[0], code, labelCount, table);
        generate(tree.children[2], code, labelCount, table);    
        generate(tree.children[0], code, labelCount, table);
        break;
    }
    case CALL_ARG:
    {
        generate(tree.children[0], code, labelCount, table);
        (*code) << "\t\tpushq\t%rax # call argument on stack\n";
        break;
    }
    case IF_ST:
    {
        (*code) << "\t\t\t#start if\n";
        int jmpLabel = (*labelCount)++;
        generate(tree.children[2], code, labelCount, table);

        (*code) << "\t\tcmpq\t$0, %rax\n"
                << "\t\tje\tl" << jmpLabel << "\n";

        generate(tree.children[4], code, labelCount, table);
        (*code) << "l" << jmpLabel << ":\n";
        break;
    }
    case ASSING_ST:
    {
        int offset = getVariableOffset(table, tree.children[0].token.code);
        generate(tree.children[2], code, labelCount, table);

        (*code) << "\t\tmovq\t%rax, " << offset << "(%rbp) # store to variable\n";
        break;
    }
        /*case PROGRAM:
        {
            callGenerate(tree, code, labelCount, table);
            (*code) << "\n";
            break;
        }*/

    default:
        callGenerate(tree, code, labelCount, table);
        break;
    }
}

void callGenerate(Tree tree, std::stringstream *code, int *labelCount, Table *table)
{
    // std::cout << tree.code << tree.token.code;
    if (tree.children == nullptr)
        return;

    for (int i = 0;; i++)
    {
        if (tree.children[i].code == 0 && tree.children[i].token.code == 0)
            return;
        if (tree.children[i].code != 0)
            generate(tree.children[i], code, labelCount, table);
    }
}

std::string generate(Tree tree)
{
    int *labelCount = new int(0);
    std::stringstream *code = new std::stringstream("");

    std::ifstream file("std.s");
    if (!file)
        throw std::runtime_error("could not open standard library file");
    (*code) << file.rdbuf();
    file.close();

    generate(tree, code, labelCount, nullptr);

    std::string output = code->str();
    std::cout << output << '\n';
    delete code;
    delete labelCount;
    return output;
}