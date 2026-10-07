#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "rpn.h"

static int valid_arguments(int argc, char **argv)
{
    if (argc == 1)
    {
        return 1;
    }

    if (argc == 2 && strcmp(argv[1], "-rpn") == 0)
    {
        return 1;
    }

    return 0;
}

static int read_input(char *buffer, size_t capacity)
{
    size_t length = 0;

    while (length < capacity - 1 && fread(&buffer[length], 1, 1, stdin) > 0)
    {
        length++;
    }

    buffer[length] = '\0';

    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
        length--;
    }

    if (length > 0 && buffer[length - 1] == '\r')
    {
        buffer[length - 1] = '\0';
    }

    return length != 0;
}

int main(int argc, char **argv)
{
    char expression[1024];
    struct output *output;
    int result;

    if (valid_arguments(argc, argv) == 0)
    {
        return 4;
    }

    if (read_input(expression, sizeof(expression)) == 0)
    {
        return 4;
    }

    if (argc == 2)
    {
        result = evaluate_rpn_text(expression);
    }
    else
    {
        output = parse_expression(expression);
        result = evaluate_rpn(output);
    }

    printf("%d\n", result);
    return 0;
}