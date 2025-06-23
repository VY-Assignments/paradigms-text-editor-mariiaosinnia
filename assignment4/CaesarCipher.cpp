#include "CaesarCipher.h"

#include <combaseapi.h>
#include <cstdio>

CaesarCipher::CaesarCipher(char *dll_name) {
    handle = LoadLibrary(TEXT("caesar.dll"));
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE) {
        printf("Lib is not found");
        return;
    }
    encrypt_ptr = (encrypt_ptr_t)GetProcAddress(handle, "encrypt");
    if (encrypt_ptr == nullptr) {
        printf("Lib is not found");
        return;
    }

    decrypt_ptr = (decrypt_ptr_t)GetProcAddress(handle, "decrypt");
    if (decrypt_ptr == nullptr) {
        printf("Lib is not found");
        return;
    }
}

char* CaesarCipher::encrypt(char* rawText, int key, int length) {
    return encrypt_ptr(rawText, key, length);
}

char* CaesarCipher::decrypt(char* encryptedText, int key, int length) {
    return decrypt_ptr(encryptedText, key, length);
}


CaesarCipher::~CaesarCipher() {
    FreeLibrary(handle);
}




