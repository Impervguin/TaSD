#ifndef VECTOR_H__
#define VECTOR_H__
#include <stddef.h>
#include <stdio.h>
#include "std_vector.h"

typedef struct vector_t vector_t;

struct vector_t
{
    size_t size;
    size_t elems;
    int *arr;
    size_t *iarr;
};

int create_vector(struct vector_t *vec);
int realloc_vector(struct vector_t *vec);
void free_vector(struct vector_t *vec);
int read_vector(FILE *f, struct vector_t *vec, int verbose);
int print_vector(FILE *f, struct vector_t *vec);
int write_vector(FILE *f, struct vector_t *vec);
size_t count_vector_size(struct vector_t *vec);
int std_to_vec(std_vector_t *std_vec, vector_t *vec);

#endif
