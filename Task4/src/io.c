#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errs.h"
#include "io.h"

void print_intro()
{
    printf("Данная программа выполняет базовые операции со стеком, а также высчитывает выражения формата число|знак...число.\n");
}

void print_menu()
{
    printf("Выберите пункт меню:\n");
    printf("%d - Считать стек из файла.\n", READ_STACK);
    printf("%d - Добавить элемент в стек.\n", ADD);
    printf("%d - Удалить элемент из стека.\n", POP);
    printf("%d - Провести операцию.\n", OPERATION);
    printf("%d - Сравнить эффективность двух видов стека.\n", COMPARE);
    printf("%d - Вывести нынешний стек.\n", PRINT);
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
        case ERR_FORMAT:
            printf("Ошибка: Некорретный формат ввода.\n");
            break;
        case ERR_COMMAND:
            printf("Ошибка: Некорректная команда.\n");
            break;
        case ERR_WR_FNAME:
            printf("Ошибка: Неправильное имя файла.\n");
            break;
        case OK:
            break;
        default:
            printf("Неизвестная ошибка.\n");
            break;
    }
}