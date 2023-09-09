#include "long_float.h"
#include "errs.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

int strtolf(const char *str, struct long_float *lf, size_t max_mant_size, size_t max_order_size)
{
    size_t before_point = 0;
    size_t nums = 0;
    size_t order_nums = 0;
    int was_point = 0;
    int sign = 1;

    size_t i = 0;
    int rc = ERR_OK;

    // Проверяем мантиссу на правильный формат и считаем ее длину в цифрах
    for (; str[i] != 'E' && str[i] != '\0' && !rc; i++)
    {
        if (str[i] <= '9' && str[i] >= '0')
        {
            nums++;
            if (!was_point)
                before_point++;
        } else if (str[i] == '.' && !was_point)
            was_point = 1;
        else if (str[i] == '+' && (!nums && !was_point))
            sign = 1;
        else if (str[i] == '-' && (!nums && !was_point))
            sign = 0;
        else
            rc = ERR_FORMAT;  
    }
    
    // Проверяем порядок на правильность ввода
    if (str[i] != '\0' && !rc)
    {
        for (i++; str[i] != '\0' && !rc; i++)
        {
            if (str[i] >= '0' && str[i] <= '9')
                order_nums++;
            else if (str[i] == '+' && !order_nums);
            else if (str[i] == '-' && !order_nums);
            else
                rc = ERR_FORMAT;
        }
    }

    // Проверяем размеры мантиссы и порядка
    if (!rc)
    {
        if (nums > max_mant_size)
            rc = ERR_MANTISS_SIZE;
        else if (nums == 0)
            rc = ERR_MANTISS_EMPTY;
        else if (order_nums > max_order_size)
            rc = ERR_ORDER_SIZE;
    }

    // Считываем число в структуру
    if (!rc)
    {
        // Обнуляем значения в структуре
        for (size_t j = 0; j < ARR_MANTISS_SIZE; j++)
            lf->mantiss[j] = 0;
        lf->order = 0;

        lf->mant_sign = sign;

        // Переводим мантиссу
        int tmp = 0;
        for (i = 0; str[i] != 'E' && str[i] != '\0'; i++)
        {
            if (str[i] != '.')
            {
                if (nums % CELL_BASE == 0)
                {
                    lf->mantiss[nums / CELL_BASE] = tmp;
                    tmp = 0;
                }
                tmp *= 10;
                tmp += (int) str[i] - '0';
                nums--;
            }
        }
        lf->mantiss[nums / CELL_BASE] = tmp;
        
        // Переводим порядок
        if (str[i] == 'E')
        {
            int modif = 1;
            int tmp = 0;   
            if (str[i + 1] == '+' || str[i + 1] == '-')
            {
                i++
                if (str[i] == '-')
                    modif = -1;
            }

            for (i++; str[i] != '\0' && !rc; i++)
            {
                tmp *= 10;
                tmp += (int) str[i] - '0';
            }
            tmp *= modif;
            tmp += before_point;
            lf->order = tmp; 
        }
    }

    return rc;
}

int check_lf_order(const struct long_float *lf, size_t order_size)
{
    int tmp = lf->order;
    size_t len = 0;
    while (tmp != 0)
    {
        tmp %= 10;
        ++len;
    }

    if (len > order_size)
        return ERR_ORDER_SIZE;
    return ERR_OK;
}


static size_t count_int_len(int a)
{
    size_t len = 0;
    while (a != 0)
    {
        len++;
    }
    return len;
    
}
void print_lf(const struct long_float *lf)
{
    size_t cells = 0;
    for (size_t i = 0; i < ARR_MANTISS_SIZE; i++)
        if (lf->mantiss[i] != 0)
            cells = i + 1;
    if (lf->mant_sign == 0)
        printf("-");
    else
        printf("+");
    printf("0.");

    while (cells > 0)
    {
        char tmp[CELL_BASE + 1];
        tmp[CELL_BASE - 1] = '\0';
        int num = lf->mantiss[cells - 1];
        for (size_t j = CELL_BASE; j > 0; j--)
        {
            if (num != 0)
            {
                tmp[j] = ((char) (num % 10)) + '0';
                num /= 10; 
            }
            else 
                tmp[j] = '0';
        }
        printf("%s", tmp);
        cells--;
    }
    printf("E%d", lf->order);
}

