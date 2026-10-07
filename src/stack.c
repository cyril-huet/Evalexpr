#include <stdlib.h>
#include "stack.h"

/* free stack */
void free_stack(struct stack *stack)
{
    while (stack != NULL)
    {
        struct stack *tmp = stack;
        stack = stack->next;
        free(tmp);
    }
}

/* push operator */
struct stack *push_stack(struct stack *stack, char op)
{
    struct stack *node = malloc(sizeof(struct stack));

    if (node == NULL)
    {
        return NULL;
    }

    node->op = op;
    node->next = stack;

    return node;
}

/* pop operator */
struct stack *pop_stack(struct stack *stack, char *op)
{
    struct stack *next;

    if (stack == NULL)
    {
        return NULL;
    }

    *op = stack->op;
    next = stack->next;

    free(stack);

    return next;
}
