#include <cstdio>
#include <windows.h>
typedef char*(*encrypt_ptr_t)(char*, int);
typedef char*(*decrypt_ptr_t)(char*, int);
typedef const char* alphabet_ptr_t;

int main() {
    HINSTANCE handle = LoadLibrary(TEXT("caesar.dll"));
    if(handle == nullptr || handle == INVALID_HANDLE_VALUE) {
        printf("Lib is not found");
        return 1;
    }

    encrypt_ptr_t encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, TEXT("encrypt"));
    if (encrypt_ptr == nullptr) {
        printf("Lib is not found");
        return 1;
    }

    decrypt_ptr_t decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, TEXT("decrypt"));
    if (decrypt_ptr == nullptr) {
        printf("Lib is not found");
        return 1;
    }

    alphabet_ptr_t alphabet_ptr = (alphabet_ptr_t)GetProcAddress(handle, "ALPHABET");
    if (!alphabet_ptr) {
        printf("Constant not found");
        return 1;
    }

    const char* input = "Roses are red, violets are blue";
    int key = 1;

    char* encrypted = encrypt_ptr((char*)input, key);
    printf("Encrypted: %s\n", encrypted);

    char* decrypted = decrypt_ptr(encrypted, key);
    printf("Decrypted: %s\n", decrypted);

    delete[] encrypted;
    delete[] decrypted;

    FreeLibrary(handle);
    return 0;
}
