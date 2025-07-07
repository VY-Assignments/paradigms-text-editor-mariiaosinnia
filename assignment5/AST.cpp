#include "AST.h"

#include "FunctionNode.h"
#include "NumberNode.h"
#include "OperatorNode.h"
#include "VariableNode.h"

Node *AST::buildtree(std::vector<std::string> &tokens) {
    for (std::string token : tokens) {
        if (isNumber(token)) {
            stack.push(new NumberNode(std::stod(token)));
        }
        else if (isOperator(token)) {
            if (stack.size() < 2) {
                throw std::runtime_error("Not enough operands for operator: " + token);
            }
            Node* right = stack.top(); stack.pop();
            Node* left = stack.top(); stack.pop();
            stack.push(new OperatorNode(token[0],left, right));
        }
        else if (isFunction(token)) {
            if (token == "abs") {
                if (stack.empty()) {
                    throw std::runtime_error("Not enough arguments for function: " + token);
                }
                Node* arg = stack.top(); stack.pop();
                stack.push(new FunctionNode(token, arg, nullptr));
            } else {
                if (stack.size() < 2) {
                    throw std::runtime_error("Not enough arguments for function: " + token);
                }
                Node* right = stack.top(); stack.pop();
                Node* left = stack.top(); stack.pop();
                stack.push(new FunctionNode(token, left, right));
            }
        }
        else {
            stack.push(new VariableNode(token));
        }
    }
    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    Node* result = stack.top();
    stack.pop();
    while (!stack.empty()) {
        delete stack.top();
        stack.pop();
    }
    return result;
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




