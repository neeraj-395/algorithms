#include <stdio.h>
#include <math.h>

#include "../include/matlib/matrix.h"

static void matrix_augment_identity(Matrix *mat, double augmented[][mat->cols * 2]) {
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < mat->cols; j++) {
            augmented[i][j] = mat->data[i][j];
        }
        for(size_t k = mat->cols; k < (mat->cols * 2); k++) {
            augmented[i][k] = (k - mat->cols == i) ? 1.0 : 0.0;
        }
    }
}

Matrix matrix_inverse(Matrix *mat) {
    if(!mat || mat->cols != mat->rows) return (Matrix) {NULL, 0, 0};

    double augmented[mat->rows][mat->cols * 2];

    matrix_augment_identity(mat, augmented);

    for(size_t i = 0; i < mat->rows; i++) {
        // Fine row pivot!
        size_t pivot_row = i;
        for(size_t j = i + 1; j < mat->rows; j++) {
            if(fabs(augmented[j][i]) > fabs(augmented[pivot_row][i])) {
                pivot_row = j;
            }
        }
        // Swap rows (if necessary)
        if(pivot_row != i) {
            for(size_t j = 0; j < mat->cols * 2; j++) {
                double temp = augmented[i][j];
                augmented[i][j] = augmented[pivot_row][j];
                augmented[pivot_row][j] = temp;
            }
        }
        // Make pivot element 1
        double pivot_element = augmented[i][i];

        if(fabs(pivot_element) < 1e-6) {
            // Matrix is singular (no inverse)
            return (Matrix){ NULL, 0, 0 };
        }

        for(size_t j = 0; j < mat->cols * 2; j++) {
            augmented[i][j] /= pivot_element;
        }

        // Eliminate other elements in the column
        for (int j = 0; j < mat->rows; j++) {
            if (j == i) continue;
            double factor = augmented[j][i];
            for (int k = 0; k < mat->cols * 2; k++) {
                augmented[j][k] -= factor * augmented[i][k];
            }
        }
    }

    // Obtain inverse matrix!
    Matrix result = matrix_init(mat->rows, mat->cols);
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < mat->cols; j++) {
            result.data[i][j] = augmented[i][j + mat->cols];
        }
    } return result;
}
