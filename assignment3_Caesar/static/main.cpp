#include <cstdio>
#include "caesar.h"

int main() {
    const char* text = "Roses are red, violets are blue";
    int key = 1;

    char* encrypted = encrypt((char*)text, key);
    printf("Encrypted:%s\n", encrypted);

    char* decrypted = decrypt(encrypted, key);
    printf("Decrypted:%s\n", decrypted);

    delete[] encrypted;
    delete[] decrypted;

    return 0;
}
