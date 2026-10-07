#include <stdlib.h>
#include "result.h"

/* free result stack */
void free_result(struct result *res)
{
    while (res != NULL)
    {
        struct result *tmp = res;
        res = res->next;
        free(tmp);
    }
}

/* push value */
struct result *push_result(struct result *res, int value)
{
    struct result *node = malloc(sizeof(struct result));

    if (node == NULL)
    {
        return NULL;
    }

    node->value = value;
    node->next = res;

    return node;
}

/* pop value */
struct result *pop_result(struct result *res, int *value)
{
    struct result *next;

    if (res == NULL)
    {
        return NULL;
    }

    *value = res->value;
    next = res->next;

    free(res);

    return next;
}
