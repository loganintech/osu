#include <vector>
#include <string>
#include <iostream>

enum NodeType
{
    Unary,
    Binary,
    Block,
    Assignment,
    Identifier,
    Value,
    Raw,
};

class Tree
{
public:
    std::string tok;
    double dat;

    NodeType nodetype;
    std::vector<Tree *> statements = std::vector<Tree *>();

    Tree(NodeType type, std::string token, double val)
    {
        tok = token;
        nodetype = type;
        dat = val;
    }
    Tree(NodeType type, std::string token)
    {
        tok = token;
        nodetype = type;
        dat = 0;
    }

    Tree(NodeType type, std::string token, std::vector<Tree *> stmts)
    {
        tok = token;
        nodetype = type;
        for (auto statement : stmts)
        {
            statements.push_back(statement);
        }
    }
    Tree(NodeType type, std::string token, Tree *left)
    {
        tok = token;
        nodetype = type;
        statements.push_back(left);
    }
    Tree(NodeType type, std::string token, Tree *left, Tree *right)
    {
        tok = token;
        nodetype = type;
        statements.push_back(left);
        statements.push_back(right);
    }

    std::string _to_digraph(std::string pre)
    {
        std::string build = std::string();
        int i = 0;
        Tree *prevstat = nullptr;
        switch (nodetype)
        {
        case NodeType::Unary:
            build = std::string(pre + " [label=\"" + tok + "\"];\n");
            build += std::string(pre + " -> " + pre + "_un;\n");
            build += statements[0]->_to_digraph(pre + "_un;\n");
            return build;
        case NodeType::Binary:
            build = std::string(pre + " [label=\"" + tok + "\"];\n");
            build += std::string(pre + " -> " + pre + "_lhs;\n");
            build += statements[0]->_to_digraph(pre + "_lhs");
            build += std::string(pre + " -> " + pre + "_rhs;\n");
            build += statements[1]->_to_digraph(pre + "_rhs");
            return build;
        case NodeType::Block:
            build = std::string(pre + " [label=\"" + tok + "\"];\n");
            for (auto statement : statements)
            {
                if (statement == nullptr || statement == prevstat)
                    continue;
                prevstat = statement;

                build += std::string(pre + " -> " + pre + "_" + std::to_string(i) + ";\n");
                build += statement->_to_digraph(pre + "_" + std::to_string(i));
                i++;
            }
            return build;
        case NodeType::Assignment:
            build = std::string(pre + " [label=\"Assignment\"];\n");
            build += std::string(pre + " -> " + pre + "_lhs;\n");
            build += statements[0]->_to_digraph(pre + "_lhs");
            build += std::string(pre + " -> " + pre + "_rhs;\n");
            build += statements[1]->_to_digraph(pre + "_rhs");
            return build;
        case NodeType::Identifier:
            build = std::string(pre + " [shape=box,label=\"Identifier: " + tok + "\"];\n");
            return build;
        case NodeType::Value:
            if (tok == "True" || tok == "False")
            {
                build = std::string(pre + " [shape=box,label=\"Boolean: " + tok + "\"];\n");
            }
            else
            {
                build = std::string(pre + " [shape=box,label=\"Integer: " + tok + "\"];\n");
            }
            return build;
        case NodeType::Raw:
            build = std::string(pre + " [label=\"" + tok + "\"];\n");
            return build;
        default:
            return std::string("Something horribly wrong has happened");
        }
        return std::string("Something horribly wrong has happened");
    }

    std::string to_digraph()
    {
        std::string build = std::string();
        build += "digraph G {\n";
        build += this->_to_digraph("root");
        build += "}\n";
        return build;
    }

    void push_back(Tree *statement)
    {
        statements.push_back(statement);
    }
};
