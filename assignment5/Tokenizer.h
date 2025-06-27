#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>


class Tokenizer {
private:
    std::vector<std::string> tokens;
    std::vector<std::string> functions = {"pow", "abs", "max", "min"};
    std::vector<char> operators = {'+', '-', '*', '/', '(', ')', ','};
public:
    std::vector<std::string> tokenization(std::string& expression);
    bool isFunction(std::string buffer);
    bool isOperator(char ch);
};



#endif
