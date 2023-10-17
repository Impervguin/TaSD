#ifndef MULTIPLICATION_H__
#define MULTIPLICATION_H__
#include "matrix.h"
#include "vector.h"
#include "std_matrix.h"
#include "std_vector.h"

/**
 * @brief Функция для умножение стандартных матрицы и вектора-столбца.
 * 
 * @param [in] mat - Матрица
 * @param [in] vec - Вектор
 * @param [out] res - Результирующий вектор
 * @return int - Код возврата
 */
int mult_std(struct std_matrix_t *mat, struct std_vector_t *vec, struct std_vector_t *res);

/**
 * @brief Функция для умножения CRS матрицы и вектора-столбца
 * 
 * @param [in] mat - Матрица
 * @param [in] vec - Вектор
 * @param [out] res - Результирующий вектор
 * @return int - Код возврата
 */
int mult(struct matrix_t *mat, struct vector_t *vec, struct vector_t *res);

#endif
