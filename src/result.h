#ifndef RESULT_H
#define RESULT_H

struct result
{
    int value;
    struct result *next;
};

struct result *push_result(struct result *result, int value);
struct result *pop_result(struct result *result, int *value);
void free_result(struct result *result);

#endif /* ! RESULT_H */