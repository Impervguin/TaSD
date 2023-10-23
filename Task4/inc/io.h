#ifndef IO_H__
#define IO_H__

typedef enum {READ_STACK = 1, ADD = 2, POP = 3, OPERATION = 4, COMPARE = 5, PRINT = 6, EXIT = 0} command_t;
#define MAX_COMMAND_NUM 6

/**
 * @brief Функция для чтения имени и открытия файла.
 * 
 * @param [out] f - Файл.
 * @return int Код возврата.
 */
int read_file(FILE **f);

/**
 * @brief Функция для вывода заголовка меню.
 * 
 */
void print_intro();

/**
 * @brief Функция для вывода меню.
 * 
 */
void print_menu();

/**
 * @brief Функция для ввода целого числа в строке.
 * 
 * @param [out] res - Найденное число.
 * @param [in] mes - Сообщение при вводе.
 * @return int - Код возврата.
 */
int int_input(int *res, char *mes);

/**
 * @brief Функция для вывода сообщения об ошибке.
 * 
 * @param rc - Код ошибки.
 */
void print_error(int rc);

#endif