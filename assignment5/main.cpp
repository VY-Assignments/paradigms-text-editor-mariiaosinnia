#include <iostream>
#include <string>

#include "AST.h"
#include "Interpreter.h"
#include "Node.h"
#include "SortingStation.h"
#include "Tokenizer.h"

int main() {
    Tokenizer tokenizer;
    SortingStation shunting;
    AST ast;
    Interpreter interpreter(&shunting, &ast);

    std::string input;

    while (true) {
        std::getline(std::cin, input);

        if (input == "exit") break;
        if (input.empty()) continue;

        std::vector<std::string> tokens = tokenizer.tokenization(input);

        if (tokens.empty()) continue;

        try {
            if (tokens[0] == "var") interpreter.setVariable(tokens);
            else if (tokens[0] == "def") interpreter.defineFunction(tokens);
            else if (tokens[1]  == "(") {
                if (interpreter.getUserFuncs().count(tokens[0])) {
                    std::string name = tokens[0];
                    std::vector<double> args;
                    for (int i = 2; i < tokens.size(); i++) {
                        if (tokens[i] == ")") break;
                        if (tokens[i] == ",") continue;
                        args.push_back(std::stod(tokens[i]));
                    }
                    double result = interpreter.callCustomFunc(name, args);
                    std::cout << result << std::endl;
                }
                else {
                    shunting.Sorting(tokens);
                    std::vector<std::string> rpn = shunting.getRPN();
                    Node* root = ast.buildtree(rpn);
                    double result = root->evaluate(interpreter.getVars());
                    std::cout << result << std::endl;
                }
            }
            else {
                shunting.Sorting(tokens);
                std::vector<std::string> rpn = shunting.getRPN();
                Node* root = ast.buildtree(rpn);
                double result = root->evaluate(interpreter.getVars());
                std::cout << result << std::endl;
            }
        } catch (std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
