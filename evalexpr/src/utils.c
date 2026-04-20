#include <stdlib.h>
#include "utils.h"

/* check digit */
int is_digit(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }

    return 0;
}

/* operator priority */
int get_priority(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }

    if (op == '*' || op == '/' || op == '%')
    {
        return 2;
    }

    if (op == '^')
    {
        return 3;
    }

    return 0;
}

/* power */
int my_pow(int base, int exp)
{
    if (exp < 0)
    {
        exit(3);
    }

    if (exp == 0)
    {
        return 1;
    }

    if (exp % 2 == 0)
    {
        int tmp = my_pow(base, exp / 2);
        return tmp * tmp;
    }

    return base * my_pow(base, exp - 1);
}

/* detect number (with unary +/-) */
int is_number_start(char *expr, int i)
{
    if (is_digit(expr[i]))
    {
        return 1;
    }

    if ((expr[i] == '+' || expr[i] == '-')
        && (i == 0 || expr[i - 1] == '(' || get_priority(expr[i - 1])))
    {
        return 1;
    }

    return 0;
}

/* read full number */
int read_number(char *expr, int *i)
{
    int sign = 1;
    int value = 0;

    while (expr[*i] == '+' || expr[*i] == '-')
    {
        if (expr[*i] == '-')
        {
            sign *= -1;
        }
        (*i)++;
    }

    while (is_digit(expr[*i]))
    {
        value = value * 10 + (expr[*i] - '0');
        (*i)++;
    }

    return value * sign;
}
