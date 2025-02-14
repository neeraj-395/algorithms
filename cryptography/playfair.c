// TODO: Implement playfair using matrix library!
// Matrix library path include folder!

#include <stdio.h>
#include "../include/matrix.h"

int main(void) {
    Matrix *mat = matrix_init(5, 5, (double[][5]) {
        {'A', 'B', 'C', 'D', 'E'},
        {'F', 'G', 'H', 'I', 'K'},
        {'L', 'M', 'N', 'O', 'P'},
        {'Q', 'R', 'S', 'T', 'U'},
        {'V', 'W', 'X', 'Y', 'Z'},
    });

    matrix_show(mat);

    matrix_free(mat);

    return 0;
}