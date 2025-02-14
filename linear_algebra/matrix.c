#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/matrix.h"

Matrix *matrix_create(size_t rows, size_t cols) {
    if(!rows || !cols) return NULL;
    Matrix *mat = malloc(sizeof(Matrix));
    mat->data = calloc(rows * cols, sizeof(double));
    mat->rows = rows; mat->cols = cols;
    return mat;
}

Matrix *matrix_init(size_t rows, size_t cols, const double data[rows][cols]) {
    Matrix *mat = matrix_create(rows, cols);
    memcpy(mat->data, data, rows * cols * sizeof(double));
    return mat;
}

void *matrix_free(Matrix *mat) {
    if(!mat) return NULL;
    if(mat->data) free(mat->data);
    free(mat); return NULL;
}

void matrix_show(Matrix *mat) {
    if(!mat || !mat->data) {  
        printf("Matrix has no data to show!\n"); 
        return; 
    }
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < mat->cols; j++) {
            printf("%f\t", matrix_get(mat, i , j));
        } printf("\n");
    } printf("\n");
}

void matrix_fill(Matrix *mat, matfill callback) {
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < mat->cols; j++) {
            matrix_set(mat, i, j, callback(matrix_get(mat, i, j)));
        }
    }
}

Matrix *matrix_elementwise(Matrix *mat, Matrix *other, operation func) {
    if(!mat || !other || mat->cols != other->cols
    || mat->rows != other->rows) return NULL;
    
    Matrix *new_mat = matrix_create(mat->rows, other->cols);
    for(size_t i = 0; i < (mat->rows * mat->cols); i++) {
        new_mat->data[i] = func(mat->data[i], other->data[i]); 
    } return new_mat;
}

Matrix *matrix_prod(Matrix *mat, Matrix *other) {
    if(!mat || !other || mat->cols != other->rows) return NULL;

    Matrix *new_mat = matrix_create(mat->rows, other->cols);
    
    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < other->cols; j++) {
            double product = 0.0;
            for(size_t k = 0; k < mat->cols; k++) {
                product += matrix_get(mat, i, k) * matrix_get(other, k, j);
            } matrix_set(new_mat, i , j, product);
        }
    } return new_mat;
}

Matrix *matrix_hconcat(Matrix *mat, Matrix *other) {
    if(!mat || !other || mat->rows != other->rows) return NULL;
    Matrix *hconcat = matrix_create(mat->rows, mat->cols + other->cols);

    for(size_t i = 0; i < mat->rows; i++) {
        for(size_t j = 0; j < mat->cols; j++) {
            matrix_set(hconcat, i , j, matrix_get(mat, i , j));
        }
        for(size_t k = 0; k < other->cols; k++) {
            matrix_set(hconcat, i, k + mat->cols, matrix_get(other, i, k));
        }
    } return hconcat;
}

Matrix *matrix_vconcat(Matrix *mat, Matrix *other) {
    if(!mat || !other || mat->rows != other->rows) return NULL;
    Matrix *vconcat = matrix_create(mat->rows + other->rows, mat->cols);

    size_t matsize = mat->rows * mat->cols * sizeof(double);
    size_t othersize = other->rows * other->cols * sizeof(double);

    memcpy(vconcat->data, mat->data, matsize);
    memcpy(&vconcat->data[mat->rows * mat->cols], other->data, othersize);
    
    return vconcat;
}