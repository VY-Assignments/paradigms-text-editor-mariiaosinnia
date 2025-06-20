

#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H
#include <bemapiset.h>


class CaesarCipher {
public:
    CaesarCipher(char* dll_name);
    ~CaesarCipher();

    char* encrypt(char* rawText, int key);
    char* decrypt(char* encryptedText, int key);
private:
    HINSTANCE handle;
    typedef char*(*encrypt_ptr_t)(char*, int);
    typedef char*(*decrypt_ptr_t)(char*, int);

    encrypt_ptr_t encrypt_ptr = nullptr;
    decrypt_ptr_t decrypt_ptr = nullptr;
    };



#endif
