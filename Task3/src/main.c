#include <stdio.h>
#include "matrix.h"
#include "vector.h"
#include "multiplicaton.h"

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;
    FILE *f = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "r");
    struct matrix_t mat;
    struct vector_t vec;
    struct vector_t res;
    int rc = read_vector(f, &vec);
    int rc2 = read_matrix(f2, &mat);
    printf("%d %d\n", rc, rc2);
    rc = mult(&mat, &vec, &res);
    printf("%d\n", rc);
    // print_matrix(stdout, &mat);
    print_vector(stdout, &res);
    free_matrix(&mat);
    free_vector(&vec);
    free_vector(&res);
    fclose(f);
    fclose(f2);
    return 0;
}