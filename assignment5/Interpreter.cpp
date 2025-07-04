#include "Interpreter.h"

#include <iostream>

#include "Node.h"

void Interpreter::setVariable(std::vector<std::string> &tokens) {
    if (tokens.size() < 4) {
        std::cout << "Invalid variable assignment" << std::endl;
        return;
    }
    std::string varName = tokens[1];
    std::vector<std::string> subTokens(tokens.begin() + 3, tokens.end());

    if (subTokens.empty()) {
        std::cout << "Invalid variable value" << std::endl;
        return;
    }
    if (subTokens.size() == 1) {
        vars[varName] = std::stod(subTokens[0]);
    }
    else if (subTokens.size() > 1) {
        sortingStation->Sorting(subTokens);
        std::vector<std::string> rpn = sortingStation->getRPN();
        Node* root = ast->buildtree(rpn);
        double result = root->evaluate(vars);
        vars[varName] = result;
    }
    else std::cout << "Invalid var value" << std::endl;
}
