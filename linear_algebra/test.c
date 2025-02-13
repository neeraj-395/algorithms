#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/matrix.h"

double func(double _) {
    (void)_;
    return rand() % 1000;
}

int main(void) {
    srand(time(NULL));

    Matrix *m1 = matrix_init(3, 3);
    Matrix *m2 = matrix_init(3, 3);

    matrix_fill(m1, func);
    matrix_fill(m2, func);

    matrix_show(m1);
    matrix_show(m2);

    Matrix *result = matrix_vconcat(m1, m2);

    matrix_show(result);

    matrix_free(result);
    matrix_free(m1);
    matrix_free(m2);
}