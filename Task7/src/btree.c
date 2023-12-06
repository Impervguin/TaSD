#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "errs.h"


void btree_node_init(btree_node *node)
{
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->data_id = VALUE_ID;
}

btree_node *btree_node_create(void)
{
    btree_node *ptr = malloc(sizeof(btree_node));
    if (ptr)
        btree_node_init(ptr);
    return ptr;
}

void btree_node_free(btree_node *node)
{
    free(node);
}

void btree_free(btree_node **tree)
{
    btree_node *now = *tree;
    while (*tree != NULL)
    {
        if (now->left == NULL)
        {
            if (now->right == NULL)
            {
                btree_node *parent = now->parent;
                btree_node_free(now);
                if (parent)
                {
                    if (parent->left == now)
                        parent->left = NULL;
                    else
                        parent->right = NULL;
                    now = parent;
                }
                else
                    *tree = NULL;
            }
            else
                now = now->right;
        }
        else
            now = now->left;
    }
}

void btree_infix_bypass(btree_node *tree)
{
    if (!tree)
        return;
    btree_infix_bypass(tree->left);
    if (tree->data_id == OPERATION_ID)
        printf("%c", tree->data.op);
    else
        printf("%d", tree->data.value);
    btree_infix_bypass(tree->right);
    if (tree->parent == NULL)
        printf("\n");
}

void btree_postfix_bypass(btree_node *tree)
{
    if (!tree)
        return;
    btree_postfix_bypass(tree->left);
    btree_postfix_bypass(tree->right);
    if (tree->data_id == OPERATION_ID)
        printf("%c", tree->data.op);
    else
        printf("%d", tree->data.value);
    if (tree->parent == NULL)
        printf("\n");
}

void btree_prefix_bypass(btree_node *tree)
{
    if (!tree)
        return;
    if (tree->data_id == OPERATION_ID)
        printf("%c", tree->data.op);
    else
        printf("%d", tree->data.value);
    btree_prefix_bypass(tree->left);
    btree_prefix_bypass(tree->right);
    if (tree->parent == NULL)
        printf("\n");
}

int btree_calculate(btree_node **tree, int *res)
{
    btree_node *now = *tree;
    while ((*tree)->data_id != VALUE_ID)
    {
        if (now->left->data_id == OPERATION_ID)
            now = now->left;
        else if (now->right->data_id == OPERATION_ID)
            now = now->right;
        else
        {
            int num1 = now->left->data.value, num2 = now->right->data.value;
            if (now->data.op == '+')
                now->data.value = num1 + num2;
            else if (now->data.op == '-')
                now->data.value = num1 - num2;
            else if (now->data.op == '*')
                now->data.value = num1 * num2;
            else if (now->data.op == '/')
            {
                if (num2 == 0)
                    return ERR_ZERO_DIVISION;
                now->data.value = num1 / num2;
            }
            else 
                return ERR_FORMAT;
            now->data_id = VALUE_ID;
            btree_free(&now->left);
            btree_free(&now->right);
            now = now->parent;
        }
    }
    *res = (*tree)->data.value;
    btree_free(tree);
    return OK;  
}

int subbtree_dot_print(FILE *f, btree_node *subtree, int *i)
{
    int now = *i;
    int rc = OK;
    if (subtree->left)
    {
        (*i)++;
        if (subtree->left->data_id == VALUE_ID)
            if (fprintf(f, "n%d[label=\"%d\"];\n", *i, subtree->left->data.value) < 0)
                return ERR_IO;
        if (subtree->left->data_id == OPERATION_ID)
            if (fprintf(f, "n%d[label=\"%c\"];\n", *i, subtree->left->data.op) < 0)
                return ERR_IO;
        if (fprintf(f, "n%d -> n%d;\n", now, *i) < 0)
            return ERR_IO;
        rc = subbtree_dot_print(f, subtree->left, i);
    }

    if (subtree->right && !rc)
    {
        (*i)++;
        if (subtree->right->data_id == VALUE_ID)
            if (fprintf(f, "n%d[label=\"%d\"];\n", *i, subtree->right->data.value) < 0)
                return ERR_IO;
        if (subtree->right->data_id == OPERATION_ID)
            if (fprintf(f, "n%d[label=\"%c\"];\n", *i, subtree->right->data.op) < 0)
                return ERR_IO;
        if (fprintf(f, "n%d -> n%d;\n", now, *i) < 0)
            return ERR_IO;
        rc = subbtree_dot_print(f, subtree->right, i);
    }
    return rc;
}

