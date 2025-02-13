#include <stdio.h>
#include <string.h>

int main(void) {
    for(unsigned i = 0; i < 255; i++) {
        if(i >= '!') printf("<%c> ", i);
        else continue;
        if(i % 10 == 0) printf("\n");
    }
}
