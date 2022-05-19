#include <iostream>
#include <set>
#include "parser.hpp"
#include "tree.cpp"

extern int yylex();

/*
 * These values are globals defined in the parsing function.
 */
extern class Tree *root;
extern std::set<std::string> symbols;

int main()
{
    if (!yylex())
    {
        // std::cout << root->to_string() << std::endl;
        std::cout << root->to_digraph() << std::endl;
        return 0;
    }
}
