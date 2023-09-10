#include "calculus.h"
#include "errs.h"

#define TMP_ARR_SIZE (ARR_MANTISS_SIZE * 2)
int multiplication(const struct long_float *flf, const struct long_float *slf, struct long_float *rlf, size_t max_mant_size)
{
    for (size_t j = 0; j < ARR_MANTISS_SIZE; j++)
        rlf->mantiss[j] = 0;
    rlf->order = 0;

    size_t flf_size = 0, slf_size = 0;
    
    for (size_t j = 0; j < ARR_MANTISS_SIZE; j++)
    {
        if (flf->mantiss[j] != 0)
            flf_size = j + 1;
        if (slf->mantiss[j] != 0)
            slf_size = j + 1;
    }

    if (flf_size && slf_size)
    {
        int arr[TMP_ARR_SIZE];
        for (size_t j = 0; j < TMP_ARR_SIZE; j++)
            arr[j] = 0;
        for (size_t i = 0; i < flf_size; i++)
        {
            for (size_t j = 0; j < slf_size; j++)
            {
                arr[i + j] += flf->mantiss[i] * slf->mantiss[j];
                
                for (size_t k = i + j; k < TMP_ARR_SIZE && arr[k] / CELL_DEC != 0; k++)
                {
                    arr[k + 1] += arr[k] / CELL_DEC;
                    arr[k] %= CELL_DEC;
                }
            }
        }
        size_t arr_size; 
        for (size_t j = 0; j < TMP_ARR_SIZE; j++)
        {
            if (arr[j] != 0)
                arr_size = j + 1;
        }
        if (arr_size > max_mant_size)
        {
            size_t diff = arr_size - max_mant_size;
            for (size_t i = 0; i < arr_size - diff; i++)
                arr[i] = arr[i + diff];
            for (size_t i = arr_size - diff; i < arr_size; i++)
                arr[i] = 0;
            arr_size = max_mant_size;
            rlf->order += diff;
        }   

        rlf->order += slf->order + flf->order - 1;
        rlf->mant_sign = ((flf->mant_sign && !slf->mant_sign) || (!flf->mant_sign && slf->mant_sign))? 0 : 1;
        for (size_t i = 0; i < arr_size; i++)
        {
            rlf->mantiss[i] = arr[i];
        }
    }
    return ERR_OK;
}
