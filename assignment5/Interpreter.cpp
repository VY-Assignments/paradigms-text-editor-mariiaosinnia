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

void Interpreter::defineFunction(std::vector<std::string> &tokens) {
    if (tokens.size() < 8) {
        std::cout << "Invalid function definition\n";
        return;
    }

    std::string funcName = tokens[1];
    if (tokens[2] != "(") {
        std::cout << "Invalid function definition\n";
        return;
    }
    int i = 3;
    std::vector<std::string> params;
    while (tokens[i] != ")") {
        params.push_back(tokens[i]);
        i++;
        if (i >= tokens.size()) {
            std::cout << "Invalid parameters\n";
            return;
        }
    }

    int body_start = i + 2;
    int body_end = tokens.size() - 1;
    std::vector<std::string> body(tokens.begin() + body_start, tokens.begin() + body_end);
    userFuncs[funcName] = {params, body};
    std::cout << "Function '" << funcName << "' defined.\n";
}
