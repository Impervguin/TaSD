#include <stdio.h>
#include <string.h>
#include "errs.h"
#include "operation.h"
#include "list_stack.h"
#include "static_stack.h"
#include <time.h>
#include <sys/time.h>

long int get_time(struct timeval *time_s, struct timeval *time_e)
{
    return (time_e -> tv_sec * 1000000 + time_e -> tv_usec) - (time_s -> tv_sec * 1000000 + time_s -> tv_usec);
}

#define TEST_COUNT 1000

int main(int argc, char **argv)
{
    int static_mem, list_mem;
    stack_node_t *list_op = NULL;
    stack_node_t *list_nums = NULL;
    struct timeval start, end;
    long static_time = 0, list_time = 0;
    static_stack_t static_op;
    init_static_stack(&static_op);
    static_stack_t static_nums;
    init_static_stack(&static_nums);
    FILE *f = NULL;
    int res;
    int rc;
    if (argc != 2)
        return 1;
    
    f = fopen(argv[1], "r");
    if (f == NULL)
        return ERR_WR_FNAME;
    
    rc = static_read_operation(f, &static_nums, &static_op);
    if (!rc)
    {
        static_mem = get_static_stack_memory(&static_nums) + get_static_stack_memory(&static_op);
        
        int *ptr_nums = static_nums.head_ptr;
        int *ptr_op = static_op.head_ptr;
        for (size_t i = 0; i < TEST_COUNT && !rc; i++)
        {
            static_nums.head_ptr = ptr_nums;
            static_op.head_ptr = ptr_op;
            gettimeofday(&start, NULL);
            rc = static_calc(&static_nums, &static_op, &res);
            gettimeofday(&end, NULL);
            static_time += get_time(&start, &end);
        }
        static_time /= TEST_COUNT;
        
        if (!rc)
        {
            rewind(f);
            rc = list_read_operation(f, &list_nums, &list_op);
            list_mem = get_list_stack_memory(list_nums) + get_list_stack_memory(list_op);
            for (size_t i = 0; i < TEST_COUNT && !rc; i++)
            {
                rewind(f);
                rc = list_read_operation(f, &list_nums, &list_op);
                if (!rc)
                {
                    gettimeofday(&start, NULL);
                    rc = list_calc(&list_nums, &list_op, &res);
                    gettimeofday(&end, NULL);
                    list_time += get_time(&start, &end);
                }
            }
            list_time /= TEST_COUNT;
        }
    }

    if (!rc)
    {
        printf("Время вычисления статического стека: %ld мкс.\n", static_time);
        printf("Время вычисления списка-стека: %ld мкс.\n", list_time);
        printf("\n");
        printf("Объем памяти по статический стек: %d байт.\n", static_mem);
        printf("Объем памяти по список-стек: %d байт.\n", list_mem);
    }

    return rc;
}