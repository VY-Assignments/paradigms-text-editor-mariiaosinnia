#include "AST.h"

#include "FunctionNode.h"
#include "NumberNode.h"
#include "OperatorNode.h"

Node *AST::buildtree(std::vector<std::string> &tokens) {
    for (std::string token : tokens) {
        if (isNumber(token)) {
            stack.push(new NumberNode(std::stod(token)));
        }
        else if (isOperator(token)) {
            Node* right = stack.top(); stack.pop();
            Node* left = stack.top(); stack.pop();
            stack.push(new OperatorNode(token[0],left, right));
        }
        else if (isFunction(token)) {
            Node* right = stack.top(); stack.pop();
            Node* left = stack.top(); stack.pop();
            stack.push(new FunctionNode(token, left, right));
        }
    }
    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return stack.top();
}

bool AST::isNumber(std::string &token) {
    try {
        std::stod(token);
        return true;
    }catch (...) {
        return false;
    }
}

bool AST::isOperator(std::string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

bool AST::isFunction(std::string &token) {
    return token == "max" || token == "min" || token == "pow" || token == "abs";
}




