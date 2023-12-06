#ifndef INT_LIST_H__
#define INT_LIST_H__

typedef struct int_listnode_t int_listnode_t;
typedef struct int_list int_list;

/**
 * @brief Узел списка, хранящий данные в формате ключ-строка - целое число
 * 
 */
struct int_listnode_t
{
    int data; /// Значение - целое
    int_listnode_t *next; /// Указатель на следующий элемент
};

/**
 * @brief Список со данными узла ввиде ключ-строка - целое число
 * 
 */
struct int_list
{
    int_listnode_t *start; /// Указатель на голову списка
    int_listnode_t *end;  /// Указатель на хвост списка
};


int_listnode_t *int_node_create(int val);
void int_node_free(int_listnode_t *node);
void int_list_free(int_list *list);

int int_list_add(int_list *list, int val);
void int_list_add_node(int_list *list, int_listnode_t *node);
int int_list_remove(int_list *list, int val);
int int_list_find(int_listnode_t *list, int val, size_t *cmp_cnt);
size_t int_list_count(int_listnode_t *list);
void print_int_list(int_list *list);

size_t int_list_memory(int_list *list);

#endif // INT_LIST_H__
