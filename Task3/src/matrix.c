#include <stdlib.h>
#include "matrix.h"
#include "errs.h"

int create_matrix(struct matrix_t *mat)
{
    mat->ia = NULL;
    mat->arr = NULL;
    mat->jarr = NULL;
    if (mat->elems != 0)
    {
        if ((mat->arr = calloc(mat->elems, sizeof(int))) == NULL)
            return ERR_MEMORY;
    
        if ((mat->jarr = calloc(mat->elems, sizeof(size_t))) == NULL)
        {
            free_matrix(mat);
            return ERR_MEMORY;
        }

        if ((mat->ia = calloc((mat->rows) + 1, sizeof(size_t))) == NULL)
        {
            free_matrix(mat);
            return ERR_MEMORY;
        }
    }
    return OK;
}

void free_matrix(struct matrix_t *mat)
{
    free(mat->arr);
    mat->arr = NULL;
    free(mat->ia);
    mat->ia = NULL;
    free(mat->jarr);
    mat->jarr = NULL;
}

int read_matrix(FILE *f, struct matrix_t *mat, int verbose)
{
    (void) verbose;
    int rc;
    if (f == NULL)
        return ERR_FILE;
    
    if (verbose)
        printf("Через пробел введите количество строк и столбцов матрицы, а также количество ненулевых элементов:\n");

    if (fscanf(f, "%zu%zu%zu", &(mat->rows), &(mat->cols), &(mat->elems)) != 3)
        return ERR_FORMAT;
    
    if (mat->rows == 0 || mat->cols == 0)
        return ERR_NULL_SIZE;
    
    if ((rc = create_matrix(mat)))
        return rc;

    size_t now_row = 0;

    if (verbose && mat->elems != 0)
    {
        printf("Введите %zu ненулевых элементов в формате: строка столбец элемент.\n", mat->elems);
        printf("При вводе строки и столбцы должны идти в порядке возрастания, а также не должно быть повторений.\n");
    }
    size_t last_col = 0;
    for (size_t i = 0; i < mat->elems; i++)
    {
        size_t row, col;
        int elem;
        if (verbose)
            printf("Введите %zu-й элемент: ", i + 1);
        if (fscanf(f, "%zu%zu%d", &row, &col, &elem) != 3)
        {
            free_matrix(mat);
            return ERR_FORMAT;
        }
        if (row > mat->rows || row == 0 || col > mat->cols || col == 0 || row - 1 < now_row || (last_col >= col && row - 1 == now_row) || elem == 0)
        {
            free_matrix(mat);
            return ERR_FORMAT;
        }
        while (now_row < row - 1)
        {
            now_row++;
            mat->ia[now_row] = i;
            last_col = 0;
        }
        mat->arr[i] = elem;
        mat->jarr[i] = col - 1;
        last_col = col;
    }

    if (verbose)
        printf("Ввод матрицы успешно окончен.\n");

    if (mat->elems != 0)
        while (now_row < mat->rows)
            mat->ia[++now_row] = mat->elems;
    return OK;
}

int write_matrix(FILE *f, struct  matrix_t *mat)
{
    // if (mat->arr == NULL)
    //     return ERR_NINIT_OBJ;
    
    if (f == NULL)
        return ERR_FILE;

    if (fprintf(f, "%zu %zu %zu\n", mat->rows, mat->cols, mat->elems) < 0)
        return ERR_IO;

    size_t i = 0;
    for (size_t j = 0; j < mat->elems; j++)
    {
        while (j == mat->ia[i])
            i++;
        
        if (fprintf(f, "%zu %zu %d\n", i, mat->jarr[j] + 1, mat->arr[j]) < 0)
            return ERR_IO;
    }
    return OK;
}

int print_matrix(FILE *f, struct  matrix_t *mat)
{
    // if (mat->arr == NULL)
    //     return ERR_NINIT_OBJ;
    
    if (f == NULL)
        return ERR_FILE;
    
    for (size_t i = 0; i < mat->rows; i++)
    {
        for (size_t j = mat->ia[i]; j < mat->ia[i + 1]; j++)
        {
            if (mat->ia[i] == j)
            {
                for (size_t k = 0; k < mat->jarr[j]; k++)
                    if (fprintf(f, "%d ", 0) < 0)
                        return ERR_IO;
            }
            else 
            {
                for (size_t k = 1; k < mat->jarr[j] - mat->jarr[j - 1]; k++)
                    if (fprintf(f, "%d ", 0) < 0)
                        return ERR_IO;
            }
            if (fprintf(f, "%d ", mat->arr[j]) < 0)
                return ERR_IO;
        }
        if (mat->ia[i] == mat->ia[i + 1])
        {
            for (size_t k = 0; k < mat->cols; k++)
                if (fprintf(f, "%d ", 0) < 0)
                    return ERR_IO;
        }
        else 
            for (size_t k = 1; k < mat->cols - mat->jarr[mat->ia[i + 1] - 1]; k++)
                if (fprintf(f, "%d ", 0) < 0)
                    return ERR_IO; 
        if (fprintf(f, "\n") < 0)
                return ERR_IO;
    }
    return OK;
}

int std_to_mat(std_matrix_t *std_mat, matrix_t *mat)
{
    free_matrix(mat);
    size_t elems = 0;
    for (size_t i = 0; i < std_mat->rows; i++)
        for (size_t j = 0; j < std_mat->cols; j++)
            if (std_mat->matrix[i][j])
                elems++;
    
    mat->rows = std_mat->rows;
    mat->cols = std_mat->cols;
    mat->elems = elems;
    if (create_matrix(mat))
        return ERR_MEMORY;
    
   size_t now_el = 0;
    for (size_t i = 0; i < std_mat->rows; i++)
    {
        mat->ia[i] = now_el;
        for (size_t j = 0; j < std_mat->cols; j++)
        {
            if (std_mat->matrix[i][j])
            {
                mat->arr[now_el] = std_mat->matrix[i][j];
                mat->jarr[now_el] = j;
                now_el++;
            }
        }
    }
    if (elems)
        mat->ia[mat->rows - 1] = now_el;
    return OK;
}

size_t count_matrix_size(struct matrix_t *mat)
{
    size_t size = 0;
    size += sizeof(int) * mat->elems;
    size += sizeof(size_t) * mat->elems;
    size += sizeof(size_t) * (mat->rows  + 1);
    size += sizeof(*mat);
    return size;
}