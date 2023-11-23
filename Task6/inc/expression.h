#ifndef EXPRESSION_H__
#define EXPRESSION_H__

typedef struct expression_t expression_t;

struct expression_t
{
    size_t size;
    size_t allocated;
    char *string;
};

int add_char_to_expression(expression_t *expr, char c);

#endif // EXPRESSION_H__
