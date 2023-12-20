#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"
#include "errs.h"
#include "orgraph.h"

ornode_t *create_ornode(char *name)
{
    ornode_t *new = malloc(sizeof(ornode_t));
    if (new)
    {
        new->name = name;
        new->mark = 0;
    }
    return new;
}

void free_ornode(ornode_t *node)
{
    if (!node)
        return;
    free(node->name);
    free(node);
}

orlist_t *create_orlist(ornode_t *data)
{
    orlist_t *new = malloc(sizeof(orlist_t));
    if (new)
    {
        new->data = data;
        new->next = NULL;
    }
    return new;
}

void free_orlist(orlist_t *list)
{
    free(list);
}

int orgraph_init(orgraph_t *graph, size_t max_size)
{
    orlist_t *new = malloc(sizeof(orlist_t) * max_size);
    if (new)
    {
        graph->nodes = new;
        graph->size = 0;
        graph->max_size = max_size;
        return OK;
    }
    return ERR_MEMORY;
}

void orgraph_free(orgraph_t *graph)
{
    if (!graph->nodes)
        return;
    for (size_t i = 0; i < graph->size; i++)
    {
        orlist_t *next;
        for (orlist_t *now = graph->nodes[i].next; now != NULL; now = next)
        {
            next = now->next;
            free_orlist(now);
        }
        free_ornode(graph->nodes[i].data);
    }
    free(graph->nodes);
    graph->max_size = 0;
    graph->size = 0;
}

int orgraph_add_node(orgraph_t *graph, char *node)
{
    if (graph->size == graph->max_size)
        return ERR_MEMORY;
    
    ornode_t *new = create_ornode(node);
    if (!new)
        return ERR_MEMORY;
    new->id = graph->size;
    graph->nodes[graph->size].data = new;
    graph->nodes[graph->size++].next = NULL;
    return OK;
}

int orgraph_add_connection(orgraph_t *graph, size_t id1, size_t id2)
{
    if (id1 >= graph->size || id2 >= graph->size)
        return ERR_RANGE;
    
    orlist_t *now = &graph->nodes[id1];
    for (; now->next != NULL && now->next->data->id != id2; now = now->next);
    if (now->next == NULL)
    {
        orlist_t *new = create_orlist(graph->nodes[id2].data);
        if (!new)
            return ERR_MEMORY;
        now->next = new;
    }
    return OK;
}

static char *readname(FILE *f)
{
    char *tmp = NULL;
    size_t len = 0;
    if (getline(&tmp, &len, f) < 0)
    {
        free(tmp);
        return NULL;
    }
    len = strlen(tmp);
    if (len && tmp[len - 1] == '\n')
        tmp[--len] = '\0';
    
    if (!len)
    {
        free(tmp);
        return NULL;
    }

    return tmp;
}

int orgraph_read(FILE *f, orgraph_t *graph, int verbose)
{
    size_t graph_size = 0;
    if (verbose)
        printf("%s", "Введите количество вершин в графе:");
    if (fscanf(f, "%zu", &graph_size) != 1)
        return ERR_FORMAT;
    char buf[2];
    if (fgets(buf, 2, f) == NULL)
        return ERR_FORMAT;
    if (buf[0] != '\n')
        return ERR_FORMAT;
    int rc = orgraph_init(graph, graph_size);
    if (rc)
        return rc;
    if (verbose)
    {
        printf("%s", "Введите имя каждой из вершин, каждая на новой строке:\n");
    }
    for (size_t i = 0; i < graph_size; i++)
    {
        if (verbose)
        {
            printf("%zu-ая:", i);
        }
        char *tmp = readname(f);
        if (!tmp)
        {
            orgraph_free(graph);
            return ERR_FORMAT;
        }
        rc = orgraph_add_node(graph, tmp);
        if (rc)
        {
            orgraph_free(graph);
            return rc;
        }
    }

    if (verbose)
    {
        printf("%s", "Введите ребра графа в формате индекс начало ребра и индекс конца ребра через пробел:\n");
    }
    size_t id1, id2;
    while (fscanf(f, "%zu%zu", &id1, &id2) == 2)
    {
        rc = orgraph_add_connection(graph, id1, id2);
        if (rc)
        {
            orgraph_free(graph);
            return rc;
        }
    }
    return OK;
}

int orgraph_to_dot(FILE *f, orgraph_t *graph)
{
    if (fprintf(f, "digraph main {\n") < 0)
        return ERR_IO;
    for (size_t i = 0; i < graph->size; i++)
    {
        if (fprintf(f, "n%zu[label=\"%s\"];\n", i, graph->nodes[i].data->name) < 0)
            return ERR_IO;
        if (graph->nodes[i].data->mark == VISITED)
            if (fprintf(f, "n%zu[color=\"%s\"];\n", i, "red") < 0)
                return ERR_IO;
    }
        
    int rc = OK;
    for (size_t i = 0; i < graph->size; i++)
        for (orlist_t *now = graph->nodes[i].next; now != NULL; now = now->next)
            if (fprintf(f, "n%zu -> n%zu;\n", i, now->data->id) < 0)
                return ERR_IO;
    if (fprintf(f, "}\n") < 0)
        return ERR_IO;
    return rc;
}

void print_graph(orgraph_t *graph)
{
    for (size_t i = 0; i < graph->size; i++)
        printf("%zu - %s\n", i, graph->nodes[i].data->name);
}

void unmark_graph(orgraph_t *graph)
{
    for (size_t i = 0; i < graph->size; i++)
        graph->nodes[i].data->mark = UNMARKED;
}


int DFS(orgraph_t *graph, size_t start)
{
    stack_node_t *stack = NULL;

    if (start >= graph->size)
        return ERR_RANGE;
    
    orlist_t *now = &graph->nodes[start];
    while (1)
    {
        now->data->mark = VISITED;
        orlist_t *connection = now->next;
        for (; connection != NULL && connection->data->mark == VISITED; connection = connection->next);
        if (connection && connection->data->mark == UNMARKED)
        {
            add_list_stack(&stack, (int) now->data->id);
            now = &graph->nodes[connection->data->id];
        }
        else
        {
            int id;
            int rc = pop_list_stack(&stack, &id);
            if (rc == ERR_EMPTY_STACK)
                break;
            now = &graph->nodes[id];
        }
    }
    return OK;
}

int BFS(orgraph_t *graph, size_t start)
{
    list_queue_t queue;
    queue_init(&queue);

    if (start >= graph->size)
        return ERR_RANGE;
    int now_id = start;
    queue_add(&queue, &now_id);
    while (queue_pop(&queue, &now_id) != ERR_EMPTY_QUEUE)
    {
        if (graph->nodes[now_id].data->mark == VISITED)
            continue;
        graph->nodes[now_id].data->mark = VISITED;
        
        for (orlist_t *connection = graph->nodes[now_id].next; connection != NULL; connection = connection->next)
        {
            if (connection->data->mark == UNMARKED)
            {
                int id = connection->data->id;
                queue_add(&queue, &id);
            }  
        }
            
    }
    return OK;
}