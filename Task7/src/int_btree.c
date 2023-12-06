#include <stdio.h>
#include <stdlib.h>
#include "int_btree.h"
#include "errs.h"

int_node_t *create_int_node(int data)
{
    int_node_t *ptr = malloc(sizeof(int_node_t));
    if (ptr)
    {
        ptr->left = NULL;
        ptr->right = NULL;
        ptr->height = 1;
        ptr->data = data;
    }
    return ptr;
}
void free_int_node(int_node_t *node)
{
    free(node);
}

void free_inttree(int_node_t **root)
{
    if (!*root)
        return;
    if ((*root)->left)
        free_inttree(&(*root)->left);
    if ((*root)->right)
        free_inttree(&(*root)->right);
    free_int_node(*root);
    *root = NULL;
}

int_node_t *inttree_add(int_node_t *root, int data)
{
    if (!root)
        return create_int_node(data);

    if (root->data == data)
        return root;

    if (root->data < data)
        root->right = inttree_add(root->right, data);
    else
        root->left = inttree_add(root->left, data);
    fixheight(root);
    return root;
}

int_node_t *inttree_join(int_node_t *p, int_node_t *q)
{
    if (!p)
        return q;
    if (!q)
        return p;
    
    p->right = inttree_join(p->right, q);
    fixheight(p);
    return p;
}

int_node_t *inttree_delete(int_node_t *root, int data)
{
    if (!root)
        return root;
    
    if (root->data == data)
    {
        int_node_t *tmp = inttree_join(root->left, root->right);
        free_int_node(root);
        return tmp;
    }
    if (root->data > data)
        root->left = inttree_delete(root->left, data);
    else
        root->right = inttree_delete(root->right, data);
    fixheight(root);
    return root;
}


int_node_t *inttree_find(int_node_t *root, int data, size_t *cmp_cnt)
{
    if (!root)
        return NULL;
    (*cmp_cnt)++;
    if (root->data == data)
        return root;
    if (root->data > data)
        return inttree_find(root->left, data, cmp_cnt);
    return inttree_find(root->right, data, cmp_cnt);
}

int get_height(int_node_t *root)
{
    return root ? root->height : 0;
}

int get_bfactor(int_node_t* root)
{
    if (!root)
        return 0;
    return get_height(root->right) - get_height(root->left);
}

void fixheight(int_node_t* root)
{
    int hl = get_height(root->left), hr = get_height(root->right);
    root->height = (hl > hr ? hl : hr) + 1;
}

int subinttree_dot_print(FILE *f, int_node_t *subtree)
{
    int rc = OK;
    if (subtree->left)
    {
        // if (fprintf(f, "n%d[label=\"%d\"];\n", subtree->left->data, subtree->left->data) < 0)
        //     return ERR_IO;
        if (fprintf(f, "%d -> %d;\n", subtree->data, subtree->left->data) < 0)
            return ERR_IO;
        rc = subinttree_dot_print(f, subtree->left);
    }

    if (subtree->right && !rc)
    {
        // if (fprintf(f, "n%d[label=\"%d\"];\n", subtree->right->data, subtree->right->data) < 0)
        //     return ERR_IO;
        if (fprintf(f, "%d -> %d;\n", subtree->data, subtree->right->data) < 0)
            return ERR_IO;
        rc = subinttree_dot_print(f, subtree->right);
    }
    return rc;
}

int intree_dot_print(FILE *f, int_node_t *tree)
{
    if (fprintf(f, "digraph main {\n") < 0)
        return ERR_IO;
    int rc = OK;
    if (tree)
    {
        if (!tree->left && !tree->right)
            if (fprintf(f, "n%d[label=\"%d\"];\n", tree->data, tree->data) < 0)
                return ERR_IO;
        rc = subinttree_dot_print(f, tree);
    }
    if (fprintf(f, "}\n") < 0)
        return ERR_IO;
    return rc;
}

int_node_t *arr_in_inttree(int *arr, size_t size)
{
    int_node_t *root = NULL;
    for (size_t i = 0; i < size; i++)
        root = inttree_add(root, arr[i]);
    return root;
}

int_node_t *intree_rotateleft(int_node_t *root)
{
    int_node_t *new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    fixheight(root);
    fixheight(new_root);
    return new_root;
}

int_node_t *intree_rotateright(int_node_t *root)
{
    int_node_t *new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    fixheight(root);
    fixheight(new_root);
    return new_root;
}

int_node_t *intavl_balance(int_node_t *root)
{
    if (!root)
        return root;
    fixheight(root);
	if(get_bfactor(root) == 2)
    {
        if (get_bfactor(root->right) < 0)
            root->right = intree_rotateright(root->right);
        return intree_rotateleft(root);
    } else if (get_bfactor(root) == -2)
    {
        if (get_bfactor(root->left) > 0)
            root->left = intree_rotateleft(root->left);
        return intree_rotateright(root);
    }
    return root;
}

int_node_t *intavl_add(int_node_t *root, int data)
{
    if (!root)
        return create_int_node(data);
    if (root->data == data)
        return root;
    
    if (root->data > data)
        root->left = intavl_add(root->left, data);
    else
        root->right = intavl_add(root->right, data);
    return intavl_balance(root);
}

int_node_t *intavl_findmin(int_node_t *root)
{
    return root->left ? intavl_findmin(root->left) : root;
}

int_node_t *intavl_removemin(int_node_t *root)
{
	if(!root->left)
		return root->right;
	root->left = intavl_removemin(root->left);
	return intavl_balance(root);
}

int_node_t *intavl_delete(int_node_t *root, int data)
{
    if (!root)
        return root;
    if (root->data > data)
        root->left = intavl_delete(root->left, data);
    else if (root->data < data)
        root->right = intavl_delete(root->right, data);
    else
    {
        int_node_t *left = root->left;
        int_node_t *right = root->right;
        free_int_node(root);
        if (right)
        {
            int_node_t *min = intavl_findmin(right);
            min->right = intavl_removemin(right);
            min->left = left;
            return intavl_balance(min);
        }
        return intavl_balance(left);
    }
    return intavl_balance(root);
}

int_node_t *balance_btree(int_node_t *root)
{
    if (!root)
        return root;
    if (root->left)
        root->left = balance_btree(root->left);
    if (root->right)
        root->right = balance_btree(root->right);
    
    return intavl_balance(root);
}


int_node_t *arr_in_intavl(int *arr, size_t size)
{
    int_node_t *root = NULL;
    for (size_t i = 0; i < size; i++)
        root = intavl_add(root, arr[i]);
    return root;
}

size_t inttree_memory(int_node_t *root)
{
    if (!root)
        return 0;
    return sizeof(*root) + inttree_memory(root->left) + inttree_memory(root->right);
}