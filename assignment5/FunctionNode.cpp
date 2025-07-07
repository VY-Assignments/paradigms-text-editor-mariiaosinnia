#include "FunctionNode.h"

#include <stdexcept>
#include <cmath>
#include <functional>

double FunctionNode::evaluate(std::unordered_map<std::string, double> &vars) {
    double num1 = 0;
    if (arg1) num1 = arg1->evaluate(vars);
    double num2 = 0;
    if (arg2) num2 = arg2->evaluate(vars);

    std::unordered_map<std::string, std::function<double(double, double)>> binFuncs = {
        {"max", [](double a, double b) { return std::max(a, b); }},
        {"min", [](double a, double b) { return std::min(a, b); }},
        {"pow", [](double a, double b) { return std::pow(a, b); }}
    };
    std::unordered_map<std::string, std::function<double(double)>> unFuncs = {
        {"abs", [](double a) { return std::abs(a); }}
    };

    if (binFuncs.find(name) != binFuncs.end()) return binFuncs.at(name)(num1, num2);
    if (unFuncs.find(name) != unFuncs.end()) return unFuncs.at(name)(num1);

    throw std::runtime_error("Unknown function: " + name);
}
