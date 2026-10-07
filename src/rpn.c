#include "rpn.h"

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
    struct output *next;

    while (output != NULL)
    {
        next = output->next;
        output->next = previous;
        previous = output;
        output = next;
    }
    return previous;
}

static void push_value(struct result **results, int value)
{
    struct result *new_result = push_result(*results, value);

    if (new_result == NULL)
    {
        free_result(*results);
        exit(4);
    }
    *results = new_result;
}

static void apply_result(struct result **results, char operation)
{
    int right;
    int left;

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

    push_value(results, apply_operation(left, right, operation));
}

int evaluate_rpn(struct output *output)
{
    struct result *results = NULL;
    struct output *next_output;
    int value;

    output = reverse_output(output);

    while (output != NULL)
    {
        next_output = output->next;

        if (output->is_number == 1)
        {
            push_value(&results, output->value);
        }
        else
        {
            apply_result(&results, output->operation);
        }

        free(output);
        output = next_output;
    }

    if (results == NULL || results->next != NULL)
    {
        free_result(results);
        exit(1);
    }

    results = pop_result(results, &value);
    free_result(results);
    return value;
}

static void skip_spaces(char *expression, int *index)
{
    while (expression[*index] == ' ' || expression[*index] == '\t')
    {
        *index = *index + 1;
    }
}

static int is_number_token(char *expression, int index)
{
    if (is_digit(expression[index]) == 1)
    {
        return 1;
    }

    if ((expression[index] == '+' || expression[index] == '-')
        && is_digit(expression[index + 1]) == 1)
    {
        return 1;
    }

    return 0;
}

static int read_rpn_number(char *expression, int *index)
{
    int sign = 1;
    int value = 0;

    if (expression[*index] == '-')
    {
        sign = -1;
        *index = *index + 1;
    }
    else if (expression[*index] == '+')
    {
        *index = *index + 1;
    }

    while (is_digit(expression[*index]) == 1)
    {
        value = value * 10 + expression[*index] - '0';
        *index = *index + 1;
    }

    return value * sign;
}

static void add_rpn_token(struct output **output, char *expression, int *index)
{
    int value;
    char operation;

    if (is_number_token(expression, *index) == 1)
    {
        value = read_rpn_number(expression, index);
        *output = push_output_number(*output, value);
    }
    else if (get_priority(expression[*index]) != 0)
    {
        operation = expression[*index];
        *index = *index + 1;
        *output = push_output_operation(*output, operation);
    }
    else
    {
        exit(1);
    }

    if (*output == NULL)
    {
        exit(4);
    }
}

int evaluate_rpn_text(char *expression)
{
    struct output *output = NULL;
    int index = 0;

    skip_spaces(expression, &index);

    while (expression[index] != '\0')
    {
        add_rpn_token(&output, expression, &index);
        skip_spaces(expression, &index);
    }

    if (output == NULL)
    {
        exit(1);
    }

    return evaluate_rpn(output);
}