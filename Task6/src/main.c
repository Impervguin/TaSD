#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "errs.h"

int main()
{
    btree_node *root = NULL;
    FILE *f = fopen("a.dot", "w");
    // expression_in_btree(1, 2, 3, 4, 5, 6, 7, 8, 9, &root);
    // btree_infix_bypass(root);
    // btree_postfix_bypass(root);
    // btree_prefix_bypass(root);
    // int n = 0;
    // btree_calculate(&root, &n);
    // printf("%d\n", n);
    btree_addchar(&root, 'h');
    btree_addchar(&root, 'c');
    btree_addchar(&root, 'a');
    btree_addchar(&root, 'b');
    btree_addchar(&root, 'u');
    btree_addchar(&root, 'l');
    btree_addchar(&root, 'y');
    btree_addchar(&root, 'z');
    btree_addchar(&root, 'e');
    // btree_deletechar(&root, 'b');
    // btree_deletechar(&root, 'h');
    // printf("%d\n", btree_findchar(root, 'b'));
    btree_dot_print(f, root);
    fclose(f);
    system("dot -Tsvg a.dot > a.svg");
    // system("open a.svg");
    btree_free(&root);
}