#include <stdlib.h>
#include "output.h"
#include "result.h"
#include "utils.h"

/* apply operation */
static int apply_op(int a, int b, char op)
{
    if (op == '+') { return a + b; }
    if (op == '-') { return a - b; }
    if (op == '*') { return a * b; }

    if (op == '/')
    {
        if (b == 0) { exit(3); }
        return a / b;
    }

    if (op == '%')
    {
        if (b == 0) { exit(3); }
        return a % b;
    }

    if (op == '^')
    {
        return my_pow(a, b);
    }

    return 0;
}

/* reverse list */
static struct output *reverse(struct output *out)
{
    struct output *prev = NULL;

    while (out != NULL)
    {
        struct output *next = out->next;
        out->next = prev;
        prev = out;
        out = next;
    }

    return prev;
}

/* evaluate RPN */
int evaluate_rpn(struct output *out)
{
    struct result *res = NULL;
    struct output *cur = reverse(out);

    while (cur != NULL)
    {
        if (cur->is_number)
        {
            res = push_result(res, cur->value);
        }
        else
        {
            int b;
            int a;

            res = pop_result(res, &b);
            res = pop_result(res, &a);

            res = push_result(res, apply_op(a, b, cur->op));
        }

        struct output *tmp = cur;
        cur = cur->next;
        free(tmp);
    }

    int final;
    res = pop_result(res, &final);

    return final;
}
