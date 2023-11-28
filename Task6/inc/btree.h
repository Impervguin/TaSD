#ifndef BTREE_H__
#define BTREE_H__

typedef struct btree_node btree_node;

#define OPERATION_ID 1
#define VALUE_ID 0

/// @brief Структура узла бинарного дерева выражения
struct btree_node
{
    btree_node *parent; /// Указатель на родителя узла, для корня - NULL
    btree_node *left; /// Указатель на левого потомка
    btree_node *right; /// Указатель на правого потомка
    int data_id; /// Переменная для определения информационной части узла.
    /// Если VALUE_ID, то хранится число, Если OPERATION_ID, то хранится символ операции
    union 
    {
        int value;
        char op;
    } data; /// Информационная часть узла
};


void btree_node_init(btree_node *tree);
btree_node *btree_node_create(void);
void btree_node_free(btree_node *node);
void btree_free(btree_node **tree);


void btree_infix_bypass(btree_node *tree);
void btree_postfix_bypass(btree_node *tree);
void btree_prefix_bypass(btree_node *tree);
int btree_dot_print(FILE *f, btree_node *tree);


int btree_addchar(btree_node **tree, char c);
int btree_findchar(btree_node *tree, char c);
int btree_deletechar(btree_node **tree, char c);


int btree_calculate(btree_node **tree, int *res);
int expression_in_btree(int A, int B, int C, int D, int E, int F, int G, int H, int I, btree_node **tree);
#endif // BTREE_H__
