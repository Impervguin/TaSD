#ifndef ORGRAPH_H__
#define ORGRAPH_H__

#include <stdio.h>

#define UNMARKED 0
#define VISITED 1

typedef struct ornode ornode_t;
typedef struct orlist orlist_t;
typedef struct orgraph orgraph_t;

/// @brief Структура узла оргграфа.
struct ornode
{
    size_t id; /// Идентификатор узла.
    char *name; /// Имя узла.
    int mark; /// Метка узла
};

/// @brief Список смежностей орграфа.
struct orlist {
    ornode_t *data; /// Информационная часть узла.
    orlist_t *next; /// Указатель на следующий элемент списка.
};

/// @brief Структура оргграфа ввиде списков смежностей.
struct orgraph
{
    orlist_t *nodes; /// Массив списков смежных узлов.
    size_t size; /// Количество узлов в графе.
    size_t max_size; /// Максимальное количество узлов.
};

ornode_t *create_ornode(char *name);
void free_ornode(ornode_t * node);
orlist_t *create_orlist(ornode_t *data);
void free_orlist(orlist_t *list);
int orgraph_init(orgraph_t *graph, size_t max_size);
void orgraph_free(orgraph_t *graph);

void print_graph(orgraph_t *graph);
void unmark_graph(orgraph_t *graph);

int orgraph_add_node(orgraph_t *graph, char *node);
int orgraph_add_connection(orgraph_t *graph, size_t id1, size_t id2);

int orgraph_read(FILE *f, orgraph_t *graph, int verbose);
int orgraph_to_dot(FILE *f, orgraph_t *graph);

int DFS(orgraph_t *graph, size_t start);
int BFS(orgraph_t *graph, size_t start);

#endif // ORGRAPH_H__
