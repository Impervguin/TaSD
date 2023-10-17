#include <stdio.h>
#include <string.h>
#include "errs.h"
#include "matrix.h"
#include "vector.h"
#include "std_matrix.h"
#include "std_vector.h"
#include "multiplicaton.h"
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

// long int get_time(struct timeval *time_s, struct timeval *time_e)
// {
//     return (time_e -> tv_sec * 1000000 + time_e -> tv_usec) - (time_s -> tv_sec * 1000000 + time_s -> tv_usec);
// }

long long get_time(struct timespec *time_s, struct timespec *time_e)
{

    return (((long long)time_e -> tv_sec) * 1000000000 + time_e -> tv_nsec) - (((long long)time_s -> tv_sec) * 1000000000 + time_s -> tv_nsec);
}

#define TEST_COUNT 10000

void init_dyn_vars(std_matrix_t *std_mat, std_vector_t *std_vec, matrix_t *mat, vector_t *vec, vector_t *res, std_vector_t *std_res)
{
    memset(std_mat, 0, sizeof(*std_mat));
    memset(mat, 0, sizeof(*mat));
    memset(std_vec, 0, sizeof(*std_vec));
    memset(vec, 0, sizeof(*vec));
    memset(res, 0, sizeof(*res));
    memset(std_res, 0, sizeof(*std_res));
}

void free_dyn_vars(std_matrix_t *std_mat, std_vector_t *std_vec, matrix_t *mat, vector_t *vec, vector_t *res, std_vector_t *std_res)
{
    free_matrix(mat);
    free_std_matrix(std_mat);
    free_vector(vec);
    free_std_vector(std_vec);
    free_vector(res);
    free_std_vector(std_res);
}

int main(int argc, char **argv)
{
    long long mult_time = 0, std_time = 0;
    std_matrix_t std_mat;
    std_vector_t std_vec;
    std_vector_t std_res;
    vector_t vec;
    vector_t res;
    matrix_t mat;
    init_dyn_vars(&std_mat, &std_vec, &mat, &vec, &res, &std_res);
    int rc;
    FILE *fmat = NULL, *fvec = NULL;
    if (argc != 3)
        return 1;
    
    fmat = fopen(argv[1], "r");
    if (fmat == NULL)
        return ERR_WR_FNAME;
    
    fvec = fopen(argv[2], "r");
    if (fvec == NULL)
        rc = ERR_WR_FNAME;
    
    if (!rc)
        rc = read_matrix(fmat, &mat, 0);
    
    if (!rc)
    {
        rewind(fmat);
        rc = read_std_matrix(fmat, &std_mat, 0);
    }

    if (!rc)
        rc = read_vector(fvec, &vec, 0);
    
    if (!rc)
    {
        rewind(fvec);
        rc = read_std_vector(fvec, &std_vec, 0);
    }

    if (!rc)
    {
        struct timespec time_s, time_e;
        for (size_t i = 0; !rc &&i < TEST_COUNT; i++)
        {
            free_vector(&res);
            clock_gettime(CLOCK_REALTIME, &time_s);
            rc = mult(&mat, &vec, &res);
            clock_gettime(CLOCK_REALTIME, &time_e);
            mult_time += get_time(&time_s, &time_e);
        }
        mult_time /= TEST_COUNT;
        
        if (!rc)
        {
            for (size_t i = 0; !rc &&i < TEST_COUNT; i++)
            {
                free_std_vector(&std_res);
                clock_gettime(CLOCK_REALTIME, &time_s);
                rc = mult_std(&std_mat, &std_vec, &std_res);
                clock_gettime(CLOCK_REALTIME, &time_e);
                std_time += get_time(&time_s, &time_e);
            }
            std_time /= TEST_COUNT;
        }
    }

    if (!rc)
    {
        printf("Время стандартного умножения: %lld нс.\n", std_time);
        printf("Время умножения в CRS:  %lld нс.\n", mult_time);
        printf("Отношение %lf.\n", ((double) std_time) / mult_time);
        printf("\n");
        printf("Размер обычного вектора: %zu байт.\n", count_std_vector_size(&std_vec));
        printf("Размер CRS вектора: %zu байт.\n", count_vector_size(&vec));
        printf("\n");
        printf("Размер обычной матрицы: %zu байт.\n", count_std_matrix_size(&std_mat));
        printf("Размер CRS матрицы: %zu байт.\n", count_matrix_size(&mat));
    }

    return rc;
}