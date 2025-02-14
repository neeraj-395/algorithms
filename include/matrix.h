#ifndef MATRIX_H
#define MATRIX_H

#define matrix_get(mat, i, j) ((mat)->data[(i) * (mat)->cols + (j)])
#define matrix_set(mat, i, j, value) ((mat)->data[(i) * (mat)->cols + (j)] = (value))

typedef unsigned long size_t;

typedef struct matrix_meta {
    double  *data; /** Matrix elements stored in 1D array. */
    unsigned rows; /** Number of rows in the matrix. */
    unsigned cols; /** Number of columns in the matrix. */
} Matrix;

/**
 * Allocates memory for a matrix with the given number of rows and columns.
 * 
 * @return Pointer to the created matrix.
 */
Matrix *matrix_create(size_t rows, size_t cols);

/**
 * Allocates memory for matrix and initialize it given data
 * 
 * @return Pointer to the initialized matrix.
 */
Matrix *matrix_init(size_t rows, size_t cols, const double data[rows][cols]);

// Frees memory allocated for a matrix.
void *matrix_free(Matrix *mat);

// Displays the contents of a matrix.
void matrix_show(Matrix *mat);

// Callback function used to fill matrix.
typedef double (*matfill)(double value);

// Function to fill matrix using a callback valuefunc.
void matrix_fill(Matrix *mat, matfill valuefunc);


// Defines a function for element-wise matrix operations.
typedef double (*operation)(double a, double b);

/**
 * Applies an element-wise operation to two matrices.
 * @return A new matrix with the result of the operation.
 */
Matrix *matrix_elementwise(Matrix *mat, Matrix *other_mat, operation func);

/**
 * Computes the product of two matrices using matrix multiplication rules.
 *
 * @return Resulting matrix after multiplication.
 * 
 * @note The number of columns in `mat` must equal the number of rows in `other_mat`.
 */
Matrix *matrix_prod(Matrix *mat, Matrix *other_mat);

/**
 * Computes the inverse of a matrix.
 * 
 * @return Inverse of the matrix
 * 
 * @note The matrix must be sqaure and non-singular.
 */
Matrix *matrix_inverse(Matrix *mat);

/**
 * Horizontally concatenate two matrices.
 * 
 * @return New concatenated matrix.
 */
Matrix *matrix_hconcat(Matrix *mat, Matrix *other);

/**
 * Vertically concatenate two matrices.
 *
 * @return New concatenated matrix.
 */
Matrix *matrix_vconcat(Matrix *mat, Matrix *other);

/**
 * Perform gaussian elimination with two matrices.
 * 
 * @return new resultant matrix.
 */
Matrix *gaussian_elimination(Matrix *coefficients, Matrix *vector);

#endif // MATRIX_H
