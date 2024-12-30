#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/matlib/matrix.h"

Matrix gaussian_elimination(Matrix *coefficients, Matrix *vector) {
    if(coefficients->rows != vector->rows) return (Matrix){ NULL, 0 , 0 };
    
    Matrix augmented = matrix_hconcat(coefficients, vector);

    // scale the matrix leaving it triangular
    for(size_t i = 0; i < coefficients->rows; i++) {
        double pivot = augmented.data[i][i];
        if(pivot == 0) continue;
        for(size_t j = i + 1; j < coefficients->cols; j++) {
            double factor = augmented.data[j][i] / pivot;
            for(size_t k = 0; k < augmented.cols; k++) {
                augmented.data[j][k] -= factor * augmented.data[i][k];
            }
        }
    }
    return augmented;
}

double func() {
    return rand() % 1000;
}

int main(void) {
    srand(time(NULL));

    Matrix coefficients = matrix_init(3, 3);
    Matrix vector = matrix_init(3, 3);

    matrix_fill(&coefficients, func);
    matrix_fill(&vector, func);

    Matrix result = gaussian_elimination(&coefficients, &vector);

    matrix_show(&result);
    matrix_free(&result);
    matrix_free(&coefficients);
    matrix_free(&vector);
}