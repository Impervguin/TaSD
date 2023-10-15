#ifndef MATRIX_H__
#define MATRIX_H__
#include <stddef.h>
#include <stdio.h>

struct matrix_t
{
    size_t rows;
    size_t cols;
    size_t elems;
    int *arr;
    size_t *jarr;
    size_t *ia;
};

int create_matrix(struct matrix_t *mat);
void free_matrix(struct matrix_t *mat);
int read_matrix(FILE *f, struct matrix_t *mat);
int print_matrix(FILE *f, struct  matrix_t *mat);
int write_matrix(FILE *f, struct  matrix_t *mat);
size_t count_matrix_size(struct matrix_t *mat);

#endif
