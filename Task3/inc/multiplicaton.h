#ifndef MULTIPLICATION_H__
#define MULTIPLICATION_H__
#include "matrix.h"
#include "vector.h"
#include "std_matrix.h"
#include "std_vector.h"

int mult_std(std_matrix_t *mat, std_vector_t *vec, std_vector_t *res);
int mult(matrix_t *mat, vector_t *vec, vector_t *res);

#endif
