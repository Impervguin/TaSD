#ifndef MATRIX_H__
#define MATRIX_H__
#include <stddef.h>
#include <stdio.h>
#include "std_matrix.h"

typedef struct matrix_t matrix_t;

/// Структура матрицы в формате CRS.
struct matrix_t
{
    size_t rows; /// Количество строк в матрице.
    size_t cols; /// Количество столбцов в матрице.
    size_t elems; /// Количество ненулевых элементов в матрице.
    int *arr; /// Массив ненулевых элементов в матрице. Имеет размер равный elems.
    size_t *jarr; /// Массив индексов столбцов соответствующих элементов из arr. Имеет размер равный elems.
    size_t *ia; /// Массив индексов, с которых начинается описание i-ой строки. Например описание 2-ой(начиная с 0) строки начинается с элемента с индексом ia[2]. Имеет размер rows + 1.
};

/**
 * @brief Функция для динамического создания CRS матрицы
 * 
 * @param [in/out] mat - Указатель на CRS матрицы.
 * @return int - Код возврата. 
 */
int create_matrix(struct matrix_t *mat);

/**
 * @brief Функция для освобождения динамической CRS матрицы.
 * 
 * @param [in/out] mat - Указатель на CRS матрицу.
 */
void free_matrix(struct matrix_t *mat);

/**
 * @brief Функция для чтения CRS матрицы в координатной форме из файла.
 * 
 * @param [in/out] f - Файл.
 * @param [out] mat - Указатель на CRS матрицу.
 * @param [in] verbose - Переменная, задающая доп. вывод при вводе. 
 * @return int - Код возврата.
 */
int read_matrix(FILE *f, struct matrix_t *mat, int verbose);

/**
 * @brief Функция для стандартного вывода CRS матрицы.
 * 
 * @param [in/out] f - Файл.
 * @param [in] mat - Указатель на CRS матрицу.
 * @return int - Код возврата.
 */
int print_matrix(FILE *f, struct  matrix_t *mat);

/**
 * @brief Функция для координатного вывода CRS матрицы.
 * 
 * @param [in/out] f - Файл.
 * @param [in] mat - Указатель на CRS матрицу.
 * @return int - Код возврата.
 */
int write_matrix(FILE *f, struct  matrix_t *mat);

/**
 * @brief Функция для подсчета занимаемой CRS матрице памяти.
 * 
 * @param [in] mat - Указатель на CRS матрицу.
 * @return size_t - Объем памяти в байтах.
 */
size_t count_matrix_size(struct matrix_t *mat);

/**
 * @brief Функция для перевода стандартной матрицы в CRS
 * 
 * @param [in] std_mat - Стандартная матрица.
 * @param [out] mat - CRS матрица.
 * @return int - Код возврата.
 */
int std_to_mat(std_matrix_t *std_mat, matrix_t *mat);

#endif
