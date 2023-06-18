#include "lexical.cpp"
#include "syntax.cpp"
#include "tree.cpp"
#pragma once
int count = 0;
namespace Parse
{
    Tree parseTree(Token *tokens, int tokenCount = 0, int code = 100, int *tokensProcessed = nullptr, bool *success_p = nullptr)
    {
        //std::cout << "start code: " << code << std::endl;
        int synLen = 0;
        Syntax *fnSyntax = getSyntax(code, &synLen);
        int skipAhead = 0;
        count++;

        Tree tree = newTree(code, new Tree[10]);

        bool success = false;

        for (int s = 0; s < synLen && !success; s++)
        {
            skipAhead = 0;
            Syntax syntax = fnSyntax[s];
            for (int t = 0;; t++)
            {
                if (syntax.tokens[t] == 0)
                {
                    success = true;
                    if (tokensProcessed != nullptr)
                        *tokensProcessed += skipAhead;
                    //std::cout << skipAhead << " added to skipAhead\n";
                    break;
                }
                else if (syntax.tokens[t] >= 100 && syntax.tokens[t] < 200)
                {
                    bool success = false;
                    tree.children[t] = parseTree(tokens, tokenCount + skipAhead, syntax.tokens[t], &skipAhead, &success);

                    if (!success)
                    {
                        treeClear(tree);
                        break;
                    }
                }
                else if (synEquals(tokens[tokenCount + skipAhead], syntax.tokens[t]))
                {
                    tree.children[t] = newTree(tokens[tokenCount + skipAhead], nullptr);
                    skipAhead++;
                }
                else
                {
                    treeClear(tree);
                    break;
                }
            }
        }
        if(success_p != nullptr)
            *success_p = success;

        if(!success)
            tree.code = 0;
        std::cout << "Status: " << success << "    code: " << code << std::endl;
        //for (int i = 0; i < 20; i++)
        //    std::cout << tokens[tokenCount + skipAhead].codeLocation[i];
        //std::cout << std::endl;

        return tree;
    }
};