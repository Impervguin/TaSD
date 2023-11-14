#include <stdio.h>
#include "static_queue.h"
#include "list_queue.h"
#include "errs.h"
#include "io.h"
#include "request.h"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

long int get_time(struct timeval *time_s, struct timeval *time_e)
{
    return (time_e -> tv_sec * 1000000 + time_e -> tv_usec) - (time_s -> tv_sec * 1000000 + time_s -> tv_usec);
}

#define TEST_COUNT 1000

int main(int argc, char **argv)
{
    struct timeval start, end;
    long static_time = 0, list_time = 0;
    size_t static_cnt = 0, list_cnt = 0;
    int rc;
    if (argc != 2)
        return 1;

    double t1_entry_min = 1, t1_entry_max = 5;
    double t2_entry_min = 0, t2_entry_max = 3;
    double t1_exec_min = 0, t1_exec_max = 4;
    double t2_exec_min = 0, t2_exec_max = 1;
    size_t requests_cnt = atoi(argv[1]);
        
    for (size_t i = 0; i < TEST_COUNT && !rc; i++)
    {
        size_t cnt = 0;
        gettimeofday(&start, NULL);
        rc = static_sim(t1_entry_min, t1_entry_max, t2_entry_min, t2_entry_max, t1_exec_min, t1_exec_max, t2_exec_min, t2_exec_max, requests_cnt, &cnt, 0);
        gettimeofday(&end, NULL);
        static_time += get_time(&start, &end);
        static_cnt += cnt;
    }
    static_time /= TEST_COUNT;
    static_cnt /= TEST_COUNT;
    
    if (!rc)
    {
        for (size_t i = 0; i < TEST_COUNT && !rc; i++)
        {
            size_t cnt = 0;
            gettimeofday(&start, NULL);
            rc = list_sim(t1_entry_min, t1_entry_max, t2_entry_min, t2_entry_max, t1_exec_min, t1_exec_max, t2_exec_min, t2_exec_max, requests_cnt, &cnt, NULL, 0, 0);
            gettimeofday(&end, NULL);
            list_time += get_time(&start, &end);
            list_cnt += cnt;
        }
        list_time /= TEST_COUNT;
        list_cnt /= TEST_COUNT;
    }

    if (!rc)
    {
        printf("Время вычисления статической очереди: %ld мкс.\n", static_time);
        printf("Время вычисления списка-очереди: %ld мкс.\n", list_time);
        printf("\n");
        printf("Объем памяти по статической очериди: %zu байт.\n", get_static_memory(static_cnt));
        printf("Объем памяти по списку-очереди: %zu байт.\n", get_list_memory(list_cnt));
    }

    return rc;
}