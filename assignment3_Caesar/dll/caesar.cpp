#include <cctype>
#include <cstring>

extern "C"{
    static char* last_allocated = nullptr;

    __declspec(dllexport) const char* ALPHABET = "abcdefghijklmnopqrstuvwxyz";

    __declspec(dllexport) char* encrypt(char* rawText, int key, int length) {
        if (last_allocated) {
            delete[] last_allocated;
            last_allocated = nullptr;
        }
        last_allocated = new char[length];
        int position = 0;

        for (int i = 0; i < length; i++) {
            bool is_upper = isupper(rawText[i]);

            if (!isalpha(rawText[i])) {
                last_allocated[position++] = rawText[i];
                continue;
            }
            for (int j = 0; j < strlen(ALPHABET); j++) {
                if (tolower(rawText[i]) == ALPHABET[j]) {
                    char encrypted_char = ALPHABET[(j + key) % 26];

                    if (is_upper) {
                        encrypted_char = toupper(encrypted_char);
                    }
                    last_allocated[position++] = encrypted_char;
                    break;
                }
            }
        }
        last_allocated[position] = '\0';

        return last_allocated;
    }

    __declspec(dllexport) char* decrypt(char* encryptedText, int key, int length) {
        if (last_allocated) {
            delete[] last_allocated;
            last_allocated = nullptr;
        }
        int position = 0;
        last_allocated = new char[length];

        for (int i = 0; i < length; i++) {
            bool is_upper = isupper(encryptedText[i]);

            if (!isalpha(encryptedText[i])) {
                last_allocated[position++] = encryptedText[i];
                continue;;
            }
            for (int j = 0; j < strlen(ALPHABET); j++) {
                if (tolower(encryptedText[i]) == ALPHABET[j]) {
                    char decrypted_char = ALPHABET[(j - key + 26) % 26];

                    if (is_upper) {
                        decrypted_char = toupper(decrypted_char);
                    }
                    last_allocated[position++] = decrypted_char;
                    break;
                }
            }
        }
        last_allocated[position] = '\0';

        return last_allocated;
    }
}





