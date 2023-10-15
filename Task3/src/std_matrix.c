#include <stdlib.h>
#include "std_matrix.h"
#include "errs.h"

int create_std_matrix(struct std_matrix_t *mat)
{
    mat->matrix = NULL;
    if (mat->rows == 0 || mat->cols == 0)
        return OK;

    mat->matrix = calloc(mat->rows, sizeof(int *));
    if (mat->matrix != NULL)
    {
        mat->matrix[0] = calloc(mat->cols * mat->rows, sizeof(int));
        if (mat->matrix[0] == NULL)
        {
            free_std_matrix(mat);
            return ERR_MEMORY;
        }
        for (size_t i = 1; i < mat->rows; i++)
        {
            mat->matrix[i] = mat->matrix[i - 1] + mat->cols;
        }
    }
    else
        return ERR_MEMORY;
    return OK;
}

void free_std_matrix(struct std_matrix_t *mat)
{
    if (mat->matrix == NULL)
        return;
    int *mmin = mat->matrix[0];
    for (size_t i = 1; i < mat->rows; i++)
        if (mat->matrix[i] < mmin)
            mmin = mat->matrix[i];
    free(mmin);
    free(mat->matrix);
    mat->matrix = NULL;
}

int read_std_matrix(FILE *f, struct std_matrix_t *mat, int verbose)
{
    (void) verbose;    
    int rc;
    if (f == NULL)
        return ERR_FILE;
    
    size_t elems;
    if (verbose)
        printf("Через пробел введите количество строк и столбцов матрицы, а также количество ненулевых элементов:\n");

    if (fscanf(f, "%zu%zu%zu", &(mat->rows), &(mat->cols), &elems) != 3)
        return ERR_FORMAT;

    if (mat->rows == 0 || mat->cols == 0)
        return ERR_NULL_SIZE;

    if ((rc = create_std_matrix(mat)))
        return rc;
    
    if (verbose && elems != 0)
    {
        printf("Введите %zu ненулевых элементов в формате: строка столбец элемент.\n", elems);
        printf("При вводе не должно быть повторений позиций элементов.\n");
    }

    for (size_t i = 0; i < elems; i++)
    {
        size_t row, col;
        int elem;

        if (verbose)
            printf("Введите %zu-й элемент: ", i + 1);

        if (fscanf(f, "%zu%zu%d", &row, &col, &elem) != 3)
        {
            free_std_matrix(mat);
            return ERR_FORMAT;
        }
        if (row > mat->rows || row == 0 || col > mat->cols || col == 0 || elem == 0 || mat->matrix[col - 1][row - 1])
        {
            free_std_matrix(mat);
            return ERR_FORMAT;
        }
        mat->matrix[row - 1][col - 1] = elem;   
    }
    if (verbose)
        printf("Ввод матрицы успешно окончен.\n");
    return OK;
}

int print_std_matrix(FILE *f, struct std_matrix_t *mat)
{
    if (f == NULL)
        return ERR_FILE;
    
    if (mat->rows == 0 || mat->cols == 0)
        return ERR_NULL_SIZE;
    
    if (mat->matrix == NULL)
        return ERR_NINIT_OBJ;

    for (size_t i = 0; i < mat->rows; i++)
    {
        for (size_t j = 0; j < mat->cols; j++)
            if (fprintf(f, "%d ", mat->matrix[i][j]) < 0)
                return ERR_IO;
        if (fprintf(f, "\n") < 0)
            return ERR_IO;
    }

    return OK;
}

int write_std_matrix(FILE *f, struct std_matrix_t *mat)
{
    if (f == NULL)
        return ERR_FILE;
    
    if (mat->rows == 0 || mat->cols == 0)
        return ERR_NULL_SIZE;
    
    if (mat->matrix == NULL)
        return ERR_NINIT_OBJ;
    
    int nnull = 0;
    for (size_t i = 0; i < mat->rows; i++)
        for (size_t j = 0; j < mat->cols; j++)
            if (mat->matrix[i][j])
                nnull++;
    
    if (fprintf(f, "%zu %zu %d\n", mat->rows, mat->cols, nnull) < 0)
        return ERR_IO;
    
    if (nnull == 0)
        return OK;
    
    for (size_t i = 0; i < mat->rows; i++)
        for (size_t j = 0; j < mat->cols; j++)
            if (mat->matrix[i][j])
                if (fprintf(f, "%zu %zu %d\n", i + 1, j + 1, mat->matrix[i][j]) < 0)
                    return ERR_IO;
    return OK;
}

// int mat_to_std(matrix_t *mat, std_matrix_t *std_mat)
// {
//     free_std_matrix(std_mat);
//     std_mat->rows = mat->rows;
//     std_mat->cols = mat->cols;
//     if (create_std_matrix(std_mat))
//         return ERR_MEMORY;
//     for (size_t i = 0; i < mat->rows; i++)
//     {
//         for (size_t j = mat->ia[i]; j < mat->ia[i + 1]; j++)
//         {

//         }
//     }
// }