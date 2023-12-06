#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "int_list.h"
#include "errs.h"

int_listnode_t *int_node_create(int val)
{
    int_listnode_t *node = malloc(sizeof(int_listnode_t));
    if (node)
    {
        node->next = NULL;
        node->data = val;
    }
    return node;
}

void int_node_free(int_listnode_t *node)
{
    free(node);
}

void int_list_free(int_list *list)
{
    int_listnode_t *next = NULL;
    for (int_listnode_t *now = list->start; now != NULL; now = next)
    {
        next = now->next;
        int_node_free(now);
    }
    list->start = NULL;
    list->end = NULL;
}

int int_list_add(int_list *list, int val)
{
    size_t tmp = 0;
    if (int_list_find(list->start, val, &tmp) != ERR_NOT_FOUND)
        return ERR_ALREADY_IN;
    int_listnode_t *new = int_node_create(val);
    if (!new)
        return ERR_MEMORY;
    new->data = val;
    if (list->start == NULL)
    {
        list->start = new;
        list->end = new;
    }
    else
    {
        list->end->next = new;
        list->end = new;
    }
    return OK;
}

void int_list_add_node(int_list *list, int_listnode_t *node)
{
    if (list->start == NULL)
    {
        list->start = node;
        list->end = node;
        node->next = NULL;
    }
    else
    {
        list->end->next = node;
        list->end = node;
        node->next = NULL;
    }
}

int int_list_remove(int_list *list, int val)
{
    if (list->start == NULL)
        return ERR_NOT_FOUND;
    if (list->start->data == val)
    {
        int_listnode_t *next = list->start->next;
        int_node_free(list->start);
        list->start = next;
        if (!list->start)
            list->end = NULL;
        return OK;
    }
    int_listnode_t *now = list->start;
    for (; now->next != NULL && now->next->data != val; now = now->next);

    if (now->next != NULL && val == now->next->data)
    {
        int_listnode_t *del = now->next;
        now->next = now->next->next;
        int_node_free(del);
        if (now->next == NULL)
            list->end = now;
        return OK;
    }

    return ERR_NOT_FOUND;
}

int int_list_find(int_listnode_t *list, int val, size_t *cmp_cnt)
{
    (*cmp_cnt)++;
    if (!list)
        return ERR_NOT_FOUND;
    if (list->data == val)
        return OK;
    return int_list_find(list->next, val, cmp_cnt);
}

size_t int_list_count(int_listnode_t *list)
{
    if (!list)
        return 0;
    return int_list_count(list->next) + 1;
}

void print_int_list(int_list *list)
{
    if (!list->start)
    {
        printf("\n");
        return;
    }
    int_listnode_t *now = list->start;
    for (;now->next != NULL; now = now->next)
    {
        printf("%d -> ", now->data);
    }
    printf("%d\n", now->data);
}


size_t int_list_memory(int_list *list)
{
    if (!list)
        return 0;
    return sizeof(int_list) + sizeof(int_listnode_t) * int_list_count(list->start);
}