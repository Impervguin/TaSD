#include <stdlib.h>
#include "vector.h"
#include "errs.h"

int create_vector(struct vector_t *vec)
{
    vec->arr = NULL;
    vec->iarr = NULL;
    if ((vec->arr = calloc(vec->elems, sizeof(int))) == NULL)
        return ERR_MEMORY;
    
    if ((vec->iarr = calloc(vec->elems, sizeof(size_t))) == NULL)
    {
        free_vector(vec);
        return ERR_MEMORY;
    }
    return OK;
}

void free_vector(struct vector_t *vec)
{
    free(vec->arr);
    free(vec->iarr);
}

int realloc_vector(struct vector_t *vec)
{
    if (vec->elems == 0)
    {
        vec->arr = NULL;
        vec->iarr = NULL;
        return OK;
    }
    int *tmp = realloc(vec->arr, sizeof(int) * vec->elems);
    if (tmp == NULL)
        return ERR_MEMORY;
    vec->arr = tmp;
    size_t *tmp2 = realloc(vec->iarr, sizeof(size_t) * vec->elems);
    if (tmp2 == NULL)
        return ERR_MEMORY;
    vec->iarr = tmp2;
    return OK;

}

int read_vector(FILE *f, struct vector_t *vec)
{
    int rc;
    if (f == NULL)
        return ERR_FILE;
    
    if (fscanf(f, "%zu%zu", &(vec->size), &(vec->elems)) != 2)
        return ERR_FORMAT;
    
    if ((rc = create_vector(vec)))
        return rc;
    size_t last_num = 0;
    for (size_t i = 0; i < vec->elems; i++)
    {
        size_t num;
        int elem;
        if (fscanf(f, "%zu%d", &num, &elem) != 2)
        {
            free_vector(vec);
            return ERR_FORMAT;
        }

        if (num == 0 || num > vec->size || last_num >= num)
        {
            free_vector(vec);
            return ERR_FORMAT;
        }
        vec->arr[i] = elem;
        vec->iarr[i] = num - 1;
    }
    return OK;
}

int print_vector(FILE *f, struct vector_t *vec)
{
    if (f == NULL)
        return ERR_FILE;
    
    // if (vec->arr == NULL)
    //     return ERR_NINIT_OBJ;
    
    if (vec->elems != 0)
    {
        for (size_t j = 0; j < vec->iarr[0]; j++)
            if (fprintf(f, "0\n") < 0)
                return ERR_IO;
        if (fprintf(f, "%d\n", vec->arr[0]) < 0)
            return ERR_IO;
    }

    for (size_t i = 1; i < vec->elems; i++)
    {
        for (size_t j = vec->iarr[i - 1]; j < vec->iarr[i] - 1; j++)
            if (fprintf(f, "0\n") < 0)
                return ERR_IO;
        if (fprintf(f, "%d\n", vec->arr[i]) < 0)
            return ERR_IO;
    }

    if (vec->elems != 0)
    {
        for (size_t j = vec->iarr[vec->elems - 1]; j < vec->size - 1; j++)
            if (fprintf(f, "0\n") < 0)
                return ERR_IO;
    }
    else
        for (size_t j = 0; j < vec->size; j++)
            if (fprintf(f, "0\n") < 0)
                return ERR_IO;

    return OK;
}

int write_vector(FILE *f, struct vector_t *vec)
{
    // if (vec->arr == NULL)
    //     return ERR_NINIT_OBJ;
    
    if (f == NULL)
        return ERR_FILE;

    if (fprintf(f, "%zu %zu\n", vec->size, vec->elems) < 0)
        return ERR_IO;

    for (size_t i = 0; i < vec->elems; i++)
        if (fprintf(f, "%zu %d\n", vec->iarr[i] + 1, vec->arr[i]) < 0)
            return ERR_IO;
    return OK;
}

