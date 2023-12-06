#include <stdio.h>
#include "errs.h"
#include "btree.h"
#include "int_btree.h"
#include "open_hash_table.h"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

// #define RAND_MAX 17
#define RAND 40
int get_random(int max)
{
    return (int) ((((double) rand()) / RAND_MAX) * max);
}

long long int get_time(struct timespec *time_s, struct timespec *time_e)
{
    return (time_e -> tv_sec * 1000000000 + time_e -> tv_nsec) - (time_s -> tv_sec * 1000000000 + time_s -> tv_nsec);
}

#define TEST_COUNT 1000000
// #undef RAND_MAX


int main()
{
    int rc;
    btree_node *calc_root = NULL;
    int_node_t *broot = NULL;
    int_node_t *avlroot = NULL;
    ohash_table_t table5, table10, table15, table20;
    int *arr = NULL;
    size_t arr_size = 0;
    init_open_hash(&table5);
    init_open_hash(&table10);
    init_open_hash(&table15);
    init_open_hash(&table20);
    rc = resize_open_hash(&table10, 10);
    if (rc)
        return rc;
    rc = resize_open_hash(&table15, 15);
    if (rc)
        return rc;
    rc = resize_open_hash(&table20, 20);
    if (rc)
        return rc;
    int A,B,C,D,E,F,G,H,I;
    long long tree_time = 0, avl_time = 0, table5_time = 0, table10_time = 0, table15_time = 0, table20_time = 0;
    size_t tree_cmp = 0, avl_cmp = 0, table5_cmp = 0, table10_cmp = 0, table15_cmp = 0, table20_cmp = 0;
    struct timespec st, ed;
    
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        A = get_random(40), B = get_random(40), C = get_random(40), D = get_random(40), E = get_random(40), F = get_random(40), G = get_random(40), H = get_random(40), I = get_random(40);
        rc = expression_in_btree(A, B, C, D, E, F, G, H, I, &calc_root);
        if (rc)
            return 1;
        
        btree_postfix_calculate(&calc_root);
        arr = btree_infix_arr(calc_root, &arr_size);
        int num = get_random(arr_size);
        broot = arr_in_inttree(arr, arr_size);

        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        inttree_find(broot, arr[num], &tree_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
        tree_time += get_time(&st, &ed);
        btree_free(&calc_root);
        free_inttree(&broot);
        free(arr);
        arr_size = 0;
    }
    tree_time = tree_time / TEST_COUNT;
    tree_cmp = tree_cmp / TEST_COUNT;

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        A = get_random(40), B = get_random(40), C = get_random(40), D = get_random(40), E = get_random(40), F = get_random(40), G = get_random(40), H = get_random(40), I = get_random(40);
        rc = expression_in_btree(A, B, C, D, E, F, G, H, I, &calc_root);
        if (rc)
            return 1;
        
        btree_postfix_calculate(&calc_root);
        arr = btree_infix_arr(calc_root, &arr_size);
        int num = get_random(arr_size);
        avlroot = arr_in_intavl(arr, arr_size);

        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        inttree_find(avlroot, arr[num], &avl_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
        avl_time += get_time(&st, &ed);
        btree_free(&calc_root);
        free_inttree(&avlroot);
        free(arr);
        arr_size = 0;
    }
    avl_time = avl_time / TEST_COUNT;
    avl_cmp = avl_cmp / TEST_COUNT;

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        A = get_random(40), B = get_random(40), C = get_random(40), D = get_random(40), E = get_random(40), F = get_random(40), G = get_random(40), H = get_random(40), I = get_random(40);
        rc = expression_in_btree(A, B, C, D, E, F, G, H, I, &calc_root);
        if (rc)
            return 1;
        
        btree_postfix_calculate(&calc_root);
        arr = btree_infix_arr(calc_root, &arr_size);
        int num = get_random(arr_size);
        arr_in_open_hash(&table5, arr, arr_size);

        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        find_open_hash(&table5, arr[num], &table5_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);

        table5_time += get_time(&st, &ed);
        btree_free(&calc_root);
        clear_open_hash(&table5);
        free(arr);
        arr_size = 0;
    }
    table5_time = table5_time / TEST_COUNT;
    table5_cmp = table5_cmp / TEST_COUNT;

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        A = get_random(40), B = get_random(40), C = get_random(40), D = get_random(40), E = get_random(40), F = get_random(40), G = get_random(40), H = get_random(40), I = get_random(40);
        rc = expression_in_btree(A, B, C, D, E, F, G, H, I, &calc_root);
        if (rc)
            return 1;
        
        btree_postfix_calculate(&calc_root);
        arr = btree_infix_arr(calc_root, &arr_size);
        int num = get_random(arr_size);
        arr_in_open_hash(&table10, arr, arr_size);

        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        find_open_hash(&table10, arr[num], &table10_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);

        table10_time += get_time(&st, &ed);
        btree_free(&calc_root);
        clear_open_hash(&table10);
        free(arr);
        arr_size = 0;
    }
    table10_time = table10_time / TEST_COUNT;
    table10_cmp = table10_cmp / TEST_COUNT;

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        A = get_random(40), B = get_random(40), C = get_random(40), D = get_random(40), E = get_random(40), F = get_random(40), G = get_random(40), H = get_random(40), I = get_random(40);
        rc = expression_in_btree(A, B, C, D, E, F, G, H, I, &calc_root);
        if (rc)
            return 1;
        
        btree_postfix_calculate(&calc_root);
        arr = btree_infix_arr(calc_root, &arr_size);
        int num = get_random(arr_size);
        arr_in_open_hash(&table15, arr, arr_size);

        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        find_open_hash(&table15, arr[num], &table15_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);

        table15_time += get_time(&st, &ed);
        btree_free(&calc_root);
        clear_open_hash(&table15);
        free(arr);
        arr_size = 0;
    }
    table15_time = table15_time / TEST_COUNT;
    table15_cmp = table15_cmp / TEST_COUNT;

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        A = get_random(40), B = get_random(40), C = get_random(40), D = get_random(40), E = get_random(40), F = get_random(40), G = get_random(40), H = get_random(40), I = get_random(40);
        rc = expression_in_btree(A, B, C, D, E, F, G, H, I, &calc_root);
        if (rc)
            return 1;
        
        btree_postfix_calculate(&calc_root);
        arr = btree_infix_arr(calc_root, &arr_size);
        int num = get_random(arr_size);
        arr_in_open_hash(&table20, arr, arr_size);

        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        find_open_hash(&table20, arr[num], &table20_cmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);

        table20_time += get_time(&st, &ed);
        btree_free(&calc_root);
        clear_open_hash(&table20);
        free(arr);
        arr_size = 0;
    }
    table20_time = table20_time / TEST_COUNT;
    table20_cmp = table20_cmp / TEST_COUNT;
    
    
    printf("Время поиска деревом - %lld нс.\n", tree_time);
    printf("Количество сравнений деревом - %zu.\n", tree_cmp);
    printf("Время поиска АВЛ-деревом - %lld нс.\n", avl_time);
    printf("Количество сравнений АВЛ-деревом - %zu.\n", avl_cmp);
    printf("Время поиска Табл 5 - %lld нс.\n",  table5_time);
    printf("Количество сравнений Табл 5 - %zu.\n", table5_cmp);
    printf("Время поиска Табл 10 - %lld нс.\n",  table10_time);
    printf("Количество сравнений Табл 10 - %zu.\n", table10_cmp);
    printf("Время поиска Табл 15 - %lld нс.\n",  table15_time);
    printf("Количество сравнений Табл 15 - %zu.\n", table15_cmp);
    printf("Время поиска Табл 20 - %lld нс.\n",  table20_time);
    printf("Количество сравнений Табл 20 - %zu.\n", table20_cmp);
}