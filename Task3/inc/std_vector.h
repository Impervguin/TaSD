#ifndef STD_VECTOR_H__
#define STD_VECTOR_H__
#include <stddef.h>
#include <stdio.h>

typedef struct std_vector_t std_vector_t;

struct std_vector_t
{
    size_t size;
    int *arr;
};

int create_std_vector(struct std_vector_t *vec);
void free_std_vector(struct std_vector_t *vec);
int read_std_vector(FILE *f, struct std_vector_t *vec, int verbose);
int print_std_vector(FILE *f, struct std_vector_t *vec);
int write_std_vector(FILE *f, struct std_vector_t *vec);
size_t count_std_vector_size(struct std_vector_t *vec);

#endif
