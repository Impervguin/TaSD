#ifndef INT_BTREE_H__
#define INT_BTREE_H__

typedef struct int_node_t int_node_t;

#define FOUND 0
#define NOT_FOUND 1

/// @brief Структура узла бинарного дерева поиска целых
/// Также используется для АВЛ
struct int_node_t
{
    int_node_t *left; /// Указатель на левого потомка
    int_node_t *right; /// Указатель на правого потомка
    int data; /// Число узла
    int height; /// Высота дерева
};

int_node_t *create_int_node(int data);
void free_int_node(int_node_t *node);
void free_inttree(int_node_t **root);
int_node_t *inttree_join(int_node_t *p, int_node_t *q);
int_node_t *inttree_add(int_node_t *root, int data);
int_node_t *inttree_delete(int_node_t *root, int data);
int_node_t *inttree_find(int_node_t *root, int data, size_t *cmp_cnt);
int get_height(int_node_t *root);
int get_bfactor(int_node_t* root);
void fixheight(int_node_t* root);
int intree_dot_print(FILE *f, int_node_t *tree);
int_node_t *arr_in_inttree(int *arr, size_t size);

int_node_t *intavl_add(int_node_t *root, int data);
int_node_t *intavl_delete(int_node_t *root, int data);
int_node_t *arr_in_intavl(int *arr, size_t size);

size_t inttree_memory(int_node_t *root);
    
#endif // INT_BTREE_H__
