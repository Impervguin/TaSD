#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errs.h"
#include "io.h"

void print_intro()
{
    printf("Данная программа выполняет поиск недостижимых узлов в графе из заданного узла.\n");
}


void print_menu()
{
    printf("Выберите пункт меню:\n");
    printf("%d - Изменить граф.\n", GRAPH);
    printf("%d - Найти недостижимые узлы поиском в ширину.\n", BFSC);
    printf("%d - Найти недостижимые узлы поиском в глубину.\n", DFSC);
    printf("%d - Сравнить алгоритмы.\n", COMPARE);
    printf("%d - Выход.\n", EXIT);
    printf("Введите номер: ");
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
    int minus = 0;
    size_t i = 0;
    if (line[0] == '-')
    {
        minus = 1;
        i++;
    }
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
    i = minus ? 1 : 0;
    while (line[i] != '\n' && line[i] != '\0')
    {
        *res *= 10;
        *res += (int) (line[i] - '0');
        i++;
    }
    if (minus)
        *res *= -1;
    free(line);
    return OK;
}

int char_input(char *res, char *mes)
{
    char *line = NULL;
    size_t len;
    printf("%s", mes);
    if (getline(&line, &len, stdin) == -1)
    {
        free(line);
        return ERR_IO;
    }

    len = strlen(line);
    if (len != 2)
    {
        free(line);
        return ERR_FORMAT;
    }

    *res = line[0];
    free(line);
    return OK;
}

int double_input(double *res, char *mes)
{
    char *line = NULL;
    size_t len;
    printf("%s", mes);
    if (getline(&line, &len, stdin) == -1)
    {
        free(line);
        return ERR_IO;
    }
    int rc = OK;
    char tmp[20];
    int code;
    if ((code = sscanf(line, "%lf%20s", res, tmp)) < 1)
        rc = ERR_FORMAT;
    
    for (char *now = tmp; *now != '\n' && *now != '\0' && code != 1 && !rc; now++)
    {
        if (*now != ' ')
        {
            rc = ERR_FORMAT;
            break;
        }
    }
    
    if (*res < 0 && !rc)
        rc = ERR_FORMAT;
    free(line);
    return rc;
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
        case ERR_FORMAT:
            printf("Ошибка: Некорректный формат ввода.\n");
            break;
        case ERR_COMMAND:
            printf("Ошибка: Некорректная команда.\n");
            break;
        case ERR_FILE_IO:
            printf("Ошибка файлового ввода/вывода.\n");
            break;
        case ERR_ZERO_DIVISION:
            printf("Ошибка: Деление на ноль.\n");
            break;
        case ERR_ALREADY_IN:
            printf("Ошибка: Элемент уже существует.\n");
            break;
        case ERR_NOT_FOUND:
            printf("Ошибка: Элемент не найден.\n");
            break;
        case ERR_EMPTY_STACK:
            printf("Ошибка: пустой стек.\n");
            break;
        case ERR_STACK_OVERFLOW:
            printf("Ошибка: переполнение стека.\n");
            break;
        case ERR_WR_FNAME:
            printf("Ошибка: Не удалось использовать файл.\n");
            break;
        case ERR_RANGE:
            printf("Ошибка: Некорректные границы.\n");
            break;
        case OK:
            break;
        default:
            printf("Неизвестная ошибка.\n");
            break;
    }
}