int btree_dot_print(FILE *f, btree_node *tree)
{
    if (fprintf(f, "digraph main {\n") < 0)
        return ERR_IO;
    int rc = OK;
    if (tree)
    {
        int i = 0;
        if (tree->data_id == VALUE_ID)
            if (fprintf(f, "n%d[label=\"%d\"];\n", i, tree->data.value) < 0)
                return ERR_IO;
        if (tree->data_id == OPERATION_ID)
            if (fprintf(f, "n%d[label=\"%c\"];\n", i, tree->data.op) < 0)
                return ERR_IO;
        rc = subbtree_dot_print(f, tree, &i);
    }
    if (fprintf(f, "}\n") < 0)
        return ERR_IO;
    return rc;
}

#define NODE_VALUE_INIT(c) \
btree_node *c##node;       \
if (!rc)             \
{                    \
    c##node = btree_node_create(); \
    if (!c##node)                              \
        rc = ERR_MEMORY;                       \
    else                                       \
    {                                          \
    c##node->data_id = VALUE_ID;                  \
    c##node->data.value = c;                      \
    c##node->left = NULL;                         \
    c##node->right = NULL;                        \
    }                   \
}

#define NODE_OP_SETTING(name, datan, leftn, rightn) \
btree_node *name;       \
if (!rc)             \
{                    \
    name = btree_node_create(); \
    if (!name)                              \
        rc = ERR_MEMORY;                       \
    else                                       \
    {                                          \
    name->data_id = OPERATION_ID;                  \
    name->data.op = datan;                      \
    name->left = leftn;                         \
    leftn->parent = name;                        \
    name->right = rightn;                        \
    rightn->parent = name;                        \
    }                   \
}



int expression_in_btree(int A, int B, int C, int D, int E, int F, int G, int H, int I, btree_node **tree)
{
    int rc = OK;
    NODE_VALUE_INIT(A)
    NODE_VALUE_INIT(B)
    NODE_VALUE_INIT(C)
    NODE_VALUE_INIT(D)
    NODE_VALUE_INIT(E)
    NODE_VALUE_INIT(F)
    NODE_VALUE_INIT(G)
    NODE_VALUE_INIT(H)
    NODE_VALUE_INIT(I)

    NODE_OP_SETTING(EaddF, '+', Enode, Fnode)
    NODE_OP_SETTING(Dmultnode, '*', Dnode, EaddF)
    NODE_OP_SETTING(GminH, '-', Gnode, Hnode)
    NODE_OP_SETTING(minmultnode, '-', Dmultnode, GminH)
    NODE_OP_SETTING(Caddnode, '+', Cnode, minmultnode)
    NODE_OP_SETTING(Iaddnode, '+', Caddnode, Inode)
    NODE_OP_SETTING(Bmultnode, '*', Bnode, Iaddnode)
    NODE_OP_SETTING(Aaddnode, '+', Anode, Bmultnode)

    if (!rc)
        *tree = Aaddnode;
    return rc;
}


int btree_addchar(btree_node **tree, char c)
{
    btree_node *now = *tree;
    if (now == NULL)
    {
        now = btree_node_create();
        if (!now)
            return ERR_MEMORY;
        now->data_id = OPERATION_ID;
        now->data.op = c;
        *tree = now;
        return OK;
    }
    btree_node *place = NULL;
    while (!place)
    {
        if (c > now->data.op)
        {
            if (now->right == NULL)
                place = now;
            else
                now = now->right;
        }
        else if (c < now->data.op)
        {
            if (now->left == NULL)
                place = now;
            else
                now = now->left;
        }
        else
            return ERR_ALREADY_IN;
    }
    btree_node *new = btree_node_create();
    if (!new)
        return ERR_MEMORY;
    new->parent = place;
    new->data.op = c;
    new->data_id = OPERATION_ID;
    if (c > place->data.op)
        place->right = new;
    else
        place->left = new;
    return OK;
}

int btree_findchar(btree_node *tree, char c)
{
    btree_node *now = tree;
    while (now != NULL)
    {
        if (c > now->data.op)
            now = now->right;
        else if (c < now->data.op)
            now = now->left;
        else
            return OK;
    }
    return ERR_NOT_FOUND;
}

/// @brief Функция не проверяет не наличие всех элементов поддерева в дереве.
/// @param tree 
/// @param subtree 
int btree_addsubtree(btree_node *tree, btree_node *subtree)
{
    btree_node *now = tree;
    while (now != NULL)
    {
        if (now->data.op > subtree->data.op)
        {
            if (!now->left)
            {
                now->left = subtree;
                subtree->parent = now;
                break;
            }
            else
                now = now->left;
        }
        else if (now->data.op < subtree->data.op)
        {
            if (!now->right)
            {
                now->right = subtree;
                subtree->parent = now;
                break;
            }
            else
                now = now->right;
        }
        else 
            return ERR_ALREADY_IN;
    }
    return OK;
}

int btree_deletechar(btree_node **tree, char c)
{
    btree_node *now = *tree;
    while (now != NULL)
    {
        if (c > now->data.op)
            now = now->right;
        else if (c < now->data.op)
            now = now->left;
        else
        {
            if (now->left != NULL)
            {
                now->left->parent = now->parent;
                if (now->parent)
                {
                    if (now->parent->left == now)
                        now->parent->left = now->left;
                    else
                        now->parent->right = now->left;
                }

                if (now->right)
                {
                    btree_addsubtree(now->left, now->right);
                }
                if (now == *tree)
                    *tree = now->left;
            }
            else if (now->right)
            {
                now->right->parent = now->parent;
                if (now->parent)
                {
                    if (now->parent->left == now)
                        now->parent->left = now->right;
                    else
                        now->parent->right = now->right;
                }

                if (now == *tree)
                    *tree = now->right;
            }
            else
            {
                if (now->parent)
                {
                    if (now->parent->left == now)
                        now->parent->left = NULL;
                    else
                        now->parent->right = NULL;
                }
                if (now == *tree)
                    *tree = NULL;
            }
            btree_node_free(now);
            return OK;
        }
    }
    return ERR_NOT_FOUND;
}


int btree_postfix_calculate(btree_node **tree)
{
    btree_node *now = *tree;
    while ((*tree)->data_id != VALUE_ID)
    {
        if (now->left->data_id == OPERATION_ID)
            now = now->left;
        else if (now->right->data_id == OPERATION_ID)
            now = now->right;
        else
        {
            int num1 = now->left->data.value, num2 = now->right->data.value;
            if (now->data.op == '+')
                now->data.value = num1 + num2;
            else if (now->data.op == '-')
                now->data.value = num1 - num2;
            else if (now->data.op == '*')
                now->data.value = num1 * num2;
            else if (now->data.op == '/')
            {
                if (num2 == 0)
                    return ERR_ZERO_DIVISION;
                now->data.value = num1 / num2;
            }
            else 
                return ERR_FORMAT;
            now->data_id = VALUE_ID;
            now = now->parent;
        }
    }
    return OK;  
}

size_t btree_node_count(btree_node *tree)
{
    if (tree == NULL)
        return 0;
    if (tree->left == NULL && tree->right == NULL)
        return 1;
    return 1 + btree_node_count(tree->left) + btree_node_count(tree->right);
}

void btree_infix_fill_arr(btree_node *tree, int *arr, size_t *size)
{
    if (tree == NULL)
        return;
    btree_infix_fill_arr(tree->left, arr, size);
    arr[(*size)++] = tree->data.value;
    btree_infix_fill_arr(tree->right, arr, size);
}

int *btree_infix_arr(btree_node *tree, size_t *size)
{
    size_t asize = btree_node_count(tree);
    if (asize == 0)
        return NULL;
    int *arr = malloc(sizeof(int) * asize);
    if (!arr)
        return NULL;
    btree_infix_fill_arr(tree, arr, size);
    return arr;
}