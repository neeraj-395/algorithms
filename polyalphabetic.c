#include <stdio.h> // printf()
#include <string.h> // strlen()
#include <ctype.h> // islower(), isalpha()

#include "keygen.h" // keygen26()

typedef char (*cryptofunc)(char, char, char, char);

char encrypt(char c, char k, char cbase, char kbase) {
    return (((c - cbase) + (k - kbase)) % 26) + cbase;
}

char decrypt(char c, char k, char cbase, char kbase) {
    return (((c - cbase) - (k - kbase) + 26) % 26) + cbase;
}

void polyalphabetic(char *text, const char *key, cryptofunc crypt) {
    size_t keyLength = strlen(key);
    size_t textLength = strlen(text);
    for(size_t i = 0, j = 0; i < textLength; i++) {
        if(!isalpha(text[i])) continue;
        char textBase = islower(text[i]) ? 'a' : 'A';
        char keyBase = islower(key[j % keyLength]) ? 'a' : 'A';
        text[i] = crypt(text[i], key[j % keyLength], textBase, keyBase);
        j = j + 1;
    }
}

int main(void) {
    char key[27] = {0};
    keygen26(key); // Generate 26 characters key

    char plaintext[] = "Neeraj Singh";
    printf("PlainText: %s\n", plaintext);
    printf("Key: %s\n", key);
    polyalphabetic(plaintext, key, encrypt);
    printf("Encrypted Text: %s\n", plaintext);
    polyalphabetic(plaintext, key, decrypt);
    printf("Decrypted Text: %s\n", plaintext);
}
