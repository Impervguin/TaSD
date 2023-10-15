#ifndef MULTIPLICATION_H__
#define MULTIPLICATION_H__
#include "matrix.h"
#include "vector.h"
#include "std_matrix.h"
#include "std_vector.h"

int mult_std(struct std_matrix_t *mat, struct std_vector_t *vec, struct std_vector_t *res);
int mult(struct matrix_t *mat, struct vector_t *vec, struct vector_t *res);

#endif
