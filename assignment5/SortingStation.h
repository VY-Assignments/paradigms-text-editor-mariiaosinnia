#ifndef SORTINGSTATION_H
#define SORTINGSTATION_H
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>

#include "Tokenizer.h"


class SortingStation {
private:
    std::unordered_map<std::string, int> priority = {
        {"=", 1},
        {"+", 2},
        {"-", 2},
        {"*", 3},
        {"/", 3},
        {"pow", 4},
        {"abs", 4},
        {"max", 4},
        {"min", 4}
    };
    std::queue<std::string> queue;
    std::stack<std::string> stack;
    std::vector<std::string> rpn;

    std::vector<std::string> operators = {"+", "-", "*", "/", "(", ")"};
    std::vector<std::string> functions = {"pow", "abs", "max", "min"};
public:
    SortingStation(){};
    void Sorting(std::vector<std::string>& tokens);
    std::vector<std::string> getRPN();
    bool isNumber(std::string& token);
    bool isOperator(std::string& ch);
    void fromStackToQueue();
    bool isFunction(std::string& token);
    void addCustomFunc(std::string& name, int precedence);
};



#endif
