#include "stack.h"

#include <stdlib.h>

struct stack *push_stack(struct stack *stack, char operation)
{
    struct stack *new_node = malloc(sizeof(struct stack));

    if (new_node == NULL)
    {
        return NULL;
    }

    new_node->operation = operation;
    new_node->next = stack;

    return new_node;
}

struct stack *pop_stack(struct stack *stack, char *operation)
{
    struct stack *next_node;

    if (stack == NULL)
    {
        return NULL;
    }

    *operation = stack->operation;
    next_node = stack->next;
    free(stack);

    return next_node;
}

void free_stack(struct stack *stack)
{
    struct stack *next_node;

    while (stack != NULL)
    {
        next_node = stack->next;
        free(stack);
        stack = next_node;
    }
}