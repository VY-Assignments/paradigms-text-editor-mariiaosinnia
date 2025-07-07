#include "Tokenizer.h"

std::vector<std::string> Tokenizer::tokenization(std::string& expression) {
    std::vector<std::string> tokens;
    std::string identifier;
    std::string number;

    for (int i = 0; i < expression.length(); i++) {
        char ch = expression[i];
        if (std::isspace(ch)) {
            if (!number.empty()) {
                tokens.push_back(number);
                number.clear();
            }
            if (!identifier.empty()) {
                tokens.push_back(identifier);
                identifier.clear();
            }
            continue;
        }
        if (ch == '-' && (i == 0 || expression[i - 1] == '(' || expression[i - 1] == ',' ||
        isOperator(expression[i - 1]))) {
            if (i + 1 < expression.length() && (std::isdigit(expression[i + 1]) || expression[i + 1] == '.')) {
                number += ch;
                continue;
            }
        }

        if (std::isdigit(ch) || ch == '.') {
            number += ch;
            continue;
        }
        if (!number.empty()) {
            tokens.push_back(number);
            number.clear();
        }
        if (std::isalnum(ch)) {
            identifier += ch;
            continue;
        }
        if (!identifier.empty()) {
            if (i + 1 < expression.length() && expression[i + 1] == '(' && isFunction(identifier)) {
                tokens.push_back(identifier);
            } else {
                tokens.push_back(identifier);
            }
            identifier.clear();
        }
        if (ch == ',') {
            tokens.push_back(",");
            continue;
        }
        if (isOperator(ch)) {
            tokens.push_back(std::string(1, ch));
        }
    }
    if (!identifier.empty()) {
        tokens.push_back(identifier);
    }
    if (!number.empty()) {
        tokens.push_back(number);
    }
    return tokens;
}

bool Tokenizer::isFunction(std::string& buffer) {
    for (std::string func:functions) {
        if (buffer == func) {
            return true;
        }
    }
    return false;
}

bool Tokenizer::isOperator(char& ch) {
    for (char oper : operators) {
        if (ch == oper) {
            return true;
        }
    }
    return false;
}

