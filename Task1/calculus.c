#include "calculus.h"
#include "errs.h"


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
    int tmp_arr[TMP_ARR_SIZE];

    make_lf_null(rlf);

    for (size_t i = 0; i < TMP_ARR_SIZE; i++)
        tmp_arr[i] = 0;

    for (size_t i = 0; i < flf->size; i++)
    {
        for (size_t j = 0; j < slf->size; j++)
        {
            tmp_arr[i + j] += flf->mantiss[i] * slf->mantiss[j];
            for (size_t k = i + j; k < TMP_ARR_SIZE - 1 && tmp_arr[k] > CELL_BASE; k++)
            {
                tmp_arr[k + 1] = tmp_arr[k] / 10;
                tmp_arr[k] %= 10; 
            }
        }
    }
    
    size_t arr_s = 0;
    for (size_t i = 0; i < TMP_ARR_SIZE; i++)
        if (tmp_arr[i] != 0)
            arr_s = i + 1;
    
    if (arr_s > max_mant_size)
    {
        size_t diff = arr_s - max_mant_size;
        rlf->order += diff;
        for (size_t i = max_mant_size; i < arr_s && tmp_arr[i] == 0; i++)
            diff++;
        shift_array_left(tmp_arr, arr_s, diff);
        arr_s -= diff;
    }

    rlf->mant_sign = ((flf->mant_sign && !slf->mant_sign) || (!flf->mant_sign && slf->mant_sign)) ? 0 : 1;
    rlf->order += slf->order + flf->order;
    rlf->size = arr_s;
}
