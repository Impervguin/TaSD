#include "calculus.h"
#include "errs.h"
#include <string.h>

static void shift_array_left(int *arr, size_t arr_s, size_t shift)
{
    for (size_t i = 0; i < arr_s - shift; i++)
        arr[i] = arr[i + shift];
    for (size_t i = arr_s - shift; i < arr_s; i++)
        arr[i] = 0;
}

#define TMP_ARR_SIZE (MAX_MANTISS_SIZE * 2)
int multiplication(const struct long_float *flf, const struct long_float *slf, struct long_float *rlf, size_t max_mant_size)
{
    /// Временный массив цифр удвоенного размера
    int tmp_arr[TMP_ARR_SIZE];
    /// Зануляем результат
    make_lf_null(rlf);
    /// Зануляем временный массив
    memset(tmp_arr, 0, sizeof(tmp_arr));

    int norm_size = flf->size + slf->size; /// Ожидаемое положение запятой
    /// Умножение столбиком
    for (size_t i = 0; i < flf->size; i++)
    {
        for (size_t j = 0; j < slf->size; j++)
        {
            tmp_arr[i + j] += flf->mantiss[i] * slf->mantiss[j];
            for (size_t k = i + j; k < TMP_ARR_SIZE - 1 && tmp_arr[k] >= CELL_BASE; k++)
            {
                tmp_arr[k + 1] += tmp_arr[k] / 10;
                tmp_arr[k] %= 10; 
            }
        }
    }
    
    size_t arr_s = 0; /// Реальное положение запятой и размер временного массива
    for (size_t i = 0; i < TMP_ARR_SIZE; i++)
        if (tmp_arr[i] != 0)
            arr_s = i + 1;

    int order_add = (int)(arr_s) - norm_size; /// Изменение порядка при нормализации
    /// Округление
    if (arr_s > max_mant_size)
    {
        size_t diff = arr_s - max_mant_size;
        // rlf->order += diff;

        // Округление
        for (size_t i = 0; i < diff; i++)
            if (tmp_arr[i] >= 5)
                tmp_arr[i + 1]++;
        for (size_t i = diff; i < arr_s && tmp_arr[i] > 9; i++)
        {
            tmp_arr[i] = 0;
            tmp_arr[i + 1]++;
        }
        /// Сдвиг дальше если на нынешней позициир ноль
        for (size_t i = diff; i < arr_s && tmp_arr[i] == 0; i++)
            diff++;
        shift_array_left(tmp_arr, arr_s, diff);
        arr_s -= diff;
    }

    /// Запись результата
    rlf->mant_sign = ((flf->mant_sign && !slf->mant_sign) || (!flf->mant_sign && slf->mant_sign)) ? 0 : 1;
    if (flf->size == 0 || slf->size == 0)
        rlf->order = 0;
    else 
        rlf->order += slf->order + flf->order + order_add;
    rlf->size = arr_s;
    for (size_t i = 0; i < arr_s; i++)
        rlf->mantiss[i] = tmp_arr[i];

    return ERR_OK;
}
