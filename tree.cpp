#include "token.cpp"
#include "syntax.cpp"
#pragma once
struct Tree
{
    int code = 0;              // 0 if token
    Token token = {.code = 0}; // 0 if more abstract syntax
    Tree *children = nullptr;
};
void treeDelete(Tree tree)
{
    tree.code = 0;
    tree.token.code = 0;
    if (tree.children == nullptr)
        return;
    for (int i = 0; i < 10; i++)
    {
        if (tree.children[i].children != nullptr)
        {
            treeDelete(tree.children[i]);
            tree.children[i].children = nullptr;
        }
    }
    delete[] tree.children;
    tree.children = nullptr;
}
void treeClear(Tree tree)
{
    tree.code = 0;
    tree.token.code = 0;
    if (tree.children == nullptr)
        return;
    for (int i = 0; i < 10; i++)
    {
        treeClear(tree.children[i]);
    }
}
Tree newTree(Token token, Tree *children)
{
    Tree tree;
    tree.token = token;
    tree.children = children;
    return tree;
}
Tree newTree(int code, Tree *children)
{
    Tree tree;
    tree.code = code;
    tree.children = children;
    return tree;
}
void printTree(Tree tree, int depth = 0)
{
    std::cout << "Tree d: " << depth << " code: ";
    if (tree.code == 0)
        std::cout << tree.token.code;
    else if(tree.code != 0)
        std::cout << syntaxToString((SyntaxEnum)tree.code);
    else
        std::cout << tree.code;

    if (tree.token.codeLocation != nullptr)
    {
        std::cout << "   ";
        for (int i = 0; i < tree.token.codeLength; i++)
            std::cout << tree.token.codeLocation[i];
    }
    std::cout << '\n';

    for (int i = 0; i < 10; i++)
    {
        if (tree.children != nullptr && !(tree.children[i].code == 0 && tree.children[i].token.code == 0))
            printTree(tree.children[i], depth + 1);
    }
}