#ifndef VARIABLENODE_H
#define VARIABLENODE_H
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "Node.h"

class VariableNode : public Node {
private:
    std::string name;
public:
    VariableNode(std::string& n) : name(n){};
    double evaluate(std::unordered_map<std::string, double>& vars) override {
        auto var = vars.find(name);
        if (var != vars.end()) return var->second;
        else throw std::runtime_error("Undefined variable: " + name);
    }
};

#endif
