#ifndef OUTPUT_H
#define OUTPUT_H

struct output
{
    int value;
    int is_number;
    char op;
    struct output *next;
};

struct output *push_output_number(struct output *out, int value);
struct output *push_output_op(struct output *out, char op);
void free_output(struct output *out);

#endif
