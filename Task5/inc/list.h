#ifndef LIST_H__
#define LIST_H__

typedef struct node_t node_t;

/// Узел обычного списка.
struct node_t
{
    void *data; /// Указатель на данные узла.
    node_t *next; /// Указатель на следующий узел.
};

/**
 * @brief Создание узла списка.
 * 
 * @return node_t* - Указатель на узел списка.
 */
node_t *node_create(void);

/**
 * @brief Функция для освобождения узла.
 * 
 * @param n - Указатель на узел.
 */
void node_free(node_t *n);

/**
 * @brief Функция для освобождения списка.
 * 
 * @param head - Указатель на голову списка.
 */
void rlist_free(node_t **head);

/**
 * @brief Функция для добавления элемента в конец списка.
 * 
 * @param head - Указатель на голову списка.
 * @param data - Указатель на данные.
 * @return int - Код возврата.
 */
int rlist_add(node_t **head, void *data);

/**
 * @brief Функция для удаления первого элемента из списка.
 * 
 * @param head - Указатель на голову.
 * @param data - Указатель на освобожденные данные.
 * @return int - Код возврата.
 */
int rlist_pop(node_t **head, void **data);


#endif // LIST_H__
