#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "errs.h"
#include "orgraph.h"

long long int get_time(struct timespec *time_s, struct timespec *time_e)
{
    return (time_e -> tv_sec * 1000000000 + time_e -> tv_nsec) - (time_s -> tv_sec * 1000000000 + time_s -> tv_nsec);
}

int get_random(int max)
{
    return (int) ((((double) rand()) / RAND_MAX) * max);
}

#define TEST_COUNT 100000
int main(int argc, char **argv)
{
    struct timespec st, ed;
    int rc = 0;
    long bfs_time = 0, dfs_time = 0;
    orgraph_t graph = {NULL, 0, 0};
    if (argc != 2)
        return 1;
    FILE *fin = fopen(argv[1], "r");
    if (!fin)
        return 2;
    
    if (orgraph_read(fin, &graph, 0))
        return 3;
    
    fclose(fin);

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        unmark_graph(&graph);
        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        int start = get_random(graph.size);
        rc = DFS(&graph, start);
        if (rc)
        {
            orgraph_free(&graph);
            return 4;
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
        dfs_time += get_time(&st, &ed);
    }
    dfs_time /= TEST_COUNT;

    for (size_t i = 0; i < TEST_COUNT; i++)
    {
        unmark_graph(&graph);
        clock_gettime(CLOCK_MONOTONIC_RAW, &st);
        int start = get_random(graph.size);
        rc = BFS(&graph, start);
        if (rc)
        {
            orgraph_free(&graph);
            return 4;
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
        bfs_time += get_time(&st, &ed);
    }
    bfs_time /= TEST_COUNT;

    printf("Среднее время поиска в глубину: %ld нс\n", dfs_time);
    printf("Среднее время поиска в ширину: %ld нс\n", bfs_time);
    return 0;
}