#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix_meta {
    double **data; /** Pointer to a 2D array storing matrix elements. */
    unsigned rows; /** Number of rows in the matrix. */
    unsigned cols; /** Number of columns in the matrix. */
} Matrix;

/**
 * @typedef valuefunc
 * @brief Function pointer type for generating values for matrix elements.
 *
 * This function should return a `double` value when called.
 */
typedef double (*valuefunc)();

/**
 * @brief Initializes a matrix with specified dimensions.
 *
 * Allocates memory for a matrix with the given number of rows and columns.
 *
 * @return Matrix structure with allocated memory.
 */
Matrix matrix_init(size_t numRow, size_t numCol);

/**
 * @brief Frees memory allocated for a matrix.
 *
 * Releases the memory associated with the matrix, including its data array.
 */
void matrix_free(Matrix *mat);

/**
 * @brief Displays the contents of a matrix.
 *
 * Prints the matrix elements to the standard output in a readable format.
 */
void matrix_show(Matrix *mat);

/**
 * @brief Fills a matrix using a callback function.
 *
 * Populates the matrix elements by calling the provided callback function.
 * Each element is assigned a value returned by the callback.
 */
void matrix_fill(Matrix *mat, valuefunc callback);

/**
 * @brief Adds two matrices.
 *
 * Performs element-wise addition of two matrices of the same dimensions.
 * 
 * @return Resulting matrix after addition.
 * @note The dimensions of `mat` and `other_mat` must match.
 */
Matrix matrix_add(Matrix *mat, Matrix *other_mat);

/**
 * @brief Multiplies two matrices.
 *
 * Computes the product of two matrices using matrix multiplication rules.
 *
 * @return Resulting matrix after multiplication.
 * @note The number of columns in `mat` must equal the number of rows in `other_mat`.
 */
Matrix matrix_prod(Matrix *mat, Matrix *other_mat);

/**
 * @brief Computes the inverse of a matrix.
 *
 * Calculates the inverse of a square matrix, if it exists.
 * 
 * @return Inverse of the matrix.
 * @note The matrix must be square and non-singular.
 */
Matrix matrix_inverse(Matrix *mat);

#endif // MATRIX_H
