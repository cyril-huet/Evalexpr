#ifndef UTILS_H
#define UTILS_H

int is_digit(char c);
int get_priority(char op);
int my_pow(int base, int exp);

int is_number_start(char *expr, int i);
int read_number(char *expr, int *i);

#endif
