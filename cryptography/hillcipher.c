#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "../include/matrix.h"

Matrix *str_matrix(const char *str, int rows, int cols) {
    Matrix *strmat = matrix_init(rows, cols);

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(!str) continue;
            char c = *(str++);
            if(isalpha(c)) matrix_set(strmat, i, j, c);
        }
    }
    return strmat;
}

int main(void) {

    char key[] = "Nsinghh.04@gmail.com";
    int keydim = ceil(sqrt(sizeof(key)));
    char text[] = "I use arch byy the way!";
    int textdim = ceil(sizeof(text) / (float)keydim);

    Matrix *key_matrix = str_matrix(key, keydim, keydim);
    Matrix *text_matrix = str_matrix(text, keydim, textdim);

    Matrix *product = matrix_prod(key_matrix, text_matrix);

    matrix_show(product);

    matrix_free(key_matrix);
    matrix_free(text_matrix);
    matrix_free(product);

    return 0;
}
