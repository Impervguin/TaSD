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

int main(void)
{
    node_t *mem_queue = NULL;
    time_t seed = time(NULL);
    int command;
    int rc = OK;
    int running = 1;
    struct timeval start, end;
    long time_static, time_list;
    double t1_entry_min = 1, t1_entry_max = 5;
    double t2_entry_min = 0, t2_entry_max = 3;
    double t1_exec_min = 0, t1_exec_max = 4;
    double t2_exec_min = 0, t2_exec_max = 1;
    size_t requests_cnt = 1000;
    size_t cnt1, cnt2;

    print_intro();

    while (running)
    {
        srand(seed);
        double tmp_t1_entry_min, tmp_t1_entry_max;
        double tmp_t2_entry_min, tmp_t2_entry_max;
        double tmp_t1_exec_min, tmp_t1_exec_max;
        double tmp_t2_exec_min, tmp_t2_exec_max;
        int mem_inf = 0;
        int tmp_requests_cnt;
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
            switch (command)
            {
            case STATIC_SIM:
                rc = static_sim(t1_entry_min, t1_entry_max, t2_entry_min, t2_entry_max, t1_exec_min, t1_exec_max, t2_exec_min, t2_exec_max, requests_cnt, &cnt1, 1);
                break;
            case LIST_SIM:
                rc = int_input(&mem_inf, "Хотите выводить информацию о памяти при добавлении/удалении в очередь заявок 1(1 - да, 0 - нет).");
                if (!rc && mem_inf != 0 && mem_inf != 1)
                    rc = ERR_FORMAT;
                if (!rc)
                    rc = list_sim(t1_entry_min, t1_entry_max, t2_entry_min, t2_entry_max, t1_exec_min, t1_exec_max, t2_exec_min, t2_exec_max, requests_cnt, &cnt2, &mem_queue, mem_inf, 1);
                
                if (!rc && mem_inf)
                {
                    int tmp = 0;
                    rc = int_input(&tmp, "Хотите вывести все освободившиеся адреса(1 - да, 0 - нет): ");
                    if (!rc && tmp == 1)
                    {
                        void *data = NULL;
                        printf("Освобожденные адреса:\n");
                        while (!rlist_pop(&mem_queue, &data))
                        {
                            printf("%p\n", data);
                        }
                    }
                    else if (tmp != 0 && !rc)
                        rc = ERR_FORMAT;
                    rlist_free(&mem_queue);
                }
                break;
            case MODIFY_PARAMS:
                printf("Нынешний интервал создания заявок 1: (%.2lf, %.2lf).\n", t1_entry_min, t1_entry_max);
                printf("Нынешний интервал создания заявок 2: (%.2lf, %.2lf).\n", t2_entry_min, t2_entry_max);
                printf("Нынешний интервал исполнения заявок 1: (%.2lf, %.2lf).\n", t1_exec_min, t1_exec_max);
                printf("Нынешний интервал исполнения заявок 2: (%.2lf, %.2lf).\n", t2_exec_min, t2_exec_max);
                printf("Необходимое количество заявок: %zu\n", requests_cnt);
                rc = double_input(&tmp_t1_entry_min, "Введите нижнюю границу интервала создания заявок 1(вещественное): ");
                if (!rc)
                    rc = double_input(&tmp_t1_entry_max, "Введите верхнюю границу интервала создания заявок 2(вещественное): ");
                if (!rc && (tmp_t1_entry_min > tmp_t1_entry_max || tmp_t1_entry_min < 0))
                    rc = ERR_INTERVAL;
                if (!rc)
                    rc = double_input(&tmp_t2_entry_min, "Введите нижнюю границу интервала создания заявок 1(вещественное): ");
                if (!rc)
                    rc = double_input(&tmp_t2_entry_max, "Введите верхнюю границу интервала создания заявок 2(вещественное): ");
                if (!rc && (tmp_t2_entry_min > tmp_t2_entry_max || tmp_t2_entry_min < 0))
                    rc = ERR_INTERVAL;
                if (!rc)
                    rc = double_input(&tmp_t1_exec_min, "Введите нижнюю границу интервала исполнения заявок 1(вещественное): ");
                if (!rc)
                    rc = double_input(&tmp_t1_exec_max, "Введите верхнюю границу интервала исполнения заявок 2(вещественное): ");
                if (!rc && (tmp_t1_exec_min > tmp_t1_exec_max || tmp_t1_exec_min < 0))
                    rc = ERR_INTERVAL;
                if (!rc)
                    rc = double_input(&tmp_t2_exec_min, "Введите нижнюю границу интервала исполнения заявок 1(вещественное): ");
                if (!rc)
                    rc = double_input(&tmp_t2_exec_max, "Введите верхнюю границу интервала исполнения заявок 2(вещественное): ");
                if (!rc && (tmp_t2_exec_min > tmp_t2_exec_max || tmp_t2_exec_min < 0))
                    rc = ERR_INTERVAL;
                if (!rc)
                {
                    rc = int_input(&tmp_requests_cnt, "Введите необходимое количество заявок 1: ");
                    if (!rc && tmp_requests_cnt <= 0)
                        rc = ERR_FORMAT;
                }
                if (!rc)
                {
                    t1_entry_max = tmp_t1_entry_max;
                    t2_entry_max = tmp_t2_entry_max;
                    t1_entry_min = tmp_t1_entry_min;
                    t2_entry_min = tmp_t2_entry_min;
                    t1_exec_max = tmp_t1_exec_max;
                    t2_exec_max = tmp_t2_exec_max;
                    t1_exec_min = tmp_t1_exec_min;
                    t2_exec_min = tmp_t2_exec_min;
                    requests_cnt = tmp_requests_cnt;
                }
                break;
            
            case COMPARE:
                gettimeofday(&start, NULL);
                rc = static_sim(t1_entry_min, t1_entry_max, t2_entry_min, t2_entry_max, t1_exec_min, t1_exec_max, t2_exec_min, t2_exec_max, requests_cnt, &cnt1, 0);
                gettimeofday(&end, NULL);
                time_static = get_time(&start, &end);
                if (!rc)
                {
                    srand(seed);
                    gettimeofday(&start, NULL);
                    rc = list_sim(t1_entry_min, t1_entry_max, t2_entry_min, t2_entry_max, t1_exec_min, t1_exec_max, t2_exec_min, t2_exec_max, requests_cnt, &cnt2, &mem_queue, 0,  0);
                    gettimeofday(&end, NULL);
                    time_list = get_time(&start, &end);
                }
                if (!rc)
                {
                    printf("Время статической симуляции: %ld\n", time_static);
                    printf("Время симуляции списком: %ld\n", time_list);
                    printf("Максимальная память для статической симуляции: %zu байт\n", get_static_memory(cnt1));
                    printf("Максимальная память для симуляции списком: %zu байт\n", get_list_memory(cnt2));
                }
                break;
            }
        }
        print_error(rc);   
    }   
    return OK;
}


