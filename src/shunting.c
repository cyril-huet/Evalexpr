#include "output.h"
#include "stack.h"
#include "utils.h"

#include <stdlib.h>

static void add_number(struct output **output, int value)
{
    struct output *new_output = push_output_number(*output, value);

    if (new_output == NULL)
    {
        free_output(*output);
        exit(4);
    }

    *output = new_output;
}

static void add_operation(struct output **output, char operation)
{
    struct output *new_output =
        push_output_operation(*output, operation);

    if (new_output == NULL)
    {
        free_output(*output);
        exit(4);
    }

    *output = new_output;
}

static void push_operation(struct stack **operations, char operation)
{
    struct stack *new_stack = push_stack(*operations, operation);

    if (new_stack == NULL)
    {
        free_stack(*operations);
        exit(4);
    }

    *operations = new_stack;
}

static void empty_until_parenthesis(struct stack **operations,
                                     struct output **output)
{
    char operation;

    while (*operations != NULL
           && (*operations)->operation != '(')
    {
        *operations = pop_stack(*operations, &operation);
        add_operation(output, operation);
    }
}

static void handle_operator(struct stack **operations,
                            struct output **output, char operation)
{
    char previous_operation;

    while (*operations != NULL
           && (*operations)->operation != '('
           && (get_priority((*operations)->operation)
                   > get_priority(operation)
               || (get_priority((*operations)->operation)
                       == get_priority(operation)
                   && operation != '^')))
    {
        *operations = pop_stack(*operations, &previous_operation);
        add_operation(output, previous_operation);
    }

    push_operation(operations, operation);
}

static void finish_operations(struct stack **operations,
                              struct output **output)
{
    char operation;

    while (*operations != NULL)
    {
        if ((*operations)->operation == '(')
        {
            free_stack(*operations);
            free_output(*output);
            exit(2);
        }

        *operations = pop_stack(*operations, &operation);
        add_operation(output, operation);
    }
}

struct output *shunting_yard(char *expression)
{
    struct stack *operations = NULL;
    struct output *output = NULL;
    int index = 0;

    while (expression[index] != '\0')
    {
        if (expression[index] == ' ')
        {
            index++;
            continue;
        }

        if (is_number_start(expression, index) == 1)
        {
            add_number(&output, read_number(expression, &index));
            continue;
        }

        if (get_priority(expression[index]) != 0)
        {
            handle_operator(&operations, &output, expression[index]);
            index++;
            continue;
        }

        if (expression[index] == '(')
        {
            push_operation(&operations, expression[index]);
            index++;
            continue;
        }

        if (expression[index] == ')')
        {
            empty_until_parenthesis(&operations, &output);

            if (operations == NULL)
            {
                free_output(output);
                exit(2);
            }

            operations = pop_stack(operations, &expression[index]);
            index++;
            continue;
        }

        free_stack(operations);
        free_output(output);
        exit(1);
    }

    finish_operations(&operations, &output);
    return output;
}