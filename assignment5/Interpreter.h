//
// Created by Legion on 03.07.2025.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "AST.h"
#include "SortingStation.h"


class Interpreter {
private:
    std::unordered_map<std::string, double> vars;
    std::unordered_map<std::string, std::string> userFuncs;

    SortingStation* sortingStation;
    AST* ast;
public:
    Interpreter(SortingStation* ss, AST* a) : sortingStation(ss), ast(a){};

    ~Interpreter() = default;
    void setVariable(std::vector<std::string>& tokens);

    std::unordered_map<std::string, double>& getVars() {
        return vars;
    }
};



#endif //INTERPRETER_H
