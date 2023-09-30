#include "country.h"
#include "errs.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>


static int check_buf(const char *buf)
{
    if (buf[0] == '\n' || buf[0] == '\0')
        return ERR_OK;
    return ERR_IO;
}

static int str_read(FILE *f, char *str, size_t max_size)
{
    if (fgets(str, max_size, f) == NULL)
        return ERR_IO;
    size_t len = strlen(str);
    if (len && str[len - 1] != '\n')
        return ERR_STR_RANGE;
    str[--len] = '\0';

    if (!len)
        return ERR_STR_EMPTY;
    return ERR_OK;

}

static int read_excursion(FILE *f, struct excursion_t *exc, int verbose)
{
    char tmpbuf[2];
    int tmp;
    if (verbose)
        printf("Введите количество Экскурсионных мест: ");
    if (fscanf(f, "%zu", &exc->obj_cnt) != 1)
        return ERR_IO;
    
    fgets(tmpbuf, 2, f);
    if (check_buf(tmpbuf))
        return ERR_IO;

    if (verbose)
        printf("Введите тип экскурсий(%d - Исторические, %d - Культурные, %d - Природные)", HISTORY, CULTURE, NATURE);
    if (fscanf(f, "%d", &tmp) != 1)
        return ERR_IO;
    
    if (tmp < 0 || tmp > 2)
        return ERR_IO;
    exc->type = tmp;
    fgets(tmpbuf, 2, f);
    if (check_buf(tmpbuf))
        return ERR_IO;
    
    if (exc->type != HISTORY && exc->type != CULTURE && exc->type != NATURE)
        return ERR_RANGE;
    return ERR_OK;
}

static int read_beach(FILE *f, struct beach_t *bc, int verbose)
{
    char tmpbuf[2];
    int tmp;
    if (verbose)
        printf("Введите лучшее время года(%d - Осень, %d - Весна, %d - Зима, %d - Лето)", AUTUMN, SPRING, WINTER, SUMMER);
    if (fscanf(f, "%d", &tmp) != 1)
        return ERR_IO;
    if (tmp < 0 || tmp > 3)
        return ERR_IO;
    bc->season = tmp;
    
    if (bc->season != AUTUMN && bc->season != SPRING && bc->season != SUMMER && bc->season != WINTER)
        return ERR_RANGE;
    
    fgets(tmpbuf, 2, f);
    if (check_buf(tmpbuf))
        return ERR_IO;
    
    if (verbose)
        printf("Введите температуру воды(Вещественное число): ");

    if (fscanf(f, "%lf", &bc->water_temp) != 1)
        return ERR_IO;
    
    fgets(tmpbuf, 2, f);
    if (check_buf(tmpbuf))
        return ERR_IO;

    if (verbose)
        printf("Введите температуру воздуха(Вещественное число): ");
    if (fscanf(f, "%lf", &bc->air_temp) != 1)
        return ERR_IO;
    
    fgets(tmpbuf, 2, f);
    if (check_buf(tmpbuf))
        return ERR_IO;
    return ERR_OK;
}

static int read_sport(FILE *f, sport_t *sp, int verbose)
{
    char tmpbuf[2];
    int tmp;
    if (verbose)
        printf("Введите вид спорта(%d - Лыжи, %d - Сёрфинг, %d - Сплав, %d - Восхождение): ", SKIING, SURFING, ALLOY, HIKING);
    if (fscanf(f, "%d", &tmp) != 1)
        return ERR_IO;
    if (tmp < 0 || tmp > 3)
        return ERR_IO;
    *sp = tmp;
    

    if (*sp != SKIING && *sp != SURFING && *sp != ALLOY && *sp != HIKING)
        return ERR_RANGE;
    
    fgets(tmpbuf, 2, f);
    if (check_buf(tmpbuf))
        return ERR_IO;
    return ERR_OK;
}

int read_country_file(FILE *f, struct country_t *country, int verbose)
{
    assert(f != NULL);
    int rc = ERR_OK;
    char tmpbuf[2];
    if (verbose)
        printf("Введите название страны(Максимум %d символов): ", NAME_SIZE - 1);
    rc = str_read(f, country->name, NAME_SIZE);
    
    if (!rc)
    {
        if (verbose)
            printf("Введите название столицы(Максимум %d символов): ", CAPITAL_SIZE - 1);
        rc = str_read(f, country->capital, CAPITAL_SIZE);
    }
    if (!rc)
    {
        if (verbose)
            printf("Введите название материка(Максимум %d символов): ", LAND_SIZE - 1);
        rc = str_read(f, country->land, LAND_SIZE);
    }
    if (!rc)
    {
        if (verbose)
            printf("Нужна ли в стране виза(1 - да, 0 - нет): ");
        if (fscanf(f, "%d", &country->visa) != 1)
            rc = ERR_IO;
        
        if (!rc && (country->visa != 0 && country->visa != 1))
            rc = ERR_RANGE;
    }
    
    if (!rc)
    {
        fgets(tmpbuf, 2, f);
        rc = check_buf(tmpbuf);
    }
        
    if (!rc)
    {
        if (verbose)
            printf("Введите время полета(Целое число, в минутах): ");
        if (fscanf(f, "%d", &country->ftime) != 1)
            rc = ERR_IO;
        
        if (!rc && country->ftime <= 0)
            rc = ERR_RANGE;
    }

    if (!rc)
    {
        fgets(tmpbuf, 2, f);
        rc = check_buf(tmpbuf);
    }

    if (!rc)
    {
        if (verbose)
            printf("Введите цену путешествия(Целое число): ");
        if (fscanf(f, "%d", &country->price) != 1)
            rc = ERR_IO;
        
        if (!rc && (country->price <= 0))
            rc = ERR_RANGE;
    }

    if (!rc)
    {
        fgets(tmpbuf, 2, f);
        rc = check_buf(tmpbuf);
    }

    if (!rc)
    {
        int tmp;
        if (verbose)
            printf("Введите тип путешествия(%d - Экскурсионный, %d - Пляжный, %d - Спортивный): ", EXCURSION, BEACH, SPORT);
        if (fscanf(f, "%d", &tmp) != 1)
            rc = ERR_IO;
        if (tmp < 0 || tmp > 2)
            rc = ERR_IO;
        country->vacation_type = tmp;
    }
    
    if (!rc)
    {
        if (country->vacation_type == EXCURSION)
            rc = read_excursion(f, &(country->vacation.excursion), verbose);
        else if (country->vacation_type == SPORT)
            rc = read_sport(f, &(country->vacation.sport), verbose);
        else if (country->vacation_type == BEACH)
            rc = read_beach(f, &(country->vacation.beach), verbose);
    }
    return rc;
}

