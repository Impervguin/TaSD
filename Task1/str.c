#include "str.h"

#include <stdio.h>
#include "errs.h"
#include <string.h>


int str_input(char *str, size_t max_size)
{
    if (fgets(str, max_size, stdin) == NULL)
        return ERR_IO;

    size_t len = strlen(str);
    if (!len && str[len - 1] != '\n')
        return ERR_STR_RANGE;

    str[--len] = '\0';

    if (!len)
        return ERR_STR_EMPTY;
    
    return ERR_OK;
}

void print_float_ruler(size_t max_mantiss_size, size_t max_order_size)
{
    printf("+");
    for (size_t i = 0; i < max_mantiss_size; i++)
    {
        if ((i + 1) % 10 == 0)
            printf("%zu", (i / 10) + 1);
        else
            printf(".");
    }
    printf("E+");
    for (size_t i = 0; i < max_order_size; i++)
        printf(".");
    printf("\n");
}

void print_intro(size_t first_mant, size_t first_order, size_t sec_mant, size_t sec_order, size_t str_size)
{
    printf("Данная программа способна перемножать два действительных числа.\n");
    printf("Каждое число должно иметь формат: [+-]?[0-9]*[.]?[0-9]*E[+-][0-9]*\n");
    printf("то есть, знак перед мантиссой и порядком не обязателен, точка необязательно, после точки или до может не быть чисел,\nно хотя бы в одном месте (до или после точки) число должна быть. Если ввели E, то должна быть хотя бы одна цифра после.\n");
    printf("Размер мантиссы первого числа: %zu, порядка: %zu\n", first_mant, first_order);
    printf("Размер мантиссы второго числа: %zu, порядка: %zu\n",sec_mant, sec_order);
    printf("Максимальная длина вводимой строки: %zu символ\n", str_size);
}
