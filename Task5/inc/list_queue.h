#ifndef LIST_QUEUE_H__
#define LIST_QUEUE_H__

#include <stdio.h>
#include "request.h"
#include "list.h"

typedef struct list_queue list_queue;
typedef struct qnode qnode;

/// Узел очереди-списка заявок
struct qnode
{
    request_t data; /// Часть узла с данными в виде заявок.
    qnode* next; /// Указатель на следующий узел.
};

/// Очередь-список
struct list_queue
{
    qnode *pin; /// Указатель на входную часть списка.
    qnode *pout; /// Указатель на выходную часть списка.
};

/**
 * @brief Функция, которая инициализирует указатели очереди NULL.
 * 
 * @param q - Указатель на очередь списком.
 */
void list_init(list_queue *q);

/**
 * @brief Функция для создания qnode.
 * 
 * @return qnode* - Указатель на qnode.
 */
qnode *qnode_create(void);

/**
 * @brief Функция для освобождения qnode.
 * 
 * @param qn - Указатель на qnode.
 */
void qnode_free(qnode *qn);

/**
 * @brief Функция для освобождения списка.
 * 
 * @param q - Указатель на список.
 */
void list_free(list_queue *q);

/**
 * @brief Функция для добавления запроса в очередь.
 * 
 * @param q - Указатель на очередь.
 * @param data - Указатель на запрос.
 * @return int - Код возврата.
 */
int list_add(list_queue *q, request_t *data);

/**
 * @brief Функция для удаления запроса в очередь.
 * 
 * @param q - Указатель на очередь.
 * @param data - Указатель на удаленный запрос.
 * @return int - Код возврата.
 */
int list_pop(list_queue *q, request_t *data);

/**
 * @brief Функция для вывода очереди.
 * 
 * @param q - Указатель на очереди.
 */
void list_print(const list_queue *q);

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
 * @param max_cnt - Указатель на максимальное кол-во заявок в очередях за время симуляции.
 * @param mem_head - Указатель на голову списка освобожденных адресов.
 * @param mem_info - Флаг на вывод адресов добаления/удаления элементов.
 * @param verbose - Флаг на вывод данных симуляции
 * @return int - Код возврата.
 */
int list_sim(double t1_create_min, double t1_create_max, double t2_create_min, double t2_create_max, \
    double t1_ex_min, double t1_ex_max, double t2_ex_min, double t2_ex_max, size_t req_cnt, \
    size_t *max_cnt,  node_t **mem_head, int mem_info, int verbose);

/**
 * @brief Функция для вычисления длины очереди.
 * 
 * @param q - Очередь.
 * @return size_t - Размер очереди.
 */
size_t list_length(list_queue *q);

/**
 * @brief Функция для получения среднего времени ожидания в очереди.
 * 
 * @param time - Нынешнее время.
 * @param q - Указатель на очередь.
 * @return double - Среднее время ожидания.
 */
double list_get_average_time(double time, list_queue *q);

/**
 * @brief Функция для получения памяти занимаемой списком с количеством элементов cnt.
 * 
 * @param cnt - Кол-во элементов.
 * @return size_t - Размер списка в байтах.
 */
size_t get_list_memory(size_t cnt);

#endif // LIST_QUEUE_H__
