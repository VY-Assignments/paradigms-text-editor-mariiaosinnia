#ifndef NUMBERNODE_H
#define NUMBERNODE_H
#include "Node.h"


class NumberNode : public Node {
private:
    double value;
public:
    NumberNode(double val) : value(val) {}
    double evaluate(std::unordered_map<std::string, double>& vars) override {
        return value;
    }
};



#endif
