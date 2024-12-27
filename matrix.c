#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

Matrix matrix_init(size_t numRow, size_t numCol) {
    if(numRow == 0 || numCol == 0) return (Matrix) {NULL, 0, 0};
    double **data = (double **) calloc(numRow, sizeof(double *));
    for(size_t i = 0; i < numRow; i++) {
        data[i] = (double *) calloc(numCol, sizeof(double));
    } return (Matrix) {data, numRow, numCol};
}

void matrix_free(Matrix *mat) {
    if(!mat || !mat->data) return;
    for(size_t i = 0; i < mat->rows; i++) free(mat->data[i]);
    free(mat->data); mat->data = NULL;
}

void matrix_show(Matrix *mat) {
    if(!mat->data) {
        printf("Matrix has no data to show!\n");
        return;
    }
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < mat->cols; j++) {
            printf("\t%f", mat->data[i][j]);
        } printf("\n");
    }
}

void matrix_fill(Matrix *mat, valuefunc callback) {
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < mat->cols; j++) {
            mat->data[i][j] = callback();
        }
    }
}

Matrix matrix_add(Matrix *mat, Matrix *other_mat) {
    if(!mat || !other_mat || mat->cols != other_mat->cols
        || mat->rows != other_mat->rows) {
        return (Matrix) {NULL, 0, 0};
    }
    Matrix new_mat = matrix_init(mat->rows, other_mat->cols);
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < other_mat->cols; j++) {
            new_mat.data[i][j] = mat->data[i][j] + other_mat->data[i][j];
        }
    } return new_mat;
}

Matrix matrix_prod(Matrix *mat, Matrix *other_mat) {
    if(!mat || !other_mat || mat->cols != other_mat->rows) {
        return (Matrix) {NULL, 0, 0};
    }

    Matrix new_mat = matrix_init(mat->rows, other_mat->cols);
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < other_mat->cols; j++) {
            for(size_t k = 0; k < mat->cols; k++) {
                new_mat.data[i][j] += mat->data[i][k] * other_mat->data[k][j];
            }
        }
    } return new_mat;
}

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
