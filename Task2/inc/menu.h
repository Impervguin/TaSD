#ifndef MENU_H__
#define MENU_H__

#include "country_arr.h"

#define MAX_INPUT_SIZE (100 + 1)
#define ERR_INPUT_IO -2
#define ERR_INPUT_VAL -1

/**
 * @brief Функция для вывода начала интерфейса программы.
 * 
 */
void print_intro();

/**
 * @brief Функция для вывода меню программы.
 * 
 */
void print_menu();

/**
 * @brief Функция для ввода выбранного действия.
 * 
 * @return int - Выбранное действие.
 */
int select_action();

/**
 * @brief Функция для ввода строки из файла.
 * 
 * @param f - Файл.
 * @param str - Строка.
 * @param max_size - Максимальный размер строки.
 * @return int - Код возврата.
 */
int str_read(FILE *f, char *str, size_t max_size);

/**
 * @brief Функция для вывода сообщения ошибки.
 * 
 * @param rc - Код ошибки
 */
void print_error(int rc);

/**
 * @brief Функция для ввода целого числа.
 * 
 * @param res - Полученное число. 
 * @param mes - Сообщение при вводе.
 * @return int - Код возврата.
 */
int int_input(int *res, const char *mes);

/**
 * @brief Функция для вывода информации о сортировках.
 * 
 * @param qsi_t - Время быстрой сортировки с индексами.
 * @param qsa_t - Время быстрой сортировки без индексов. 
 * @param msi_t - Время обычной сортировки с индексами.
 * @param msa_t - Время обычной сортировки без индексов.
 * @param isize - Память хранения массива с индексами.
 * @param asize - Память хранения массива без индексов.
 */
void print_sort_tables(long qsi_t, long qsa_t, long msi_t, long msa_t, size_t isize, size_t asize);
#endif