#include "OperatorNode.h"

double OperatorNode::evaluate(std::unordered_map<std::string, double>& vars) override {
    double l_num = left->evaluate(vars);
    double r_num = right->evaluate(vars);

    switch (operat) {
        case '+': return l_num + r_num;
        case '-': return l_num - r_num;
        case '*': return l_num * r_num;
        case '/': return l_num / r_num;
        default: throw std::runtime_error("Undefined operator");
    }
}
