#include "caesar.h"
#include <cstdio>

int main() {
    printf(encrypt("Hello, world!", 5));
    printf(decrypt(encrypt("Hello, world!", 5), 5));
    return 0;
}
