#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/matrix.h"

Matrix *gaussian_elimination(Matrix *coefficients, Matrix *vector) {
    if(!coefficients || !vector || coefficients->rows != vector->rows) {
        return NULL;
    }
    
    Matrix *augmented = matrix_hconcat(coefficients, vector);

    // scale the matrix leaving it triangular
    for(size_t i = 0; i < coefficients->rows; i++) {
        double pivot = matrix_get(augmented, i, i);
        if(pivot == 0) continue;
        for(size_t j = i + 1; j < coefficients->cols; j++) {
            double factor = matrix_get(augmented, j, i) / pivot;
            for(size_t k = 0; k < augmented->cols; k++) {
                double target = matrix_get(augmented, j, k);
                double pivot_row = matrix_get(augmented, i , k);
                matrix_set(augmented, j, k, target - factor * pivot_row);
            }
        }
    }
    return augmented;
}