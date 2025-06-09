#include <cctype>
#include <cstring>
#include "caesar.h"


const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz";

char* encrypt(char* rawText, int key) {
    char* encrypted_text = new char[strlen(rawText) + 1];
    int position = 0;

    for (int i = 0; i < strlen(rawText); i++) {
        bool is_upper = isupper(rawText[i]);

        if (!isalpha(rawText[i])) {
            encrypted_text[position++] = rawText[i];
        }
        for (int j = 0; j < strlen(ALPHABET); j++) {
            if (tolower(rawText[i]) == ALPHABET[j]) {
                char encrypted_char = ALPHABET[(j + key) % 26];

                if (is_upper) {
                    encrypted_char = toupper(encrypted_char);
                }
                encrypted_text[position++] = encrypted_char;
                break;
            }
        }
    }
    encrypted_text[position] = '\0';

    return encrypted_text;
}

char* decrypt(char* encryptedText, int key) {
    char* decrypted_text = new char[strlen(encryptedText)];
    int position = 0;

    for (int i = 0; i < strlen(encryptedText); i++) {
        bool is_upper = isupper(encryptedText[i]);

        if (!isalpha(encryptedText[i])) {
            decrypted_text[position++] = encryptedText[i];
        }
        for (int j = 0; j < strlen(ALPHABET); j++) {
            if (tolower(encryptedText[i]) == ALPHABET[j]) {
                char decrypted_char = ALPHABET[(j - key + 26) % 26];

                if (is_upper) {
                    decrypted_char = toupper(decrypted_char);
                }
                decrypted_text[position++] = decrypted_char;
                break;
            }
        }
    }
    decrypted_text[position] = '\0';

    return decrypted_text;
}





