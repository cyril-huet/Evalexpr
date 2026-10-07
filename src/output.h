#ifndef OUTPUT_H
#define OUTPUT_H

struct output
{
    int value;
    int is_number;
    char operation;
    struct output *next;
};

struct output *push_output_number(struct output *output, int value);
struct output *push_output_operation(struct output *output, char operation);
void free_output(struct output *output);

#endif /* ! OUTPUT_H */