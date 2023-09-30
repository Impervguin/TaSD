#include <stdio.h>
#include <string.h>
#include "country.h"
#include "country_arr.h"
#include "errs.h"
#include "menu.h"


int str_read(FILE *f, char *str, size_t max_size)
{
    if (fgets(str, max_size, f) == NULL && !feof(f))
        return ERR_IO;
    size_t len = strlen(str);
    if (len && str[len - 1] != '\n')
        return ERR_STR_RANGE;
    str[--len] = '\0';

    if (!len)
        return ERR_STR_EMPTY;
    return ERR_OK;
}

void print_menu()
{
    printf("МЕНЮ\n");
    printf("1 - Ввести файл для работы.\n");
    printf("2 - Вывести текущую таблицу.\n");
    printf("3 - Добавить страну в таблицу.\n");
    printf("4 - Удалить страну из таблицы.\n");
    printf("5 - Вывести список стран на выбранном материке, со стоимостью ниже указанной, где можно заняться указанным видом спорта.\n");
    printf("6 - Сохранить таблицу в файл.\n");
    printf("7 - Отсортитировать страны по цене путешествия.\n");
    printf("8 - Отсортитировать страны по цене путешествия без индексов.\n");
    printf("9 - Сравнить сортировку выбором и быструю на данной таблице данных.\n");
    printf("0 - Выход.\n");
}

int select_action()
{
    char inp[MAX_INPUT_SIZE];
    printf("Введите действие: ");
    if (fgets(inp, MAX_INPUT_SIZE, stdin) == NULL && !feof(stdin))
        return ERR_INPUT_IO;
    
    size_t len = strlen(inp);
    if (len && inp[len - 1] == '\n')
        inp[--len] = '\0';
    
    if (!len || len > 1 || inp[0] > '9' || inp[0] < '0')
        return ERR_INPUT_VAL;
    
    return (int) inp[0] - '0';
}

int int_input(int *res, const char *mes)
{
    char inp[MAX_INPUT_SIZE];
    printf("%s", mes);
    if (fgets(inp, MAX_INPUT_SIZE, stdin) == NULL && !feof(stdin))
        return ERR_INPUT_IO;
    
    size_t len = strlen(inp);
    if (len && inp[len - 1] == '\n')
        inp[--len] = '\0';
    
    if (!len || len == MAX_INPUT_SIZE)
        return ERR_INPUT_VAL;
    *res = 0;
    for (size_t i = 0; i < len; i++)
    {
        if (inp[i] > '9' || inp[i] < '0')
            return ERR_INPUT_VAL;
        *res *= 10;
        *res += (int) inp[i] - '0';
    }
    return ERR_OK;
}

void print_error(int rc)
{
    switch (rc)
    {
    case ERR_OK:
        break;
    case ERR_IO:
        printf("Ошибка ввода/вывода.\n");
        break;
    case ERR_STR_RANGE:
        printf("Ошибка длины строки.\n");
        break;
    case ERR_STR_EMPTY:
        printf("Пустая строка.\n");
        break;
    case ERR_ARR_RANGE:
        printf("Ошибка длины массива.\n");
        break;
    case ERR_ARR_EMPTY:
        printf("Пустой массив.\n");
        break;
    case ERR_RANGE:
        printf("Выход за границы.\n");
        break;
    case ERR_CORR_FILE:
        printf("Слишком большой файл.\n");
        break;
    case ERR_FILE:
        printf("Ошибка с открытием файла.\n");
        break;
    case ERR_INPUT_IO:
        printf("Ошибка ввода/вывода.\n");
        break;
    case ERR_INPUT_VAL:
        printf("Неккоректное значение.\n");
        break;
    default:
        printf("Неизвестная ошибка.\n");
        break;
    }
}

void print_sort_tables(long qsi_t, long qsa_t, long msi_t, long msa_t, size_t isize, size_t asize)
{
    printf("------------------------------------------------------------------------\n");
    printf("Время быстрой сортировки в массиве с индексами: %ld мкс\n", qsi_t);
    printf("Время быстрой сортировки в массиве без индексов: %ld мкс\n", qsa_t);
    printf("Время сортировки выбором в массиве с индексами: %ld мкс\n", msi_t);
    printf("Время сортировки выбором в массиве без индексов: %ld мкс\n", msa_t);
    printf("------------------------------------------------------------------------\n");
    printf("Объём массива с индексами: %zu байт.\n", isize);
    printf("Объём массива без индексов: %zu байт.\n", asize);
    printf("------------------------------------------------------------------------\n");
}