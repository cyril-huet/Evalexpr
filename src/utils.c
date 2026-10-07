#include "utils.h"

#include <stdlib.h>

int is_digit(char character)
{
    if (character >= '0' && character <= '9')
    {
        return 1;
    }

    return 0;
}

int get_priority(char operation)
{
    if (operation == '+' || operation == '-')
    {
        return 1;
    }

    if (operation == '*' || operation == '/' || operation == '%')
    {
        return 2;
    }

    if (operation == '^')
    {
        return 3;
    }

    return 0;
}

int my_pow(int base, int exponent)
{
    int result = 1;
    int index = 0;

    if (exponent < 0)
    {
        exit(3);
    }

    for (index = 0; index < exponent; index++)
    {
        result = result * base;
    }

    return result;
}

int is_number_start(char *expression, int index)
{
    if (is_digit(expression[index]) == 1)
    {
        return 1;
    }

    if (expression[index] != '+' && expression[index] != '-')
    {
        return 0;
    }

    if (index == 0 || expression[index - 1] == '(')
    {
        return 1;
    }

    if (get_priority(expression[index - 1]) != 0)
    {
        return 1;
    }

    return 0;
}

int read_number(char *expression, int *index)
{
    int sign = 1;
    int value = 0;

    while (expression[*index] == '+' || expression[*index] == '-')
    {
        if (expression[*index] == '-')
        {
            sign = sign * -1;
        }

        *index = *index + 1;
    }

    while (is_digit(expression[*index]) == 1)
    {
        value = value * 10 + expression[*index] - '0';
        *index = *index + 1;
    }

    return value * sign;
}