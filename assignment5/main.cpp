#include <iostream>
#include <string>

#include "SortingStation.h"
#include "Tokenizer.h"

int main() {
    std::string input;
    std::cout << "Enter an expression: ";
    std::getline(std::cin, input);

    Tokenizer tokenizer;
    std::vector<std::string> tokens = tokenizer.tokenization(input);

    std::cout << "Tokens:\n";
    for (const auto& t : tokens) {
        std::cout << t << " ";
    }
    std::cout << "\n";

    SortingStation station(tokens);
    station.Sorting(tokens);

    std::cout << "RPN:\n";
    while (!station.queue.empty()) {
        std::cout << station.queue.front() << " ";
        station.queue.pop();
    }
    std::cout << "\n";

    return 0;
}
