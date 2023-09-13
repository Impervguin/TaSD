#include <stdio.h>
#include "long_float.h"
#include "calculus.h"
#include "errs.h"
#include "str.h"


#define MAX_FIRST_MANTISS_SIZE 35
#define MAX_SECOND_MANTISS_SIZE 40
#define MAX_RESULT_MANTISS_SIZE 40

// #define MAX_FIRST_STR_SIZE (MAX_FIRST_MANTISS_SIZE + 1 + 1 + 1 + 1 + MAX_FIRST_ORDER_SIZE + 2)
// #define MAX_SECOND_STR_SIZE (MAX_SECOND_MANTISS_SIZE + 1 + 1 + 1 + 1 + MAX_SECOND_ORDER_SIZE + 2)

#define MAX_STR_SIZE (MAX_SECOND_MANTISS_SIZE + 1 + 1 + 1 + 1 + MAX_SECOND_ORDER_SIZE + 2 + 20)

#define MAX_FIRST_ORDER_SIZE 5
#define MAX_SECOND_ORDER_SIZE 5
#define MAX_RESULT_ORDER_SIZE 5


int main (void)
{
    struct long_float flf, slf, rlf;
    char first_float_str[MAX_STR_SIZE], second_float_str[MAX_STR_SIZE];
    int rc = ERR_OK;
    print_intro(MAX_FIRST_MANTISS_SIZE, MAX_FIRST_ORDER_SIZE, MAX_SECOND_MANTISS_SIZE, MAX_SECOND_ORDER_SIZE, MAX_STR_SIZE);
    printf("Введите первое число:\n");
    print_float_ruler(MAX_FIRST_MANTISS_SIZE, MAX_FIRST_ORDER_SIZE);
    rc = str_input(first_float_str, MAX_STR_SIZE);
    if (!rc)
        rc = strtolf(first_float_str, &flf, MAX_FIRST_MANTISS_SIZE, MAX_FIRST_ORDER_SIZE);
    if (!rc)
    {
        printf("Введите второе число:\n");
        print_float_ruler(MAX_SECOND_MANTISS_SIZE, MAX_SECOND_ORDER_SIZE);
        rc = str_input(second_float_str, MAX_STR_SIZE);
    }
        
    if (!rc)
        rc = strtolf(second_float_str, &slf, MAX_SECOND_MANTISS_SIZE, MAX_SECOND_ORDER_SIZE);
    if (!rc)
    {
        multiplication(&flf, &slf, &rlf, MAX_RESULT_MANTISS_SIZE);
        rc = check_lf_order(&rlf, MAX_RESULT_ORDER_SIZE);
    }
    if (!rc)
    {
        printf("Результат: ");
        print_lf(&rlf);
    }
    

    switch (rc)
    {
    case ERR_OK:
        break;
    case ERR_FORMAT:
        printf("Некорректный формат числа.\n");
        break;
    case ERR_MANTISS_EMPTY:
        printf("Нет мантиссы у числа.\n");
        break;
    case ERR_MANTISS_SIZE:
        printf("Слишком длинная мантисса.\n");
        break;
    case ERR_ORDER_SIZE:
        printf("Слишеом длинный порядок.\n");
        break;
    case ERR_IO:
        printf("Ошибка ввода/вывода.\n");
        break;
    case ERR_STR_EMPTY:
        printf("Введена пустая строка.\n");
        break;
    case ERR_STR_RANGE:
        printf("Слишком большая суммарная длина строки\n");
        break;
    default:
        printf("Неизвестная ошибка.\n");
        break;
    }
    return rc;
}

// Умножение на 0
// 48 * 4
// 0.00033 * 3
