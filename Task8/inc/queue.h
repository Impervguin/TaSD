#ifndef QUQUE_H__
#define QUQUE_H__

typedef struct list_queue list_queue_t;
typedef struct qnode qnode_t;

/// Узел очереди-списка заявок
struct qnode
{
    int data; /// Часть узла с данными в виде заявок.
    qnode_t* next; /// Указатель на следующий узел.
};

/// Очередь-список
struct list_queue
{
    qnode_t *pin; /// Указатель на входную часть списка.
    qnode_t *pout; /// Указатель на выходную часть списка.
};

void queue_init(list_queue_t *q);

qnode_t *qnode_create(void);

void qnode_free(qnode_t *qn);

void queue_free(list_queue_t *q);

int queue_add(list_queue_t *q, int *data);

int queue_pop(list_queue_t *q, int *data);


#endif // QUQUE_H__
