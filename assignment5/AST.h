#ifndef AST_H
#define AST_H
#include <stack>
#include <string>
#include <vector>


class Node;

class AST {
private:
    std::stack<Node*> stack;
public:
    Node* buildtree(std::vector<std::string>& tokens);
    bool isNumber(std::string& token);
    bool isOperator(std::string& token);
    bool isFunction(std::string& token);
};



#endif
