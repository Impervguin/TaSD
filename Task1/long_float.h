#ifndef LONG_FLOAT_H__
#define LONG_FLOAT_H__

#include <stddef.h>

#define MAX_MANTISS_SIZE 40
#define CELL_BASE 10


struct long_float
{
    char mant_sign;
    int mantiss[MAX_MANTISS_SIZE];
    int order;
    size_t size;
};

/**
 * @brief Зануляет все значения длинного числа
 * 
 * @param [out] lf - Длинное число
 */
void make_lf_null(struct long_float *lf);

/**
 * @brief Переводит строку в длинное число
 * 
 * @param [in] str - Строка
 * @param [out] lf - Указатель на длинное число
 * @param [in] max_mant_size - Максимальный размер мантиссы в числе
 * @param [in] max_order_size - Максимальный размер порядка в числе
 * @return int Код возврата
 */
int strtolf(const char *str, struct long_float *lf, size_t max_mant_size, size_t max_order_size);

/**
 * @brief Функция для проверки длинны порядка числа
 * 
 * @param [in] lf - Длинное число
 * @param [in] order_size - Макс размер порядка
 * @return int Код возврата
 */
int check_lf_order(const struct long_float *lf, size_t order_size);

/**
 * @brief Функция для вывода длинного числа
 * 
 * @param [in] lf - Длинное число
 */
void print_lf(const struct long_float *lf);

#endif
