#ifndef KEYGEN_H
#define KEYGEN_H

#include <string.h> // strlen(), strcpy()
#include <stdlib.h> // size_t, rand(), srand()
#include <time.h> // time()

const char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void shuffle(char *str) {
    size_t length = strlen(str);
    srand(time(NULL));
    for(size_t i = 0; i < length; i++) {
        size_t randinx = rand() % length;
        char temp = str[i];
        str[i] = str[randinx];
        str[randinx] = temp;
    }
}

void keygen26(char *key) {
    strcpy(key, alphabets);
    shuffle(key);
}

#endif // KEYGEN_H