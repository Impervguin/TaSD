#ifndef COUNTRY_H__
#define COUNTRY_H__

#include <stddef.h>
#include <stdio.h>

#define NAME_SIZE (15 + 1)
#define CAPITAL_SIZE (15 + 1)
#define LAND_SIZE (18 + 1)

typedef enum  {EXCURSION, SPORT, BEACH} vacation_t;
typedef enum  {WINTER, SPRING, SUMMER, AUTUMN} season_t;
typedef enum  {NATURE, HISTORY, CULTURE} obj_t;
typedef enum  {SKIING, SURFING, HIKING, ALLOY} sport_t;

struct excursion_t
{
    size_t obj_cnt;
    obj_t type;
};

struct beach_t
{
    season_t season;
    double water_temp;
    double air_temp; 
};

/**
 * @brief Структура страны.
 * name - Название страны.
 * capital - Столица страны.
 * land - Континент.
 * visa - Необходимость визы в стране.
 * ftime - Время полета до страны.
 * price - Цена путешествия в страну.
 * vacation_type - Тип путешествия.
 * vacation - Детали путешествия.
 */
struct country_t
{
    char name[NAME_SIZE + 1];
    char capital[CAPITAL_SIZE + 1];
    char land[CAPITAL_SIZE + 1];
    int visa;
    int ftime;
    int price;
    vacation_t vacation_type;
    union
    {
        struct excursion_t excursion;
        struct beach_t beach;
        sport_t sport;
    } vacation;
};

/**
 * @brief Функция для чтения страны из файла.
 * 
 * @param f - Файл.
 * @param country - Указатель на страну.
 * @param verbose - Флаг подробного вывода.
 * @return int Код возврата.
 */
int read_country_file(FILE *f, struct country_t *country, int verbose);

/**
 * @brief Функция для вывода страны в файл.
 * 
 * @param f - Файл
 * @param country - Указатель на страну.
 * @param verbose - Флаг подробного вывода.
 * @return int - Код возврата.
 */
int print_country_file(FILE *f, const struct country_t *country, int verbose);

/**
 * @brief Функция для сравнения двух стран по цене путешествия.
 * 
 * @param pc1 - Указатель на первую страну.
 * @param pc2 - Указатель на вторую страну.
 * @return int >0 - Если вторая страна дороже первой, 0 если равны, иначе <0.
 */
int cmp_country(const void *pc1, const void *pc2);
#endif