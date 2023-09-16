#include "long_float.h"
#include "errs.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

void make_lf_null(struct long_float *lf)
{
    for (size_t i = 0; i < MAX_MANTISS_SIZE; i++)
        lf->mantiss[i] = 0;
    lf->mant_sign = 0;
    lf->order = 0;
    lf->size = 0;
}

int strtolf(const char *str, struct long_float *lf, size_t max_mant_size, size_t max_order_size)
{
    size_t mant_size = 0, order_size = 0; /// Размеры  мантиссы и порядка
    const char *mant_p = str, *mant_e = NULL, *order_p = NULL, *order_e = NULL; /// Указатели на начало мантиссы, конец мантиссы, начало порядка, конец порядка
    char order_sign = 1; ///  Знак порядка
    char sign = 1; /// Знак числа
    int was_zero = 0; /// Был ли ноль до цифр
    size_t now_zeros = 0; /// Хранит количество нулей между цифрами(для того, чтобы в последствии откинуть, еслиэто не значащие нули)
    size_t zeros_before_point = 0; /// Хранит количество нулей до точки, но после последней значащей цифры.
    /// Нужна для увеличения порядка числа
    size_t zeros_after_point = 0; /// Количество нулей после точки, но до первой цифры(после точки)
    int was_point = 0; /// Была ли точка в число
    int was_point_in_prep = 0; /// Была ли точка при отбрасывании первых не значащих нулей

    /// Чтение знака
    if ((*mant_p) == '-' || (*mant_p) == '+')
    {
        if ((*mant_p) == '-')
            sign = 0;
        mant_p++;
    }

    /// Чтение незначащих нулей
    while (*mant_p == '0' || *mant_p == '.')
    {
        if (*mant_p == '0')
        {
            mant_p++;
            was_zero = 1;
            if (was_point)
                zeros_after_point++;
        }
        else
        {
            mant_p++;
            was_point = 1;
            was_point_in_prep = 1;
        }
    }
        
    
    
    /// Подсчет размера мантиссы и проверка её формата
    const char *now = mant_p;
    for (; *now != '\0' && *now != 'E'; now++)
    {
        if (*now > '0' && *now <= '9')
            {
                mant_size += 1 + now_zeros;
                now_zeros = 0;
                mant_e = now;
                zeros_before_point = 0;
            }
        else if (*now == '0')
        {
            now_zeros++;
            if (!was_point)
                zeros_before_point++;
            if (was_point && mant_size == 0)
                zeros_after_point++;
        }
            
        else if (*now == '.' && !was_point)
            was_point = 1;
        else
            return ERR_FORMAT;
    }

    /// Подсчет размера порядка и проверка его порядка
    if (*now == 'E')
    {
        int was_null_order = 0;
        now++;
        if ((*now) == '-' || (*now) == '+')
        {
        if ((*now) == '-')
            order_sign = 0;
        now++;
        }
        
        while (*now == '0')
        {
            now++;
            was_null_order = 1;
        }
            

        order_p = order_e = now;
        for (; *now != '\0'; now++)
        {
            if (*now >= '0' && *now <= '9')
            {
                order_size++;
                order_e = now;
            }
            else
                return ERR_FORMAT;
        }
        if (order_size == 0 && !was_null_order)
            return ERR_FORMAT;
    }

    /// Проверки размеров
    if (mant_size == 0 && !zeros_after_point && !was_zero)
        return ERR_MANTISS_EMPTY;
    if (mant_size > max_mant_size)
        return ERR_MANTISS_SIZE;
    if (order_size > max_order_size)    
        return ERR_ORDER_SIZE;
    
    /// Зануляем выходное длинное число
    make_lf_null(lf);
    
    /// Чтение мантиссы
    size_t now_mant = mant_size - 1; /// Индекс нынешней цифры в длинном числе
    size_t order_add = 0; /// Добавка к порядку из-за нормализации числа(учитываются только цифры между первой и последней ненуловой)
    if (!was_point_in_prep)
        was_point = 0;
    
    for (const char *now = mant_p; now <= mant_e; now++)
    {
        if (*now != '.')
        {
            if (!was_point)
                order_add++;
            lf->mantiss[now_mant] = (int) ((*now) - '0');
            now_mant--;
        }
        else
            was_point = 1;
    }

    /// Чтение порядка
    if (order_size != 0)
    {
        int tmp = 0;
        for (const char *now = order_p; now <= order_e; now++)
        {
            tmp *= 10;
            tmp += (int) ((*now) - '0');
        }
        if (!order_sign)
            tmp = -tmp;
        lf->order = tmp;
    }

    lf->order += order_add + zeros_before_point - zeros_after_point; /// Порядок
    lf->mant_sign = sign; /// знак
    lf->size = mant_size; /// Размер

    return ERR_OK;
}

int check_lf_order(const struct long_float *lf, size_t order_size)
{
    int tmp = lf->order;
    size_t len = 0;
    while (tmp != 0)
    {
        tmp /= 10;
        ++len;
    }

    if (len > order_size)
        return ERR_RES_ORDER_SIZE;
    return ERR_OK;
}


// static size_t count_int_len(int a)
// {
//     size_t len = 0;
//     while (a != 0)
//     {
//         len++;
//         a /= 10;
//     }
//     return len;
    
// }
void print_lf(const struct long_float *lf)
{
    if (lf->mant_sign == 1)
        printf("+");
    else
        printf("-");

    printf("0.");
    for (int i = lf->size - 1; i >= 0; i--)
    {
        printf("%d", lf->mantiss[i]);
    }
    if (lf->size == 0)
        printf("0");
    printf("E");
    if (lf->order >= 0)
        printf("+");
    printf("%d", lf->order);
    printf("\n");
}
