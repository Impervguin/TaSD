#ifndef STD_MATRIX_H__
#define STD_MATRIX_H__
#include <stddef.h>
#include <stdio.h>

typedef struct std_matrix_t std_matrix_t;

/// Стандартная матрица.
struct std_matrix_t
{
    size_t rows; /// Количество строк в матрице.
    size_t cols; /// Количество столбцов в матрице.
    int **matrix; /// Массив указателей на строки матрицы.
};

/**
 * @brief Функция для динамического создания матрицы
 * 
 * @param mat - Указатель на матрицы.
 * @return int - Код возврата. 
 */
int create_std_matrix(struct std_matrix_t *mat);

/**
 * @brief Функция для освобождения динамической матрицы.
 * 
 * @param mat - Указатель на матрицу.
 */
void free_std_matrix(struct std_matrix_t *mat);

/**
 * @brief Функция для чтения матрицы в координатной форме из файла.
 * 
 * @param f - Файл.
 * @param mat - Указатель на матрицу.
 * @param verbose - Переменная, задающая доп. вывод при вводе. 
 * @return int - Код возврата.
 */
int read_std_matrix(FILE *f, struct std_matrix_t *mat, int verbose);

/**
 * @brief Функция для стандартного вывода матрицы.
 * 
 * @param f - Файл.
 * @param mat - Указатель на матрицу.
 * @return int - Код возврата.
 */
int print_std_matrix(FILE *f, struct std_matrix_t *mat);

/**
 * @brief Функция для координатного вывода матрицы.
 * 
 * @param f - Файл.
 * @param mat - Указатель на матрицу.
 * @return int - Код возврата.
 */
int write_std_matrix(FILE *f, struct std_matrix_t *mat);

/**
 * @brief Функция для подсчета занимаемой матрице памяти.
 * 
 * @param mat - Указатель на матрицу.
 * @return size_t - Объем памяти в байтах.
 */
size_t count_std_matrix_size(struct std_matrix_t *mat);

#endif