static void print_excursion(FILE *f, const struct excursion_t *exc)
{
    fprintf(f, "Количество объектов: %zu\n", exc->obj_cnt);
    fprintf(f, "Тип объектов: ");
    if (exc->type == NATURE)
        fprintf(f, "Природный\n");
    else if (exc->type == HISTORY)
        fprintf(f, "Исторический\n");
    else if (exc->type == CULTURE)
        fprintf(f, "Культурный\n");
}

static void print_beach(FILE *f, const struct beach_t *bc)
{
    fprintf(f, "Лучший сезон: ");
    if (bc->season == WINTER)
        fprintf(f, "Зима\n");
    else if (bc->season == SUMMER)
        fprintf(f, "Лето\n");
    else if (bc->season == SPRING)
        fprintf(f, "Весна\n");
    else if (bc->season == AUTUMN)
        fprintf(f, "Осень\n");
    fprintf(f, "Температура воды: %lf\n", bc->water_temp);
    fprintf(f, "Температура воздуха: %lf\n", bc->air_temp);
}

static void print_sport(FILE *f, sport_t sp)
{
    fprintf(f, "Тип спорта: ");
    if (sp == SKIING)
        fprintf(f, "Лыжи\n");
    else if (sp == HIKING)
        fprintf(f, "Восхождение\n");
    else if (sp == ALLOY)
        fprintf(f, "Сплав\n");
    else if (sp == SURFING)
        fprintf(f, "Сёрфинг\n");
}

static void print_vacation(FILE *f, vacation_t vt)
{
    fprintf(f, "Тип путешествия: ");
    if (vt == EXCURSION)
        fprintf(f, "Экскурсионный\n");
    else if (vt == BEACH)
        fprintf(f, "Пляжный\n");
    else if (vt == SPORT)
        fprintf(f, "Спортивный\n");
}

int print_country_file(FILE *f, const struct country_t *country, int verbose)
{
    if (verbose)
    {
        fprintf(f, "Название: %s\n", country->name);
        fprintf(f, "Столица: %s\n", country->capital);
        fprintf(f, "Материк: %s\n", country->land);
        fprintf(f, "Виза: %s\n", country->visa == 1 ? "Да" : "Нет");
        fprintf(f, "Время полета: %d\n", country->ftime);
        fprintf(f, "Цена путешенсвия: %d\n", country->price);
        print_vacation(f, country->vacation_type);
        if (country->vacation_type == EXCURSION)
        {
            print_excursion(f, &(country->vacation.excursion));
        }
        else if (country->vacation_type == BEACH)
        {
            print_beach(f, &(country->vacation.beach));
        }
        else if (country->vacation_type == SPORT)
        {
            print_sport(f, country->vacation.sport);
        }
    }
    else
    {
        fprintf(f, "%s\n", country->name);
        fprintf(f, "%s\n", country->capital);
        fprintf(f, "%s\n", country->land);
        fprintf(f, "%d\n", country->visa);
        fprintf(f, "%d\n", country->ftime);
        fprintf(f, "%d\n", country->price);
        fprintf(f, "%d\n", country->vacation_type);
        if (country->vacation_type == EXCURSION)
        {
            fprintf(f, "%zu\n", country->vacation.excursion.obj_cnt);
            fprintf(f, "%d\n", country->vacation.excursion.type);
        }
        else if (country->vacation_type == BEACH)
        {
            fprintf(f, "%d\n", country->vacation.beach.season);
            fprintf(f, "%lf\n", country->vacation.beach.water_temp);
            fprintf(f, "%lf\n", country->vacation.beach.air_temp);
        }
        else if (country->vacation_type == SPORT)
        {
            fprintf(f, "%d\n", country->vacation.sport);
        }
    }
    return ERR_OK;
}

int cmp_country(const void *pc1, const void *pc2)
{
    const struct country_t *p1 = pc1, *p2 = pc2;
    return p2->price - p1->price;
}
