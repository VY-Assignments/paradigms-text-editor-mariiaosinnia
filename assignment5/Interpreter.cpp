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
    if (tokens.size() < 6) {
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

    int body_start = i + 1;
    int body_end = tokens.size();
    std::vector<std::string> body(tokens.begin() + body_start, tokens.begin() + body_end);
    userFuncs[funcName] = {params, body};
}

double Interpreter::callCustomFunc(std::string name, std::vector<double> args) {
    if (!userFuncs.count(name)) {
        throw std::runtime_error("Function not found");

    }

    userFunc func = userFuncs[name];
    if (args.size() != func.params.size()) {
        throw std::runtime_error("Incorrect number of arguments for function");
    }

    std::unordered_map<std::string, double> localVars;
    for (int i = 0; i < args.size(); i++) {
        localVars[func.params[i]] = args[i];
    }

    sortingStation->Sorting(func.body);
    std::vector<std::string> rpn = sortingStation->getRPN();
    Node* root = ast->buildtree(rpn);
    double result = root->evaluate(localVars);
    return result;
}

