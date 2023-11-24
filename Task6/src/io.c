#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errs.h"
#include "io.h"

void print_intro()
{
    printf("Данная программа выполняет базовые операции с двоичным деревом поиска, а также на основе дерева и стека может посчитать значение выражения A + (B * (C + (D * (E - F) - (G - H)) + I))");
}


void print_menu()
{
    printf("Выберите пункт меню:\n");
    printf("%d - Добавить символ в дерево.\n", ADD);
    printf("%d - Найти символ в дереве.\n", FIND);
    printf("%d - Удалить символ из дерева.\n", DELETE);
    printf("%d - Вывести префиксный обход дерева.\n", PREFIX);
    printf("%d - Вывести инфиксный обход дерева.\n", INFIX);
    printf("%d - Вывести постфиксный обход дерева.\n", POSTFIX);
    printf("%d - Вывести изображение дерева.\n", PRINT);
    printf("%d - Изменить переменные.\n", CHANGE);
    printf("%d - Посчитать выражение.\n", CALC);
    printf("%d - Сравнение времени вычисления выражения в дереве и стеке.\n", COMPARE);
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

// int read_file(FILE **f)
// {
//     FILE *tmp = NULL;
//     char *line = NULL;
//     size_t len;
//     printf("Введите имя файла: ");
//     if (getline(&line, &len, stdin) == -1)
//     {
//         free(line);
//         return ERR_IO;
//     }
//     len = strlen(line);
//     if (len || line[len - 1] == '\n')
//         line[len - 1] = '\0';
    
//     tmp = fopen(line, "r");
//     if (tmp == NULL)
//     {
//         free(line);
//         return ERR_WR_FNAME;
//     }

//     *f = tmp;
//     free(line);
//     return OK;
// }

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
        case OK:
            break;
        default:
            printf("Неизвестная ошибка.\n");
            break;
    }
}
