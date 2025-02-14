#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/matrix.h"

int main(void) {
    srand(time(NULL));

    Matrix *m1 = matrix_init(3, 3, (double[][3]) {
        {1.0, 2.0, 3.0},
        {4.0, 1.0, 6.0},
        {7.0, 8.0, 1.0}
    });

    Matrix *m2 = matrix_init(3, 3, (double[][3]) {
        {2.0, 8.0, 14.0},
        {4.0, 10.0, 16.0},
        {6.0, 12.0, 18.0}
    });

    matrix_show(m1);
    matrix_show(m2);

    Matrix *result = matrix_vconcat(m1, m2);

    matrix_show(result);

    matrix_free(result);
    matrix_free(m1);
    matrix_free(m2);
}