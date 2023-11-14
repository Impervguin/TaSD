#ifndef STATIC_QUEUE_H__
#define STATIC_QUEUE_H__

#include <stdio.h>
#include "request.h"

#define STATIC_QUEUE_SIZE 100000

typedef struct static_queue static_queue;

/// Очередь заявок в виде статического массива.
struct static_queue
{
    request_t arr[STATIC_QUEUE_SIZE]; /// Статический массив заявок.
    request_t *end; /// Указатель на физический конец очереди.
    request_t *pin; /// Указатель на входную часть массива.
    request_t *pout; /// Указатель на выходную часть массива.
    int full; /// Флаг заполненности очереди.
};

/**
 * @brief Функция для зануления статической очереди.
 * 
 * @param q - Указатель на очередь.
 */
void static_init(static_queue *q);

/**
 * @brief Функция для добавления в статическую очередь.
 * 
 * @param q - Указатель на очередь.
 * @param req - Указатель на запрос.
 * @return int - Код возврата.
 */
int static_add(static_queue *q, request_t *req);

/**
 * @brief Функция для удаления из статической очереди.
 * 
 * @param q - Указатель на очередь.
 * @param req - Указатель на удаленный запрос.
 * @return int - Код возврата.
 */
int static_pop(static_queue *q, request_t *req);

/**
 * @brief Функция для вывода статической очереди.
 * 
 * @param q - Указатель на очередь.
 */
void static_print(const static_queue *q);

/**
 * @brief Функция для проведения симуляции с очередью запросов.
 * 
 * @param t1_create_min - Нижняя граница времени создания заявки типа 1.
 * @param t1_create_max - Верхняя граница времени создания заявки типа 1. 
 * @param t2_create_min - Нижняя граница времени создания заявки типа 2. 
 * @param t2_create_max - Верхняя граница времени создания заявки типа 2.
 * @param t1_ex_min - Нижняя граница времени выполнения заявки типа 1.
 * @param t1_ex_max - Верхняя граница времени выполнения заявки типа 1.
 * @param t2_ex_min - Нижняя граница времени выполнения заявки типа 2.
 * @param t2_ex_max - Верхняя граница времени выполнения заявки типа 2.
 * @param req_cnt - Необходимое количество заявок первого типа для завершения симуляции.
 * @param verbose - Флаг на вывод данных симуляции
 * @return int - Код возврата.
 */
int static_sim(double t1_create_min, double t1_create_max, double t2_create_min, double t2_create_max, \
    double t1_ex_min, double t1_ex_max, double t2_ex_min, double t2_ex_max, size_t req_cnt, size_t *max_cnt, int verbose);

/**
 * @brief Функция для получения длины статической очереди.
 * 
 * @param q - Указатель на очередь.
 * @return size_t - Размер очереди.
 */
size_t static_length(static_queue *q);

/**
 * @brief Функция для получения среднего времени ожидания в очереди.
 * 
 * @param time - Нынешнее время.
 * @param q - Указатель на очередь.
 * @return double - Среднее время ожидания.
 */
double get_average_time(double time, static_queue *q);

/**
 * @brief Функция для получения памяти занимаемой статической очередью с количеством элементов cnt.
 * 
 * @param cnt - Кол-во элементов.
 * @return size_t - Размер списка в байтах.
 */
size_t get_static_memory(size_t cnt);

#endif // STATIC_QUEUE_H__
