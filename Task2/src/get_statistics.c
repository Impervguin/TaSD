#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include "country.h"
#include "country_arr.h"
#include "errs.h"

long int get_time(struct timeval *time_s, struct timeval *time_e)
{
    return (time_e -> tv_sec * 1000000 + time_e -> tv_usec) - (time_s -> tv_sec * 1000000 + time_s -> tv_usec);
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Недостаточное количество аргументов.\n");
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    struct country_ind_arr_t arr;
    struct country_ind_arr_t tmp_arr;
    struct country_arr_t w_arr;

    if (f == NULL)
    {
        printf("Неккоректное имя файла.\n");
        return 1; 
    }

    if (read_country_ind_arr(f, &arr))
    {
        printf("Неккоректное содержимое файла.\n");
        return 1; 
    }

    int n = atoi(argv[2]);

    long mys_ind, mys, qs, qs_ind, tsum;
    size_t ind_s = sizeof(arr), arr_s = sizeof(w_arr);
    struct timeval time_s, time_e;
    tsum = 0;
    for (int i = 0; i < n; i++)
    {
        indtoarr(&arr, &w_arr);
        gettimeofday(&time_s, NULL);
        sort_country_arr(&w_arr);
        gettimeofday(&time_e, NULL);
        tsum += get_time(&time_s, &time_e);
    }
    mys = tsum / n;
    
    tsum = 0;
    for (int i = 0; i < n; i++)
    {
        indtoarr(&arr, &w_arr);
        gettimeofday(&time_s, NULL);
        qsort_country_arr(&w_arr, 0, w_arr.size - 1);
        gettimeofday(&time_e, NULL);
        tsum += get_time(&time_s, &time_e);
    }
    qs = tsum / n;

    tsum = 0;
    for (int i = 0; i < n; i++)
    {
        tmp_arr = arr;
        gettimeofday(&time_s, NULL);
        sort_country_ind_arr(&tmp_arr);
        gettimeofday(&time_e, NULL);
        tsum += get_time(&time_s, &time_e);
    }
    mys_ind = tsum / n;

    tsum = 0;
    for (int i = 0; i < n; i++)
    {
        tmp_arr = arr;
        gettimeofday(&time_s, NULL);
        qsort_country_ind_arr(&tmp_arr, 0, arr.size - 1);
        gettimeofday(&time_e, NULL);
        tsum += get_time(&time_s, &time_e);
    }
    qs_ind = tsum / n;
    printf("sort_country_arr: %ld\n", mys);
    printf("qsort_country_arr: %ld\n", qs);
    printf("sort_country_ind_arr: %ld\n", mys_ind);
    printf("qsort_country_ind_arr: %ld\n", qs_ind);
    printf("\n");
    printf("country_arr_t: %zu\n", arr_s);
    printf("country_ind_arr_t: %zu\n", ind_s);
}