#ifndef MATRIX_H
#define MATRIX_H

#define matrix_get(mat, i, j) ((mat)->data[(i) * (mat)->cols + (j)])
#define matrix_set(mat, i, j, value) ((mat)->data[(i) * (mat)->cols + (j)] = (value))

typedef unsigned long size_t;

typedef struct matrix_meta {
    double  *data; /** Pointer to a one dim array storing matrix elements. */
    unsigned rows; /** Number of rows in the matrix. */
    unsigned cols; /** Number of columns in the matrix. */
} Matrix;

/**
 * Allocates memory for a matrix with the given number of rows and columns.
 * 
 * @return Matrix structure with allocated memory.
 */
Matrix *matrix_init(size_t rows, size_t cols);

/**
 * Frees memory allocated for a matrix.
 *
 * Releases the memory associated with the matrix, including its data array.
 */
void *matrix_free(Matrix *mat);

/**
 * Displays the contents of a matrix.
 *
 * Prints the matrix elements to the standard output in a readable format.
 */
void matrix_show(Matrix *mat);

// Function pointer type for generating values for matrix elements.
typedef double (*valuefunc)();

/**
 * Populates the matrix elements by calling the provided callback function.
 * 
 * Each element is assigned a value returned by the callback.
 */
void matrix_fill(Matrix *mat, valuefunc callback);

// Defines a function for element-wise matrix operations.
typedef double (*operafunc)(double a, double b);

/**
 * Applies an element-wise operation to two matrices.
 * @return A new Matrix with the result of the operation.
 */
Matrix *matrix_op(Matrix *mat, Matrix *other_mat, operafunc op);

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
