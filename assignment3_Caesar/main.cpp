#include "caesar.h"
#include <cstdio>

int main() {
    char* result;
    result = encrypt("Hello, world!", 5);
    printf(result);
    return 0;
}
