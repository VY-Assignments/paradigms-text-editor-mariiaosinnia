#ifndef FUNCTIONNODE_H
#define FUNCTIONNODE_H
#include <string>

#include "Node.h"


class FunctionNode : public Node{
private:
    std::string name;
    Node* arg1;
    Node* arg2;
public:
    FunctionNode(std::string& n, Node* a1, Node* a2) : name(n), arg1(a1), arg2(a2){};
    double evaluate(std::unordered_map<std::string, double> &vars) override;
};



#endif
