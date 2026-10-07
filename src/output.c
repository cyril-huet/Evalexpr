#include "output.h"

#include <stdlib.h>

struct output *push_output_number(struct output *output, int value)
{
    struct output *new_output = malloc(sizeof(struct output));

    if (new_output == NULL)
    {
        return NULL;
    }

    new_output->value = value;
    new_output->is_number = 1;
    new_output->operation = '\0';
    new_output->next = output;

    return new_output;
}

struct output *push_output_operation(struct output *output, char operation)
{
    struct output *new_output = malloc(sizeof(struct output));

    if (new_output == NULL)
    {
        return NULL;
    }

    new_output->value = 0;
    new_output->is_number = 0;
    new_output->operation = operation;
    new_output->next = output;

    return new_output;
}

void free_output(struct output *output)
{
    struct output *next_output;

    while (output != NULL)
    {
        next_output = output->next;
        free(output);
        output = next_output;
    }
}