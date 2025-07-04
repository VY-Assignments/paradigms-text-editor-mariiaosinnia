#ifndef NODE_H
#define NODE_H
#include <string>
#include <unordered_map>


class Node {
public:
    virtual ~Node() {}
    virtual double evaluate(std::unordered_map<std::string, double>& vars) = 0;
};


#endif
