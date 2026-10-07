#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct output *shunting_yard(char *expr);
int evaluate_rpn(struct output *out);

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        return 4;
    }

    if (argc == 2 && strcmp(argv[1], "-rpn") != 0)
    {
        return 4;
    }

    char buffer[1024];
    size_t i = 0;

    while (i < sizeof(buffer) - 1 && fread(&buffer[i], 1, 1, stdin) > 0)
    {
        i++;
    }

    buffer[i] = '\0';

    if (i == 0)
    {
        return 4;
    }

    if (buffer[i - 1] == '\n')
    {
        buffer[i - 1] = '\0';
    }

    if (buffer[0] == '\0')
    {
        return 0;
    }

    struct output *out = shunting_yard(buffer);
    int result = evaluate_rpn(out);

    printf("%d\n", result);

    return 0;
}
