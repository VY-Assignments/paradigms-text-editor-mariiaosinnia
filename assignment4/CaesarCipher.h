#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H
#include <bemapiset.h>


class CaesarCipher {
public:
    CaesarCipher(char* dll_name);
    ~CaesarCipher();

    char* encrypt(char* rawText, int key, int length);
    char* decrypt(char* encryptedText, int key, int length);
private:
    HINSTANCE handle;
    typedef char*(*encrypt_ptr_t)(char*, int, int);
    typedef char*(*decrypt_ptr_t)(char*, int, int);

    encrypt_ptr_t encrypt_ptr = nullptr;
    decrypt_ptr_t decrypt_ptr = nullptr;
    };



#endif
