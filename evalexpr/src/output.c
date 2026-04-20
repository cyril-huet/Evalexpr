#include <stdlib.h>
#include "output.h"

/* free output list */
void free_output(struct output *out)
{
    while (out != NULL)
    {
        struct output *tmp = out;
        out = out->next;
        free(tmp);
    }
}

/* push number */
struct output *push_output_number(struct output *out, int value)
{
    struct output *node = malloc(sizeof(struct output));

    if (node == NULL)
    {
        return NULL;
    }

    node->value = value;
    node->is_number = 1;
    node->op = 0;
    node->next = out;

    return node;
}

/* push operator */
struct output *push_output_op(struct output *out, char op)
{
    struct output *node = malloc(sizeof(struct output));

    if (node == NULL)
    {
        return NULL;
    }

    node->value = 0;
    node->is_number = 0;
    node->op = op;
    node->next = out;

    return node;
}
