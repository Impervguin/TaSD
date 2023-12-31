#include <stdio.h>
#include <string.h>
#include "io.h"
#include "errs.h"
#include "matrix.h"
#include "vector.h"
#include "std_matrix.h"
#include "std_vector.h"
#include "multiplicaton.h"
#include <time.h>
#include <sys/time.h>

long int get_time(struct timeval *time_s, struct timeval *time_e)
{
    return (time_e -> tv_sec * 1000000 + time_e -> tv_usec) - (time_s -> tv_sec * 1000000 + time_s -> tv_usec);
}

#define FILE_INPUT 1
#define USER_INPUT 0

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

int main(void)
{
    long int mult_time, std_time;
    std_matrix_t std_mat;
    std_vector_t std_vec;
    std_vector_t std_res;
    vector_t vec;
    vector_t res;
    matrix_t mat;
    init_dyn_vars(&std_mat, &std_vec, &mat, &vec, &res, &std_res);
    FILE *fmat = NULL, *fvec = NULL;
    int command;
    int rc;
    int running = 1;

    print_intro();
    while (running)
    {
        if (fmat)
        {
            fclose(fmat);
            fmat = NULL;
        }
            
        if (fvec)
        {
            fclose(fvec);
            fvec = NULL;
        }
            
        free_dyn_vars(&std_mat, &std_vec, &mat, &vec, &res, &std_res);
        rc = OK;
        print_menu();
        
        rc = int_input(&command, "Введите номер: ");
        if (!rc)
            if (command > MAX_COMMAND_NUM || command < 0)
                rc = ERR_COMMAND;
        if (!rc && command == EXIT)
        {
            running = 0;
            continue;
        }
        
        if (!rc)
        {
            int fdes = 2;
            printf("Ввод матрицы.\n");
            rc = int_input(&fdes, "Введите вид ввода(1 - Файловый, 0 - Консольный.): ");
            if (!rc)
                if (fdes != USER_INPUT && fdes != FILE_INPUT)
                    rc = ERR_COMMAND;
            
            if (!rc && fdes == USER_INPUT)
            {
                if (command == MULT)
                {
                    rc = read_matrix(stdin, &mat, 1);
                }
                else if (command == STD_MULT)
                {
                    rc = read_std_matrix(stdin, &std_mat, 1);
                }
                else if (command == COMPAR)
                {
                    rc = read_std_matrix(stdin, &std_mat, 1);
                    if (!rc)
                        rc = std_to_mat(&std_mat, &mat);
                }
                
                while(!rc && getchar() != '\n');
            }
            else if (!rc && fdes == FILE_INPUT)
            {
                rc = read_file(&fmat);
                if (!rc)
                {
                    if (command == MULT)
                    {
                        rc = read_matrix(fmat, &mat, 0);
                    }
                    else if (command == STD_MULT)
                    {
                        rc = read_std_matrix(fmat, &std_mat, 0);
                    }
                    else if (command == COMPAR)
                    {
                        rc = read_std_matrix(fmat, &std_mat, 0);
                        if (!rc)
                        {
                            rewind(fmat);
                            rc = read_matrix(fmat, &mat, 0);
                        }     
                    }
                }
            }

        }

        if (!rc)
        {
            int fdes = 2;
            printf("Ввод вектора.\n");
            rc = int_input(&fdes, "Введите вид ввода(1 - Файловый, 0 - Консольный.): ");
            if (!rc)
                if (fdes != USER_INPUT && fdes != FILE_INPUT)
                    rc = ERR_COMMAND;
            
            if (!rc && fdes == USER_INPUT)
            {
                if (command == MULT)
                {
                    rc = read_vector(stdin, &vec, 1);
                }
                else if (command == STD_MULT)
                {
                    rc = read_std_vector(stdin, &std_vec, 1);
                }
                else if (command == COMPAR)
                {
                    rc = read_std_vector(stdin, &std_vec, 1);
                    if (!rc)
                        rc = std_to_vec(&std_vec, &vec);
                }
                while(!rc && getchar() != '\n');
            }
            else if (!rc && fdes == FILE_INPUT)
            {
                rc = read_file(&fvec);
                if (!rc)
                {
                    if (command == MULT)
                    {
                        rc = read_vector(fvec, &vec, 0);
                    }
                    else if (command == STD_MULT)
                    {
                        rc = read_std_vector(fvec, &std_vec, 0);
                    }
                    else if (command == COMPAR)
                    {
                        rc = read_std_vector(fvec, &std_vec, 0);
                        if (!rc)
                        {
                            rewind(fvec);
                            rc = read_vector(fvec, &vec, 0);
                        }     
                    }
                }
            }
        }

        if (!rc)
        {
            if (command == MULT)
            {
                rc = mult(&mat, &vec, &res);
            }
            else if (command == STD_MULT)
            {
                rc = mult_std(&std_mat, &std_vec, &std_res);
            }
            else if (command == COMPAR)
            {
                struct timeval time_s, time_e;
                gettimeofday(&time_s, NULL);
                rc = mult(&mat, &vec, &res);
                gettimeofday(&time_e, NULL);
                mult_time = get_time(&time_s, &time_e);

                if (!rc)
                {
                    gettimeofday(&time_s, NULL);
                    rc = mult_std(&std_mat, &std_vec, &std_res);
                    gettimeofday(&time_e, NULL);
                    std_time = get_time(&time_s, &time_e);
                }
            }
        }

        if (!rc)
        {
            printf("Результаты:\n");
            if (command == MULT)
            {
                rc = print_vector(stdout, &res);
            }
            else if (command == STD_MULT)
            {
                rc = write_std_vector(stdout, &std_res);
            }
            else if (command == COMPAR)
            {
                printf("Время стандартного умножения: %ld мкс.\n", std_time);
                printf("Время умножения в CRS:  %ld мкс.\n", mult_time);
                printf("\n");
                printf("Размер обычного вектора: %zu байт.\n", count_std_vector_size(&std_vec));
                printf("Размер CRS вектора: %zu байт.\n", count_vector_size(&vec));
                printf("\n");
                printf("Размер обычной матрицы: %zu байт.\n", count_std_matrix_size(&std_mat));
                printf("Размер CRS матрицы: %zu байт.\n", count_matrix_size(&mat));

            }
            if (!rc)
                running = 0;
        }

        if (rc)
            print_error(rc);
    }

    free_dyn_vars(&std_mat, &std_vec, &mat, &vec, &res, &std_res);
    if (fmat)
        fclose(fmat);
    
    if (fvec)
        fclose(fvec);
    
    return OK;
}