#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "io.h"
#include "errs.h"
#include "orgraph.h"

long int get_time(struct timespec *time_s, struct timespec *time_e)
{
    return (time_e -> tv_sec * 1000000000 + time_e -> tv_nsec) - (time_s -> tv_sec * 1000000000 + time_s -> tv_nsec);
}

int main(void)
{
    struct timespec st, ed;
    long bfs_time, dfs_time;
    orgraph_t graph = {NULL, 0, 0};
    int command;
    int rc = OK;
    int running = 1;

    print_intro();

    while (running)
    {
        orgraph_t tmpgraph = {NULL, 0, 0};
        rc = OK;
        char *dotfname = "tmp.dot";
        FILE *dot;
        FILE *fgraph = NULL;
        print_menu();
        rc = int_input(&command, "");
        int itmp;
        if (!rc)
            if (command > MAX_COMMAND_NUM || command < 0)
                rc = ERR_COMMAND;
        if (!rc && command == EXIT)
        {
            running = 0;
            continue;
        }
        
        if (!rc)
        {
            switch (command)
            {
                case GRAPH:
                    rc = int_input(&itmp, "Вид ввода?(0 - файл, любое другое число - консольный):");
                    if (rc)
                        break;
                    if (!itmp)
                    {
                        rc = read_file(&fgraph);
                        if (rc)
                            break;
                        rc = orgraph_read(fgraph, &tmpgraph, 0);
                        fclose(fgraph);
                    }
                    else 
                        rc = orgraph_read(stdin, &tmpgraph, 1);
                    if (rc)
                        break;
                    if (graph.nodes)
                        orgraph_free(&graph);
                    
                    if (tmpgraph.size == 0)
                    {
                        printf("Граф пустой.\n");
                        break;
                    }
                    graph = tmpgraph;
                    tmpgraph.nodes = NULL;
                    tmpgraph.size = 0;
                    tmpgraph.max_size = 0;
                    printf("Граф успешно изменен.\n");
                    dot = fopen(dotfname, "w");
                    if (!dot)
                    {
                        rc = ERR_FILE;
                        break;
                    }
                    rc = orgraph_to_dot(dot, &graph);
                    fclose(dot);
                    if (rc)
                        break;
                    system("dot -Tsvg tmp.dot > tmp.svg");
                    system("open tmp.svg");
                    break;
                case BFSC:
                    if (!graph.nodes)
                    {
                        printf("Не задан граф.");
                        break;
                    }
                    unmark_graph(&graph);
                    print_graph(&graph);
                    rc = int_input(&itmp, "Введите индекс начального узла:");
                    if (rc)
                        break;
                    rc = BFS(&graph, itmp);
                    if (rc)
                        break;
                    dot = fopen(dotfname, "w");
                    if (!dot)
                    {
                        rc = ERR_FILE;
                        break;
                    }
                    rc = orgraph_to_dot(dot, &graph);
                    fclose(dot);
                    if (rc)
                        break;
                    system("dot -Tsvg tmp.dot > tmp.svg");
                    system("open tmp.svg");
                    break;
                case DFSC:
                    if (!graph.nodes)
                    {
                        printf("Не задан граф.");
                        break;
                    }
                    unmark_graph(&graph);
                    print_graph(&graph);
                    rc = int_input(&itmp, "Введите индекс начального узла:");
                    if (rc)
                        break;
                    rc = DFS(&graph, itmp);
                    if (rc)
                        break;
                    dot = fopen(dotfname, "w");
                    if (!dot)
                    {
                        rc = ERR_FILE;
                        break;
                    }
                    rc = orgraph_to_dot(dot, &graph);
                    fclose(dot);
                    if (rc)
                        break;
                    system("dot -Tsvg tmp.dot > tmp.svg");
                    system("open tmp.svg");
                    break;
                case COMPARE:
                    if (!graph.nodes)
                    {
                        printf("Не задан граф.");
                        break;
                    }
                    unmark_graph(&graph);
                    print_graph(&graph);
                    rc = int_input(&itmp, "Введите индекс начального узла:");
                    if (rc)
                        break;

                    unmark_graph(&graph);
                    clock_gettime(CLOCK_MONOTONIC_RAW, &st);
                    rc = DFS(&graph, itmp);
                    clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
                    dfs_time = get_time(&st, &ed);
                    if (rc)
                        break;

                    unmark_graph(&graph);
                    clock_gettime(CLOCK_MONOTONIC_RAW, &st);
                    rc = BFS(&graph, itmp);
                    clock_gettime(CLOCK_MONOTONIC_RAW, &ed);
                    bfs_time = get_time(&st, &ed);
                    if (rc)
                        break;
                    
                    printf("Время поиска в глубину: %ld нс\n", dfs_time);
                    printf("Время поиска в ширину: %ld нс\n", bfs_time);
                    break;
            }
        }
        print_error(rc); 
        printf("\n");  
    }
    if (graph.nodes)
        orgraph_free(&graph);
    return OK;
}