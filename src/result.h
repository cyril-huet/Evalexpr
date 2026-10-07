#ifndef RESULT_H
#define RESULT_H

struct result
{
    int value;
    struct result *next;
};

struct result *push_result(struct result *res, int value);
struct result *pop_result(struct result *res, int *value);
void free_result(struct result *res);

#endif
