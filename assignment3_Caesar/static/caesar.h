#ifndef CAESAR_H
#define CAESAR_H

extern const char* ALPHABET;

char* encrypt(char* rawText, int key);
char* decrypt(char* encryptedText, int key);

#endif
