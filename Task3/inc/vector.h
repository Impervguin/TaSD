#ifndef VECTOR_H__
#define VECTOR_H__
#include <stddef.h>
#include <stdio.h>

struct vector_t
{
    size_t size;
    int *arr;
    size_t *iarr;
};

int create_vector(vector_t *vec);
void free_vector(vector_t *vec);
int read_vector(FILE *f, vector_t *vec);
int print_vector(FILE *f, vector_t *vec);
int write_vector(FILE *f vector_t *vec);
size_t count_vector_size(vector_t *vec);

#endif
