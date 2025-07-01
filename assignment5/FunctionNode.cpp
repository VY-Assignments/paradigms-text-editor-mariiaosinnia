#include "FunctionNode.h"

#include <stdexcept>
#include <cmath>

double FunctionNode::evaluate(std::unordered_map<std::string, double> &vars) {
    double num1 = 0;
    if (arg1) num1 = arg1->evaluate(vars);
    double num2 = 0;
    if (arg2) num2 = arg2->evaluate(vars);

    if (name == "max") return std::max(num1, num2);
    else if (name == "min") return std::min(num1, num2);
    else if (name == "pow") return std::pow(num1, num2);
    else if (name == "abs") return std::abs(num1);
    else throw std::runtime_error("Unknown function: " + name);
}
