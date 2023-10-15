#include <string.h>
#include "multiplicaton.h"
#include "matrix.h"
#include "std_matrix.h"
#include "vector.h"
#include "std_vector.h"
#include "errs.h"

int mult(struct matrix_t *mat, struct vector_t *vec, struct vector_t *res)
{
    if (mat->arr == NULL || vec->arr == NULL)
        return ERR_NINIT_OBJ;
    
    if (mat->rows == 0 || mat->cols == 0 || vec->size == 0)
        return ERR_NULL_SIZE;
    
    if (mat->cols != vec->size)
        return ERR_INCOMP_SIZES;
    
    res->size = mat->rows;
    res->elems = mat->rows;
    if (create_vector(res))
        return ERR_MEMORY;
    
    char tmp[vec->size];
    memset(tmp, 0, vec->size);
    for (size_t i = 0; i < vec->elems; i++)
        tmp[vec->iarr[i]] = 1;
    
    size_t now_size = 0;
    for (size_t i = 0; i < mat->rows; i++)
    {
        int sum = 0;
        for (size_t j = mat->ia[i]; j < mat->ia[i + 1]; j++)
        {
            if (tmp[mat->jarr[j]])
                sum += mat->arr[j] * vec->arr[mat->jarr[j]];
        }
        if (sum != 0)
        {
            res->arr[now_size] = sum;
            res->iarr[now_size] = i;
            now_size++;
        }
    }
    res->elems = now_size;
    realloc_vector(res);
    return OK;
}