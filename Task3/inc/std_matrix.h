#ifndef STD_MATRIX_H__
#define STD_MATRIX_H__
#include <stddef.h>
#include <stdio.h>

typedef struct std_matrix_t std_matrix_t;

struct std_matrix_t
{
    size_t rows;
    size_t cols;
    int **matrix;
};

int create_std_matrix(struct std_matrix_t *mat);
void free_std_matrix(struct std_matrix_t *mat);
int read_std_matrix(FILE *f, struct std_matrix_t *mat, int verbose);
int print_std_matrix(FILE *f, struct std_matrix_t *mat);
int write_std_matrix(FILE *f, struct std_matrix_t *mat);
size_t count_std_matrix_size(struct std_matrix_t *mat);
// int mat_to_std(matrix_t *mat, std_matrix_t *std_mat);

#endif
