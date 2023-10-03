#include "country.h"
#include "country_arr.h"
#include "errs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int read_country_arr(FILE *f, struct country_arr_t *arr)
{
    char tmpbuf[2];
    tmpbuf[0] = '\n';
    size_t now_s = 0;
    struct country_t tmp;
    int rc = ERR_OK;
    while (now_s < MAX_ARRAY_SIZE && !(rc = read_country_file(f, &tmp, 0)))
        arr->arr[now_s++] = tmp;
    
    if (!rc)
    {
        while (tmpbuf[0] == '\n' && fgets(tmpbuf, 2, f) != NULL);
        if (!feof(f))
            rc = ERR_CORR_FILE;
        
    }

    if (rc == ERR_IO && feof(f))
        rc = ERR_OK;

    if (!rc)
        arr->size = now_s;
    return rc;       
}

int read_country_ind_arr(FILE *f, struct country_ind_arr_t *arr)
{
    union
    {
        struct country_ind_arr_t arr_ind;
        struct country_arr_t arr;
    } tmp;

    int rc;
    rc = read_country_arr(f, &tmp.arr);
    if (!rc)
    {
        *arr = tmp.arr_ind;
        for (size_t i = 0; i < arr->size; i++)
            arr->indexes[i] = i;
    }
    return rc;
}

int add_country_arr(struct country_arr_t *arr, struct country_t *country)
{
    if (arr->size == MAX_ARRAY_SIZE)
        return ERR_ARR_RANGE;
    arr->arr[arr->size++] = *country;
    return ERR_OK;
}

int add_country_ind_arr(struct country_ind_arr_t *arr, struct country_t *country)
{
    if (arr->size == MAX_ARRAY_SIZE)
        return ERR_ARR_RANGE;
    arr->arr[arr->size] = *country;
    arr->indexes[arr->size] = arr->size;
    arr->size++;
    return ERR_OK;
}

int write_country_arr(FILE *f, struct country_arr_t *arr)
{
    assert(f != NULL);
    int rc = ERR_OK;
    for (size_t i = 0; i < arr->size && !rc; i++)
        rc = print_country_file(f, &(arr->arr[i]), 0);
    return rc;
}

int write_country_ind_arr(FILE *f, struct country_ind_arr_t *arr)
{
    assert(f != NULL);
    int rc = ERR_OK;
    for (size_t i = 0; i < arr->size && !rc; i++)
        rc = print_country_file(f, &(arr->arr[arr->indexes[i]]), 0);
    return rc;
}

int delete_country_arr(struct country_arr_t *arr, size_t ind)
{
    if (ind >= arr->size)
        return ERR_RANGE;
    for (size_t i = ind + 1; i < arr->size; i++)
        arr->arr[i - 1] = arr->arr[i];
    arr->size--;
    return ERR_OK;
}

int delete_country_ind_arr(struct country_ind_arr_t *arr, size_t ind)
{
    if (ind >= arr->size)
        return ERR_RANGE;
    size_t ind_val = arr->indexes[ind];
    for (size_t i = 0; i < arr->size; i++)
    {
        if (i >= ind)
            arr->indexes[i] = arr->indexes[i + 1];
        if (arr->indexes[i] > ind_val)
            arr->indexes[i]--;
        if (i >= ind_val)
            arr->arr[i] = arr->arr[i + 1];
    }
    arr->size--;
    return ERR_OK;
}

// void sort_country_arr(struct country_arr_t *arr)
// {
//     struct country_t tmp;
//     for (size_t i = 0; i < arr->size - 1; i++)
//     {
//         size_t best = i;
//         for (size_t now = i + 1; now < arr->size; now++)
//         {
//             if (cmp_country(&arr->arr[now], &arr->arr[best]) > 0)
//                 best = now;
//         }
//         if (best != i)
//         {
//             tmp = arr->arr[i];
//             arr->arr[i] = arr->arr[best];
//             arr->arr[best] = tmp;
//         }
//     }
// }

void sort_country_arr(struct country_arr_t *arr)
{
    struct country_t tmp;
    for (size_t i = arr->size - 1; i > 0; i--)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (cmp_country(&arr->arr[j], &arr->arr[j + 1]) < 0)
            {
                tmp = arr->arr[j];
                arr->arr[j] = arr->arr[j + 1];
                arr->arr[j + 1] = tmp;
            }
        }
    }
}

// void sort_country_ind_arr(struct country_ind_arr_t *arr)
// {
//     size_t tmp;
//     for (size_t i = 0; i < arr->size - 1; i++)
//     {
//         size_t best = i;
//         for (size_t now = i + 1; now < arr->size; now++)
//         {
//             if (cmp_country(&arr->arr[arr->indexes[now]], &arr->arr[arr->indexes[best]]) > 0)
//                 best = now;
//         }
//         if (best != i)
//         {
            // tmp = arr->indexes[i];
            // arr->indexes[i] = arr->indexes[best];
            // arr->indexes[best] = tmp;
//         }
//     }
// }

