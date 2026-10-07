#include <stdlib.h>

#include "output.h"
#include "result.h"
#include "utils.h"

static int apply_operation(int left, int right, char operation)
{
    if (operation == '+')
    {
        return left + right;
    }

    if (operation == '-')
    {
        return left - right;
    }

    if (operation == '*')
    {
        return left * right;
    }

    if (operation == '/')
    {
        if (right == 0)
        {
            exit(3);
        }

        return left / right;
    }

    if (operation == '%')
    {
        if (right == 0)
        {
            exit(3);
        }

        return left % right;
    }

    if (operation == '^')
    {
        return my_pow(left, right);
    }

    exit(1);
}

static struct output *reverse_output(struct output *output)
{
    struct output *previous = NULL;
    struct output *next_output;

    while (output != NULL)
    {
        next_output = output->next;
        output->next = previous;
        previous = output;
        output = next_output;
    }

    return previous;
}

static void push_value(struct result **results, int value)
{
    struct result *new_results = push_result(*results, value);

    if (new_results == NULL)
    {
        free_result(*results);
        exit(4);
    }

    *results = new_results;
}

static void apply_result(struct result **results, char operation)
{
    int right;
    int left;
    int value;

    if (*results == NULL)
    {
        exit(1);
    }

    *results = pop_result(*results, &right);

    if (*results == NULL)
    {
        exit(1);
    }

    *results = pop_result(*results, &left);
    value = apply_operation(left, right, operation);
    push_value(results, value);
}

int evaluate_rpn(struct output *output)
{
    struct result *results = NULL;
    struct output *current_output;
    int final_value;

    output = reverse_output(output);

    while (output != NULL)
    {
        current_output = output;
        output = output->next;

        if (current_output->is_number == 1)
        {
            push_value(&results, current_output->value);
        }
        else
        {
            apply_result(&results, current_output->operation);
        }

        free(current_output);
    }

    if (results == NULL || results->next != NULL)
    {
        free_result(results);
        exit(1);
    }

    results = pop_result(results, &final_value);
    return final_value;
}