#include <stdio.h>
#include "errs.h"
#include "io.h"
#include "list_stack.h"
#include "static_stack.h"
#include "btree.h"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

long long int get_time(struct timespec *time_s, struct timespec *time_e)
{
    return (time_e -> tv_sec * 1000000000 + time_e -> tv_nsec) - (time_s -> tv_sec * 1000000000 + time_s -> tv_nsec);
}

#define TEST_COUNT 1000000
#undef RAND_MAX
#define RAND_MAX 20
int main()
{
    int rc;
    int A,B,C,D,E,F,G,H,I;
    btree_node *calc_root = NULL;
    long long tree_time = 0, static_time = 0, list_time = 0;
    struct timespec st, ed;
    int itmp;
    
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        A = rand(), B = rand(), C = rand(), D = rand(), E = rand(), F = rand(), G = rand(), H = rand(), I = rand();
        rc = expression_in_btree(A, B, C, D, E, F, G, H, I, &calc_root);
        if (rc)
            return 1;
        
        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        rc = btree_calculate(&calc_root, &itmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
        if (rc)
            return 1;
        tree_time += get_time(&st, &ed);
    }
    tree_time = tree_time / TEST_COUNT;
    
    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        A = rand(), B = rand(), C = rand(), D = rand(), E = rand(), F = rand(), G = rand(), H = rand(), I = rand();
        rc = expression_in_btree(A, B, C, D, E, F, G, H, I, &calc_root);
        if (rc)
            return 1;
        
        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        rc = btree_calculate(&calc_root, &itmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
        if (rc)
            return 1;
        tree_time += get_time(&st, &ed);
    }
    tree_time = tree_time / TEST_COUNT;

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        A = rand(), B = rand(), C = rand(), D = rand(), E = rand(), F = rand(), G = rand(), H = rand(), I = rand();
        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        rc = static_calculate_expression(A, B, C, D, E, F, G, H, I, &itmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
        if (rc)
            return 1;
        static_time += get_time(&st, &ed);
    }
    static_time = static_time / TEST_COUNT;



    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        A = rand(), B = rand(), C = rand(), D = rand(), E = rand(), F = rand(), G = rand(), H = rand(), I = rand();
        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        rc = list_calculate_expression(A, B, C, D, E, F, G, H, I, &itmp);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
        if (rc)
            return 1;
        list_time += get_time(&st, &ed);
    }
    list_time = list_time / TEST_COUNT;

    printf("Время подсчета деревом - %lld нс.\n", tree_time);
    printf("Время подсчета статическим стеком - %lld нс.\n", static_time);
    printf("Время подсчета стеком-списком - %lld нс.\n", list_time);
}