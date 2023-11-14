#include "list.h"
#include "errs.h"
#include <stdlib.h>


node_t *node_create(void)
{
    node_t *t = malloc(sizeof(node_t));
    if (t)
    {
        t->next = NULL;
        t->data = NULL;
    }
    return t;
}

void node_free(node_t *n)
{
    free(n);
}
void rlist_free(node_t **head)
{
    node_t *next = NULL;
    for (node_t *now = *head; now != NULL; now = next)
    {
        next = now->next;
        free(now);
    }
    *head = NULL;
}

int rlist_add(node_t **head, void *data)
{
    node_t *new = node_create();
    if (!new)
        return ERR_MEMORY;
    new->data = data;
    if (*head == NULL)
    {
        *head = new;
    }
    else
    {
        node_t *last = *head;
        for (; last->next != NULL; last = last->next);
        last->next = new;
    }
    return OK;
}

int rlist_pop(node_t **head, void **data)
{
    if (!*head)
        return ERR_EMPTY_QUEUE;
    node_t *get = *head;
    *head = (*head)->next;
    *data = get->data;
    node_free(get);
    return OK;
}
