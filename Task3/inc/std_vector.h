#ifndef STD_VECTOR_H__
#define STD_VECTOR_H__
#include <stddef.h>
#include <stdio.h>

typedef struct std_vector_t std_vector_t;

/// Стандартный вектор
struct std_vector_t
{
    size_t size; /// Размер вектора.
    int *arr; /// Массив элементов вектора.
};

/**
 * @brief Функция для динамического выделения памяти под вектор.
 * Для выделения памяти должен быть указано поле size.
 * @param [out] vec - Указатель на вектор.
 * @return int - Код возврата.
 */
int create_std_vector(struct std_vector_t *vec);

/**
 * @brief Функция для освобождения динамической памяти из под вектора.
 * 
 * @param [in/out] vec - Указатель на вектор. 
 */
void free_std_vector(struct std_vector_t *vec);

/**
 * @brief Функция для чтения вектора, заданного в координатном формате, из файла.
 * 
 * @param [in/out] f - Файл.
 * @param [out] vec - Указатель на вектор.
 * @param [in] verbose - Переменная, задающая доп. вывод при вводе.
 * @return int - Код возврата.
 */
int read_std_vector(FILE *f, struct std_vector_t *vec, int verbose);

/**
 * @brief Функция для вывода вектора в стандартном формате.
 * 
 * @param [in/out] f - Файл.
 * @param [in] vec - Указатель на вектор.
 * @return int - Код возврата.
 */
int print_std_vector(FILE *f, struct std_vector_t *vec);

/**
 * @brief Функция для вывода вектора в координатном формате.
 * 
 * @param [in/out] f - Файл.
 * @param [in] vec - Указатель на вектор
 * @return int - Код возврата.
 */
int write_std_vector(FILE *f, struct std_vector_t *vec);

/**
 * @brief Функция, которая считает объем занимаемой вектором память.
 * 
 * @param [in] vec - Указатель на вектор.
 * @return size_t - Объем памяти в байтах.
 */
size_t count_std_vector_size(struct std_vector_t *vec);

#endif
