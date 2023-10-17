#ifndef VECTOR_H__
#define VECTOR_H__
#include <stddef.h>
#include <stdio.h>
#include "std_vector.h"

typedef struct vector_t vector_t;

/// Вектор в формате CRS.
struct vector_t
{
    size_t size; /// Размер вектора.
    size_t elems; /// Количество ненулевых элементов в векторе.
    int *arr; /// Массив ненулевых элементов в векторе. Имеет размер elems.
    size_t *iarr; /// Массив индексов ненулевых элементов соответствующих из arr. Имеет размер elems.
};

/**
 * @brief Функция для динамического выделения памяти под CRS вектор.
 * Для выделения памяти должен быть указано поле size.
 * @param [out] vec - Указатель на CRS вектор.
 * @return int - Код возврата.
 */
int create_vector(struct vector_t *vec);

/**
 * @brief Функция для перевыделения памяти по CRS вектор.
 * 
 * @param [in/out] vec - Указатель на CRS вектор.
 * @return int - Код возврата 
 */
int realloc_vector(struct vector_t *vec);

/**
 * @brief Функция для освобождения динамической памяти из-под CRS вектора.
 * 
 * @param [in/out] vec - Указатель на CRS вектор. 
 */
void free_vector(struct vector_t *vec);

/**
 * @brief Функция для чтения CRS вектора, заданного в координатном формате, из файла.
 * 
 * @param [in/out] f - Файл.
 * @param [out] vec - Указатель на CRS вектор.
 * @param [in] verbose - Переменная, задающая доп. вывод при вводе.
 * @return int - Код возврата.
 */
int read_vector(FILE *f, struct vector_t *vec, int verbose);

/**
 * @brief Функция для вывода CRS вектора в стандартном формате.
 * 
 * @param [in/out] f - Файл.
 * @param [in] vec - Указатель на CRS вектор.
 * @return int - Код возврата.
 */
int print_vector(FILE *f, struct vector_t *vec);

/**
 * @brief Функция для вывода CRS вектора в координатном формате.
 * 
 * @param [in/out] f - Файл.
 * @param [in] vec - Указатель на CRS вектор
 * @return int - Код возврата.
 */
int write_vector(FILE *f, struct vector_t *vec);

/**
 * @brief Функция, которая считает объем занимаемой CRS вектором память.
 * 
 * @param [in] vec - Указатель на CRS вектор.
 * @return size_t - Объем памяти в байтах.
 */
size_t count_vector_size(struct vector_t *vec);

/**
 * @brief Функция для перевода стандартного вектора в CRS.
 * 
 * @param [in] std_vec - Указатель на стандартный вектор.
 * @param [out] vec - Указатель на CRS вектор. 
 * @return int - Код возврата.
 */
int std_to_vec(std_vector_t *std_vec, vector_t *vec);

#endif
