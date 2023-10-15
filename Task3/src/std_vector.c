#include <stdlib.h>
#include "std_vector.h"
#include "errs.h"

int create_std_vector(struct std_vector_t *vec)
{
    vec->arr = NULL;
    if (vec->size != 0)
    {
        vec->arr = calloc(vec->size, sizeof(int));
        if (vec->arr == NULL)
            return ERR_MEMORY;
    }
    return OK;
}

void free_std_vector(struct std_vector_t *vec)
{
    free(vec->arr);
    vec->arr = NULL;
}

int read_std_vector(FILE *f, struct std_vector_t *vec)
{
    int rc;
    if (f == NULL)
        return ERR_FILE;
    
    size_t elems;
    if (fscanf(f, "%zu%zu", &(vec->size), &elems) != 2)
        return ERR_FORMAT;

    if (vec->size == 0)
        return ERR_NULL_SIZE;

    if ((rc = create_std_vector(vec)))
        return rc;
    
    for (size_t i = 0; i < elems; i++)
    {
        size_t num;
        int elem;
        if (fscanf(f, "%zu%d", &num, &elem) != 2)
        {
            free_std_vector(vec);
            return ERR_FORMAT;
        }
        if (num > vec->size || num == 0)
        {
            free_std_vector(vec);
            return ERR_FORMAT;
        }
        vec->arr[num - 1] = elem;   
    }
    return OK;
}

int print_std_vector(FILE *f, struct std_vector_t *vec)
{
    if (f == NULL)
        return ERR_FILE;
    
    if (vec->size == 0)
        return ERR_NULL_SIZE;
    
    if (vec->arr == NULL)
        return ERR_NINIT_OBJ;

    for (size_t i = 0; i < vec->size; i++)
        if (fprintf(f, "%d\n", vec->arr[i]) < 0)
            return ERR_IO;
    
    return OK;
}

int write_std_vector(FILE *f, struct std_vector_t *vec)
{
        if (f == NULL)
        return ERR_FILE;
    
    if (vec->size == 0)
        return ERR_NULL_SIZE;
    
    if (vec->arr == NULL)
        return ERR_NINIT_OBJ;
    
    int nnull = 0;

    for (size_t i = 0; i < vec->size; i++)
        if (vec->arr[i])
            nnull++;
    
    if (fprintf(f, "%zu %d\n", vec->size, nnull) < 0)
        return ERR_IO;
    
    if (nnull == 0)
        return OK;
    
    for (size_t i = 0; i < vec->size; i++)
        if (vec->arr[i])
            if (fprintf(f, "%zu %d\n", i + 1, vec->arr[i]) < 0)
                return ERR_IO;
    
    return OK;
}