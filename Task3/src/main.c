#include <stdio.h>
#include "matrix.h"
#include "vector.h"
#include "std_matrix.h"
#include "std_vector.h"
#include "multiplicaton.h"

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;
    FILE *f = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "r");
    struct std_matrix_t mat;
    struct std_vector_t vec;
    struct std_vector_t res;
    int rc = read_std_vector(f, &vec);
    int rc2 = read_std_matrix(f2, &mat);
    printf("%d %d\n", rc, rc2);
    rc = mult_std(&mat, &vec, &res);
    printf("%d\n", rc);
    // print_matrix(stdout, &mat);
    print_std_vector(stdout, &res);
    free_std_matrix(&mat);
    free_std_vector(&vec);
    free_std_vector(&res);
    fclose(f);
    fclose(f2);


    // if (argc != 2)
    //     return 1;
    // FILE *f = fopen(argv[1], "r");
    // // FILE *f2 = fopen(argv[2], "r");
    // struct std_vector_t vec;
    // int rc = read_std_vector(f, &vec);
    // printf("%d\n", rc);
    // print_std_vector(stdout, &vec);
    // free_std_vector(&vec);
    // fclose(f);
    // // fclose(f2);
    return 0;
}