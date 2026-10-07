#ifndef UTILS_H
#define UTILS_H

int is_digit(char character);
int get_priority(char operation);
int my_pow(int base, int exponent);

int is_number_start(char *expression, int index);
int read_number(char *expression, int *index);

#endif /* ! UTILS_H */