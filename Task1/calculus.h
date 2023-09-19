#ifndef CALCULUS_H__
#define CALCULUS_H__

#include "long_float.h"
/**
 * @brief Функция для перемножения двух длинных действительных чисел
 * 
 * @param [in] flf - Первое число
 * @param [in] slf - Второе число
 * @param [out] rlf - Результирующее число
 * @param [in] max_mant_size - Максимальный размер мантиссы результата
 * @return int Код возврата
 */
int multiplication(const struct long_float *flf, const struct long_float *slf, struct long_float *rlf, size_t max_mant_size);

#endif
