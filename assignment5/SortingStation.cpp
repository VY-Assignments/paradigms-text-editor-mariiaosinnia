#include "SortingStation.h"
void SortingStation::Sorting(std::vector<std::string> tokens) {
    for (std::string token : tokens) {
        if (isNumber(token)) {
            queue.push(token);
        }
        else if (isFunction(token)) {
            stack.push(token);
        }
        else if (token == "(") {
            stack.push(token);
        }
        else if (token == ")") {
            while (!stack.empty() && stack.top() != "(") {
                fromStackToQueue();
            }
            if (!stack.empty()) stack.pop();
            if (!stack.empty() && isFunction(stack.top())) {
                fromStackToQueue();
            }
        }
        else if (token == ",") {
            while (!stack.empty() && stack.top() != "(") {
                fromStackToQueue();
            }
        }
        else if (isOperator(token)) {
            while (!stack.empty() && stack.top() != "(" &&
                priority[stack.top()] >= priority[token]) {
                fromStackToQueue();
            }
            stack.push(token);
        }
        else queue.push(token);
    }
    while (!stack.empty()) {
        fromStackToQueue();
    }
}

std::vector<std::string> SortingStation::getRPN() {
    std::vector<std::string> rpn;
    while (!queue.empty()) {
        rpn.push_back(queue.front());
        queue.pop();
    }
    return rpn;
}


bool SortingStation::isNumber(std::string& token) {
    try {
        std::stod(token);
        return true;
    } catch (...) {
        return false;
    }
}

bool SortingStation::isOperator(std::string& token) {
    for (std::string oper : operators) {
        if (token == oper) {
            return true;
        }
    }
    return false;
}

bool SortingStation::isFunction(std::string& token) {
    for (std::string func : functions) {
        if (token == func) return true;
    }
    return false;
}


void SortingStation::fromStackToQueue() {
    queue.push(stack.top());
    stack.pop();
}

