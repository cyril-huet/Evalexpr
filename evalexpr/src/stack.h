#ifndef STACK_H
#define STACK_H

struct stack
{
    char op;
    struct stack *next;
};

struct stack *push_stack(struct stack *stack, char op);
struct stack *pop_stack(struct stack *stack, char *op);
void free_stack(struct stack *stack);

#endif
