#ifndef PARSER_H
#define PARSER_H

struct output;

struct output *shunting_yard(char *expression);

#endif /* ! PARSER_H */