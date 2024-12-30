#include <stdio.h>
#include <string.h>
#include <math.h>

#include "./inc/matlib/matrix.h"

Matrix genMatrixfromText(const char *txt, size_t rowdim) {
    const size_t txtlen = strlen(txt);
    const size_t coldim = ceil((float)txtlen / (float)rowdim);

    Matrix txtMatrix = matrix_init(rowdim, coldim);

    for(size_t i = 0, t = 0; i < rowdim; i++) {
        for(size_t j = 0; j < coldim; j++) {
            if(t <= txtlen) txtMatrix.data[i][j] = txt[t++];
        }
    } return txtMatrix;
}

char encrypt(char *plaintext, const char *key) {
    size_t txtlen = strlen(key);
    size_t keyRowDim = ceil(sqrt(txtlen));

    Matrix keyMatrix = genMatrixfromText(key, keyRowDim);
    Matrix txtMatrix = genMatrixfromText(plaintext, keyMatrix.cols);

    Matrix product = matrix_prod(&keyMatrix, &txtMatrix);

    for(size_t i = 0, k = 0; i < product.rows; i++) {
        for(size_t j = 0; j < product.cols; j++) {
            if(k <= txtlen)
            plaintext[k++] = (char)((int)product.data[i][j] % 256);
        }
    }
    matrix_free(&keyMatrix);
    matrix_free(&txtMatrix);
    matrix_free(&product);
}



int main(void) {

    char key[] = {"Nsinghh.04@gmail.com"};
    char text[] = {"I use arch byy the way!"};

   encrypt(text, key);

   printf("%s\n", text);
    return 0;
}