void sort_country_ind_arr(struct country_ind_arr_t *arr)
{
    size_t tmp;
    for (size_t i = arr->size - 1; i > 0; i--)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (cmp_country(&arr->arr[arr->indexes[j]], &arr->arr[arr->indexes[j + 1]]) < 0)
            {
                tmp = arr->indexes[j];
                arr->indexes[j] = arr->indexes[j + 1];
                arr->indexes[j + 1] = tmp;
            }
        }
    }
}

static int mystreq(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1), len2 = strlen(str2);
    if (len1 != len2)
        return 0;
    for (size_t i = 0; i < len1; i++)
        if (str1[i] != str2[i])
            return 0;
    return 1;
}

int find_country_arr(const struct country_arr_t *arr, const char *continent, int price, sport_t sp, struct country_arr_t *res)
{
    res->size = 0;
    for (size_t i = 0; i < arr->size; i++)
    {
        if (arr->arr[i].vacation_type == SPORT && arr->arr[i].vacation.sport == sp && arr->arr[i].price <= price && mystreq(continent, arr->arr[i].land))
            res->arr[res->size++] = arr->arr[i];
    }
    if (!res->size)
        return ERR_ARR_EMPTY;
    return ERR_OK;
}

int find_country_ind_arr(const struct country_ind_arr_t *arr, const char *continent, int price, sport_t sp, struct country_ind_arr_t *res)
{
    res->size = 0;
    for (size_t i = 0; i < arr->size; i++)
    {
        if (arr->arr[arr->indexes[i]].vacation_type == SPORT && arr->arr[arr->indexes[i]].vacation.sport == sp && arr->arr[arr->indexes[i]].price <= price && mystreq(continent, arr->arr[arr->indexes[i]].land))
        {    
            res->arr[res->size] = arr->arr[arr->indexes[i]];
            res->indexes[res->size] = res->size;
            res->size++;
        }
        
    }
    if (!res->size)
        return ERR_ARR_EMPTY;
    return ERR_OK;
}

void indtoarr(const struct country_ind_arr_t *ind_arr, struct country_arr_t *arr)
{
    arr->size = ind_arr->size;
    for (size_t i = 0; i < arr->size; i++)
        arr->arr[i] = ind_arr->arr[ind_arr->indexes[i]];
}

void arrtoind(const struct country_arr_t *arr, struct country_ind_arr_t *ind_arr)
{
    ind_arr->size = arr->size;
    for (size_t i = 0; i < arr->size; i++)
    {
        ind_arr->arr[i] = arr->arr[i];
        ind_arr->indexes[i] = i;
    }
}

void print_country_ind_arr(const struct country_ind_arr_t *ind_arr)
{
    printf("------------------------------------------------------------------------\n");
    for (size_t i = 0; i < ind_arr->size; i++)
    {
        printf("#%zu\n", i + 1);
        printf("Номер в исходном массиве %zu\n", ind_arr->indexes[i]);
        print_country_file(stdout, &ind_arr->arr[ind_arr->indexes[i]], 1);
        printf("------------------------------------------------------------------------\n");
    }
}

void print_country_arr(const struct country_arr_t *arr)
{
    printf("------------------------------------------------------------------------\n");
    for (size_t i = 0; i < arr->size; i++)
    {
        printf("#%zu\n", i + 1);
        print_country_file(stdout, &arr->arr[i], 1);
        printf("------------------------------------------------------------------------\n");
    }
}

size_t country_arr_partion(struct country_arr_t *arr, int low, int high)
{
    struct country_t *pivot = &(arr->arr[high]);
    struct country_t tmp;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (cmp_country(&(arr->arr[j]), pivot) >= 0)
        {
            i++;
            tmp = arr->arr[j];
            arr->arr[j] = arr->arr[i];
            arr->arr[i] = tmp;
        }
    }

    tmp = arr->arr[high];
    arr->arr[high] = arr->arr[i + 1];
    arr->arr[i + 1] = tmp;
    return (i + 1);
}

void qsort_country_arr(struct country_arr_t *arr, int low, int high)
{
    // qsort(arr->arr, sizeof(arr->arr[0]), sizeof(arr->arr) / sizeof(arr->arr[0]), cmp_country);
    if (low < high)
    {
        int piv = country_arr_partion(arr, low, high);
        qsort_country_arr(arr, low, piv - 1);
        qsort_country_arr(arr, piv + 1, high);
    }
}


int country_arr_ind_partion(struct country_ind_arr_t *arr, int low, int high)
{
    struct country_t *pivot = &(arr->arr[arr->indexes[high]]);
    int tmp;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (cmp_country(&(arr->arr[arr->indexes[j]]), pivot) >= 0)
        {
            i++;
            tmp = arr->indexes[j];
            arr->indexes[j] = arr->indexes[i];
            arr->indexes[i] = tmp;
        }
    }
    tmp = arr->indexes[high];
    arr->indexes[high] = arr->indexes[i + 1];
    arr->indexes[i + 1] = tmp;
    return (i + 1);
}

void qsort_country_ind_arr(struct country_ind_arr_t *arr, int low, int high)
{
    if (low < high)
    {
        int piv = country_arr_ind_partion(arr, low, high);
        qsort_country_ind_arr(arr, low, piv - 1);
        // if (piv == high)
        //     piv--;
        qsort_country_ind_arr(arr, piv + 1, high);
    }
}