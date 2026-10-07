#ifndef STACK_H
#define STACK_H

struct stack
{
    char operation;
    struct stack *next;
};

struct stack *push_stack(struct stack *stack, char operation);
struct stack *pop_stack(struct stack *stack, char *operation);
void free_stack(struct stack *stack);

#endif /* ! STACK_H */