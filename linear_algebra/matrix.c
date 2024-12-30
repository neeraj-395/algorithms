#include <stdio.h>
#include <stdlib.h>

#include "../include/matlib/matrix.h"

Matrix matrix_init(size_t numRow, size_t numCol) {
    if(numRow == 0 || numCol == 0) return (Matrix) {NULL, 0, 0};
    double **data = (double **) calloc(numRow, sizeof(double *));

    for(size_t i = 0; i < numRow; i++) {
        data[i] = (double *) calloc(numCol, sizeof(double));
    } return (Matrix) {data, numRow, numCol};
}

void matrix_free(Matrix *mat) {
    if(!mat || !mat->data) return;
    for(size_t i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }  free(mat->data); mat->data = NULL;
}

void matrix_show(Matrix *mat) {
    if(!mat->data) {  printf("Matrix has no data to show!\n"); return; }
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < mat->cols; j++) {
            printf("\t%f", mat->data[i][j]);
        } printf("\n");
    } printf("\n");
}

void matrix_fill(Matrix *mat, valuefunc callback) {
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < mat->cols; j++) {
            mat->data[i][j] = callback();
        }
    }
}

Matrix matrix_op(Matrix *mat, Matrix *other_mat, operafunc __op) {
    if(!mat || !other_mat || mat->cols != other_mat->cols
        || mat->rows != other_mat->rows) {
        return (Matrix) {NULL, 0, 0};
    }
    Matrix new_mat = matrix_init(mat->rows, other_mat->cols);
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < other_mat->cols; j++) {
            new_mat.data[i][j] = __op(mat->data[i][j], other_mat->data[i][j]);
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

Matrix matrix_hconcat(Matrix *mat, Matrix *other) {
    if(mat->rows != other->rows) return (Matrix) { NULL, 0 , 0 };
    Matrix concatenated = matrix_init(mat->rows, mat->cols + other->cols);

    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < mat->cols; j++) {
            concatenated.data[i][j] = mat->data[i][j];
        }
        for(size_t k = 0; k < other->cols; k++) {
            concatenated.data[i][k + mat->cols] = other->data[i][k];
        }
    } return concatenated;
}

Matrix matrix_vconcat(Matrix *mat, Matrix *other) {
    if(mat->cols != other->cols) return (Matrix) { NULL, 0 , 0 };
    Matrix concatenated = matrix_init(mat->rows + other->rows, mat->cols);

    for(size_t i = 0; i < mat->cols; i++) {
        for(size_t j = 0; j < mat->rows; j++) {
            concatenated.data[j][i] = mat->data[j][i];
        }
        for(size_t k = 0; k < other->rows; k++) {
            concatenated.data[k + mat->rows][i] = other->data[k][i];
        }
    } return concatenated;
}

