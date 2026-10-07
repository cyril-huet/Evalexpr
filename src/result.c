#include "result.h"

#include <stdlib.h>

struct result *push_result(struct result *result, int value)
{
    struct result *new_result = malloc(sizeof(struct result));

    if (new_result == NULL)
    {
        return NULL;
    }

    new_result->value = value;
    new_result->next = result;

    return new_result;
}

struct result *pop_result(struct result *result, int *value)
{
    struct result *next_result;

    if (result == NULL)
    {
        return NULL;
    }

    *value = result->value;
    next_result = result->next;
    free(result);

    return next_result;
}

void free_result(struct result *result)
{
    struct result *next_result;

    while (result != NULL)
    {
        next_result = result->next;
        free(result);
        result = next_result;
    }
}