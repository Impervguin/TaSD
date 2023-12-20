#include <stdlib.h>
#include "errs.h"
#include "queue.h"


void queue_init(list_queue_t *q)
{
    q->pin = NULL;
    q->pout = NULL;
}

qnode_t *qnode_create(void)
{
    return malloc(sizeof(qnode_t));
}

void qnode_free(qnode_t *qn)
{
    free(qn);
}

void queue_free(list_queue_t *q)
{
    qnode_t *next;
    for (qnode_t *now = q->pout; now != NULL; now = next)
    {
        next = now->next;
        qnode_free(now);
    }
}

int queue_add(list_queue_t *q, int *data)
{
    qnode_t *tmp = qnode_create();
    if (tmp == NULL)
        return ERR_MEMORY;
    tmp->data = *data;
    tmp->next = NULL;
    if (q->pin)
        q->pin->next = tmp;
    if (!q->pout)
        q->pout = tmp;
    q->pin = tmp;
    return OK;
}

int queue_pop(list_queue_t *q, int *data)
{
    if (q->pout == NULL)
        return ERR_EMPTY_QUEUE;
    qnode_t *tmp = q->pout->next;
    *data = q->pout->data;
    qnode_free(q->pout);
    q->pout = tmp;
    if (q->pout == NULL)
        q->pin = NULL;
    return OK;
}