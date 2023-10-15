#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errs.h"
#include "io.h"

void print_intro()
{
    printf("Данная программа выполняет умножение матрицы целых на вектор столбец целых.\n");
}

void print_menu()
{
    printf("Выберите вариант умножения:\n");
    printf("%d - Умножение в форме хранения CRS.\n", MULT);
    printf("%d - Умножение в стандартной форме хранения.\n", STD_MULT);
    printf("%d - Сравнение двух вариантов умножения.\n", COMPAR);
    printf("%d - Выход.\n", EXIT);
    // printf("Введите номер: ");
}

int int_input(int *res, char *mes)
{
    char *line = NULL;
    size_t len;
    printf("%s", mes);
    if (getline(&line, &len, stdin) == -1)
    {
        free(line);
        return ERR_IO;
    }

    size_t i = 0;
    while (line[i] != '\n' && line[i] != '\0')
    {
        if (line[i] > '9' || line[i] < '0')
        {
            free(line);
            return ERR_FORMAT;
        }
        i++;
    }

    if (i == 0)
    {
        free(line);
        return ERR_FORMAT;
    }

    *res = 0;
    i = 0;
    while (line[i] != '\n' && line[i] != '\0')
    {
        *res *= 10;
        *res += (int) (line[i] - '0');
        i++;
    }
    free(line);
    return OK;
}

int read_file(FILE **f)
{
    FILE *tmp = NULL;
    char *line = NULL;
    size_t len;
    printf("Введите имя файла: ");
    if (getline(&line, &len, stdin) == -1)
    {
        free(line);
        return ERR_IO;
    }
    len = strlen(line);
    if (len || line[len - 1] == '\n')
        line[len - 1] = '\0';
    
    tmp = fopen(line, "r");
    if (tmp == NULL)
    {
        free(line);
        return ERR_WR_FNAME;
    }

    *f = tmp;
    free(line);
    return OK;
}

void print_error(int rc)
{
    switch (rc)
    {
        case ERR_IO:
            printf("Ошибка функций ввода/вывода.\n");
            break;
        case ERR_MEMORY:
            printf("Ошибка выделения памяти.\n");
            break;
        case ERR_FILE:
            printf("Ошибка при работе с файлом.\n");
            break;
        case ERR_INCOMP_SIZES:
            printf("Ошибка: Неподходящие размеры для умножения.\n");
            break;
        case ERR_NINIT_OBJ:
            printf("Ошибка: Невыделенный объект.\n");
            break;
        case ERR_FORMAT:
            printf("Ошибка: Некорретный формат ввода.\n");
            break;
        case ERR_NULL_SIZE:
            printf("Ошибка: Нулевой размер.\n");
            break;
        case ERR_COMMAND:
            printf("Ошибка: Некорректная команда.\n");
            break;
        case ERR_WR_FNAME:
            printf("Ошибка: Неправильное имя файла.\n");
            break;
        default:
            printf("Неизвестная ошибка.\n");
            break;
    }
}