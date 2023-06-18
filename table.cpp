#include <map>
struct Variable
{
    int code = 0;
    int bpOffset = 0;
};
struct Table
{
    // key = code, value = offset
    std::map<int, int> variables;
    int argumentOffset = 8;
    int variableOffset = 0;
};
void tableAddVariable(Table *t, int code)
{
    t->variableOffset -= 8;
    if (t->variables.count(code))
    {
        std::cout << code << '\n';
        throw std::runtime_error("Double definition of variable, code: " );
    }
    t->variables[code] = t->variableOffset;
}
void tableAddArgument(Table *t, int code)
{
    t->argumentOffset += 8;
    if (t->variables.count(code))
        throw std::runtime_error("Double definition of argument" + code);
    t->variables[code] = t->argumentOffset;
}
int getVariableOffset(Table *t, int code)
{
    return t->variables[code];
}
void printTable(Table *t)
{
    for (std::map<int, int>::iterator it = t->variables.begin();
         it != t->variables.end(); it++)
    {
        if (it->second > 0)
        {
            std::cout << "Argument code: " << it->first
                      << "    bp offset: " << it->second << '\n';
        }
        else
        {
            std::cout << "Variable code: " << it->first
                      << "    bp offset: " << it->second << '\n';
        }
    }
}