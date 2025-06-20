#include "CaesarCipher.h"

#include <combaseapi.h>
#include <cstdio>

CaesarCipher::CaesarCipher(char *dll_name) {
    HINSTANCE handle = LoadLibrary(TEXT("caesar.dll"));
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

char* CaesarCipher::encrypt(char* rawText, int key) {
    return encrypt_ptr(rawText, key);
}

char* CaesarCipher::decrypt(char* encryptedText, int key) {
    return decrypt_ptr(encryptedText, key);
}


CaesarCipher::~CaesarCipher() {
    FreeLibrary(handle);
}



