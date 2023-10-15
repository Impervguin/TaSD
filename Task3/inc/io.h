#ifndef IO_H__
#define IO_H__

typedef enum {MULT = 1, STD_MULT = 2, COMPAR = 3, EXIT = 0} command_t;
#define MAX_COMMAND_NUM 3

int read_file(FILE **f);
void print_intro();
void print_menu();
int int_input(int *res, char *mes);
void print_error(int rc);

#endif