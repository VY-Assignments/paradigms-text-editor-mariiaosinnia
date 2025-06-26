#ifndef OPERATORNODE_H
#define OPERATORNODE_H
#include <stdexcept>

#include "Node.h"


class OperatorNode : public Node {
private:
    char operat;
    Node* left;
    Node* right;
public:
    OperatorNode(char op, Node* l, Node* r) : operat(op), left(l), right(r) {};
    double evaluate(std::unordered_map<std::string, double>& vars) override;
};



#endif
