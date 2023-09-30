#include "country.h"
#include "country_arr.h"
#include "menu.h"
#include "errs.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

long int get_time(struct timeval *time_s, struct timeval *time_e)
{
    return (time_e -> tv_sec * 1000000 + time_e -> tv_usec) - (time_s -> tv_sec * 1000000 + time_s -> tv_usec);
}

#define MAX_FILE_NAME (32 + 1)

int main(void)
{
    int working = 1;
    int action = 0;
    int rc = ERR_OK;
    FILE *f = NULL;
    char fname[MAX_ARRAY_SIZE];
    struct country_ind_arr_t arr;
    struct country_arr_t w_arr;
    arr.size = 0;
    struct country_t tmp_ctry;

    while (working)
    {
        rc = ERR_OK;
        // flush_stdin();
        print_menu();
        action = select_action();
        if (!action)
            working = 0;
        else if (action == -2)
            printf("Ошибка ввода/вывода, попробуйте снова.\n");
        else if (action == -1)
            printf("Неккоректный ввод.\n");
        else if (action == 1)
        {
            printf("Введите имя файла(Максимальная длина %d): ", MAX_FILE_NAME - 1);
            rc = str_read(stdin, fname, MAX_ARRAY_SIZE);
            if (!rc)
            {
                if (f != NULL)
                    fclose(f);
                f = fopen(fname, "r+");
                if (f == NULL)
                    rc = ERR_FILE;
                else
                {
                    if (arr.size != 0)
                    {
                        int des = 0;
                        int_input(&des, "Файл открыт. Хотите считать оттуда данные, заменив нынешнюю таблицу?(1 - да, любая другая строка - нет): ");
                        if (des == 1)
                        {
                            rc = read_country_ind_arr(f, &arr);
                            if (!rc)
                                printf("Файл успешно считан.\n");
                        }   
                    }
                    else
                    {
                        rc = read_country_ind_arr(f, &arr);
                        if (!rc)
                            printf("Файл успешно считан.\n");
                    }   
                }
            }
            print_error(rc);
        }
        else if (action == 2)
        {
            if (arr.size == 0)
                printf("Пустая таблица.\n");
            else
            {
                print_country_ind_arr(&arr);
            }
        }
        else if (action == 3)
        {
            if (arr.size == MAX_ARRAY_SIZE)
                printf("Максимальный размер таблицы(%d стран)", MAX_ARRAY_SIZE);
            else
            {
                    rc = read_country_file(stdin, &tmp_ctry, 1);
                    if (!rc)
                    {
                        rc = add_country_ind_arr(&arr, &tmp_ctry);
                    }
            }   
            print_error(rc);
        }
        else if (action == 4)
        {
            int num = -1;
            rc = int_input(&num, "Введите номер удаляемого элемента: ");
            if (!rc)
                rc = delete_country_ind_arr(&arr, num - 1);
            if (!rc)
                printf("Элемент успешно удален!");
            print_error(rc);
        }   
        else if (action == 5)
        {
            char land[LAND_SIZE];
            int price;
            sport_t sp;
            printf("Введите материк(Максимальное количество символов %d): ", LAND_SIZE - 1);
            rc = str_read(stdin, land, LAND_SIZE);
            if (!rc)
                rc = int_input(&price, "Введите максимальную цену: ");
            if (!rc)
            {
                int tmp;
                printf("Введите вид спорта(%d - Лыжи, %d - Сёрфинг, %d - Сплав, %d - Восхождение):", SKIING, SURFING, ALLOY, HIKING);
                rc = int_input(&tmp, " ");
                if (!rc && (tmp > 3 || tmp < 0))
                    rc = ERR_INPUT_VAL;
                if (!rc)
                    sp = tmp;
            }
            if (!rc)
            {
                struct country_ind_arr_t tmp_arr;
                rc = find_country_ind_arr(&arr, land, price, sp, &tmp_arr);
                if (!rc)
                {
                    print_country_ind_arr(&tmp_arr);
                }
            }
            print_error(rc);
        }
        else if (action == 6)
        {
            if (f == NULL) 
                rc = ERR_FILE;
            if (!rc)
            {
                fclose(f);
                fopen(fname, "w+");
                rc = write_country_ind_arr(f, &arr);
                fclose(f);
                fopen(fname, "r+");
            }
            if (!rc)
                printf("Успешно записано.");
            print_error(rc);
        }
        else if (action == 7)
        {
            if (arr.size == 0)
                rc = ERR_ARR_EMPTY;
            
            if (!rc)
            {
                // qsort_country_ind_arr(&arr, 0, arr.size - 1);
                sort_country_ind_arr(&arr);
                printf("Страны отсортированы.\n");
            }
            print_error(rc);   
        }
        else if (action == 8)
        {
            if (arr.size == 0)
                rc = ERR_ARR_EMPTY;
            
            if (!rc)
            {
                indtoarr(&arr, &w_arr);
                // qsort_country_arr(&w_arr, 0, w_arr.size - 1);
                sort_country_arr(&w_arr);
                arrtoind(&w_arr, &arr);
                printf("Страны отсортированы.\n");
            }
            print_error(rc);
        }
        else if (action == 9)
        {
            if (arr.size == 0)
                rc = ERR_ARR_EMPTY;
            if (!rc)
            {
                long mys_ind, mys, qs, qs_ind;
                size_t ind_s = sizeof(arr), arr_s = sizeof(w_arr);
                struct timeval time_s, time_e;
                struct country_ind_arr_t tmp_ind_arr;

                indtoarr(&arr, &w_arr);
                gettimeofday(&time_s, NULL);
                sort_country_arr(&w_arr);
                gettimeofday(&time_e, NULL);
                mys = get_time(&time_s, &time_e);

                indtoarr(&arr, &w_arr);
                gettimeofday(&time_s, NULL);
                qsort_country_arr(&w_arr, 0, w_arr.size - 1);
                gettimeofday(&time_e, NULL);
                qs = get_time(&time_s, &time_e);

                tmp_ind_arr = arr;
                gettimeofday(&time_s, NULL);
                sort_country_ind_arr(&tmp_ind_arr);
                gettimeofday(&time_e, NULL);
                mys_ind = get_time(&time_s, &time_e);

                tmp_ind_arr = arr;
                gettimeofday(&time_s, NULL);
                qsort_country_ind_arr(&tmp_ind_arr, 0, arr.size - 1);
                gettimeofday(&time_e, NULL);
                qs_ind = get_time(&time_s, &time_e);

                print_sort_tables(qs_ind, qs, mys_ind, mys, ind_s, arr_s);
            }
            print_error(rc);
        }
        else
            printf("Некорректный код.\n");
    }
    if (f != NULL)
        fclose(f);
}