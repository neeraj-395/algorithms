#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../include/keygen.h"

void encrypt(char *text, const char *key) {
    size_t size = strlen(text);
    for(size_t i = 0; i < size; i++) {
        if(!isalpha(text[i])) continue;
        char textBase = islower(text[i]) ? 'a': 'A';
        text[i] = key[text[i] - textBase];
    }
}

void decrypt(char *ciphertext, const char *key) {
    char rkey[27] = {0};
    size_t keyLength = strlen(key);
    for (size_t i = 0; i < keyLength; i++) {
        rkey[key[i] - 'A'] = 'A' + i;
    } encrypt(ciphertext, rkey);
}

int main(void) {
    // Generate 26 characters long key
    char key[27] = {0};
    keygen26(key);

    char plaintext[] = "Neeraj Singh";
    printf("Plain Text: %s\n", plaintext);
    printf("Key: %s\n", key);
    encrypt(plaintext, key);
    printf("Encrypted Text: %s\n", plaintext);
    decrypt(plaintext, key);
    printf("Decrypted Text: %s\n", plaintext);

    return 0;
}

