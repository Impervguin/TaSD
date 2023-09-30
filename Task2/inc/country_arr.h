#ifndef COUNTRY_ARR_H__
#define COUNTRY_ARR_H__

#define MAX_ARRAY_SIZE 10000

#include "country.h"
#include <stddef.h>
#include <stdio.h>

/**
 * @brief Структура для храниния массива стран с индексами.
 * size - Количество элементов.
 * arr - Массив стран.
 * indexes - Массив индексов.
 */
struct country_ind_arr_t
{
    size_t size;
    struct country_t arr[MAX_ARRAY_SIZE];
    size_t indexes[MAX_ARRAY_SIZE];
};

/**
 * @brief Структура для храниния массива стран.
 * size - Количество элементов.
 * arr - Массив стран.
 */
struct country_arr_t
{
    size_t size;
    struct country_t arr[MAX_ARRAY_SIZE];
};

/**
 * @brief Функция для чтения массива стран из файла.
 * 
 * @param [in] f - Файл.
 * @param [out] arr - Указатель на массив стран.
 * @return int - Код возврата.
 */
int read_country_arr(FILE *f, struct country_arr_t *arr);

/**
 * @brief Функция для чтения массива стран из файла.
 * 
 * @param [in] f - Файл.
 * @param [out] arr - Указатель на массив стран с массиво индексов.
 * @return int - Код возврата.
 */
int read_country_ind_arr(FILE *f, struct country_ind_arr_t *arr);

/**
 * @brief Функция для удаления страны из массива стран.
 * 
 * @param [in/out] arr - Указатель на массив стран.
 * @param [in] ind - Индекс удаляемого элемента
 * @return int - Код возврата
 */
int delete_country_arr(struct country_arr_t *arr, size_t ind);

/**
 * @brief Функция для удаления страны из массива стран с индексами.
 * 
 * @param [in/out] arr - Указатель на массив стран с индексами.
 * @param [in] ind - Индекс удаляемого элемента
 * @return int - Код возврата
 */
int delete_country_ind_arr(struct country_ind_arr_t *arr, size_t ind);

/**
 * @brief Функция для добавления страны в конец массива стран. 
 * 
 * @param [in/out] arr - Указатель на массив стран.
 * @param [in] country - Указатель на страну.
 * @return int - Код возврата. 
 */
int add_country_arr(struct country_arr_t *arr, struct country_t *country);

/**
 * @brief Функция для добавления страны в конец массива стран с индексами. 
 * 
 * @param [in/out] arr - Указатель на массив стран с индексами.
 * @param [in] country - Указатель на страну.
 * @return int - Код возврата. 
 */
int add_country_ind_arr(struct country_ind_arr_t *arr, struct country_t *country);


/**
 * @brief Функция для записи массива стран в файл.
 * 
 * @param [out] f - Файл.
 * @param [in] arr - Массив стран.
 * @return int - Код возврата.
 */
int write_country_arr(FILE *f, struct country_arr_t *arr);

/**
 * @brief Функция для записи массива стран с индексами в файл.
 * 
 * @param [out] f - Файл.
 * @param [in] arr - Массив стран.
 * @return int - Код возврата.
 */
int write_country_ind_arr(FILE *f, struct country_ind_arr_t *arr);

/**
 * @brief Функция для поиска в стран на выбранном континенте с нужным спортом и ценой ниже указанной.
 * 
 * @param [in] arr - Массив стран.
 * @param [in] continent - Искомый континент.
 * @param [in] price - Максимальная цена.
 * @param [in] sp - Искомый спорт.
 * @param [out] res - Массив стран с найденными странами.
 * @return int - Код возврата.
 */
int find_country_arr(const struct country_arr_t *arr, const char *continent, int price, sport_t sp, struct country_arr_t *res);

/**
 * @brief Функция для поиска в стран на выбранном континенте с нужным спортом и ценой ниже указанной.
 * 
 * @param [in] arr - Массив стран с индексами.
 * @param [in] continent - Искомый континент.
 * @param [in] price - Максимальная цена.
 * @param [in] sp - Искомый спорт.
 * @param [out] res - Массив стран с найденными странами.
 * @return int - Код возврата.
 */
int find_country_ind_arr(const struct country_ind_arr_t *arr, const char *continent, int price, sport_t sp, struct country_ind_arr_t *res);

/**
 * @brief Функция для сортировки массива стран пузырьком(или выбором).
 * 
 * @param [in/out] arr - Массив стран.
 */
void sort_country_arr(struct country_arr_t *arr);
/**
 * @brief Функция для сортировки массива стран c индексами пузырьком(или выбором).
 * 
 * @param [in/out] arr - Массив стран с индексами.
 */
void sort_country_ind_arr(struct country_ind_arr_t *arr);

/**
 * @brief Сортировка хоара для массива стран.
 * 
 * @param [in/out] arr - Массив стран.
 * @param [in] low - Первый элемент массива.
 * @param [in] high - Последний элемент массива.
 */
void qsort_country_arr(struct country_arr_t *arr, int low, int high);

/**
 * @brief Сортировка хоара для массива стран с индексами.
 * 
 * @param [in/out] arr - Массив стран с индексами.
 * @param [in] low - Первый элемент массива.
 * @param [in] high - Последний элемент массива.
 */
void qsort_country_ind_arr(struct country_ind_arr_t *arr, int low, int high);

/**
 * @brief Функция для перевода массива стран с индексами в массив стран.
 * 
 * @param [in] ind_arr - Массив стран с индексами.
 * @param [out] arr - Массив стран
 */
void indtoarr(const struct country_ind_arr_t *ind_arr, struct country_arr_t *arr);

/**
 * @brief Функция для перевода массива стран в массив стран с индексами.
 * 
 * @param [in] arr - Массив стран
 * @param [out] ind_arr - Массив стран с индексами.
 */
void arrtoind(const struct country_arr_t *arr, struct country_ind_arr_t *ind_arr);

/**
 * @brief Функция для вывода на экран массива стран с индексами.
 * 
 * @param [in] ind_arr - Массив стран с индексами.
 */
void print_country_ind_arr(const struct country_ind_arr_t *ind_arr);

/**
 * @brief Функция для вывода на экран массива стран.
 * 
 * @param [in] ind_arr - Массив стран.
 */
void print_country_arr(const struct country_arr_t *arr);

#endif