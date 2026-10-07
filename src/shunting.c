#include <stdlib.h>
#include "stack.h"
#include "output.h"
#include "utils.h"
#include "result.h"

/* shunting yard */
struct output *shunting_yard(char *expr)
{
    struct stack *ops = NULL;
    struct output *out = NULL;
    int i = 0;

    while (expr[i] != '\0')
    {
        if (expr[i] == ' ')
        {
            i++;
            continue;
        }

        if (is_number_start(expr, i))
        {
            int value = read_number(expr, &i);
            out = push_output_number(out, value);
            continue;
        }

        if (get_priority(expr[i]))
        {
            while (ops != NULL && ops->op != '(' &&
                  (get_priority(ops->op) > get_priority(expr[i]) ||
                  (get_priority(ops->op) == get_priority(expr[i]) && expr[i] != '^')))
            {
                char op;
                ops = pop_stack(ops, &op);
                out = push_output_op(out, op);
            }

            ops = push_stack(ops, expr[i]);
            i++;
            continue;
        }

        if (expr[i] == '(')
        {
            ops = push_stack(ops, expr[i]);
            i++;
            continue;
        }

        if (expr[i] == ')')
        {
            char op;

            while (ops != NULL && ops->op != '(')
            {
                ops = pop_stack(ops, &op);
                out = push_output_op(out, op);
            }

            if (ops == NULL)
            {
                exit(2);
            }

            ops = pop_stack(ops, &op);
            i++;
            continue;
        }

        exit(1);
    }

    while (ops != NULL)
    {
        char op;

        if (ops->op == '(')
        {
            exit(2);
        }

        ops = pop_stack(ops, &op);
        out = push_output_op(out, op);
    }

    return out;
}
