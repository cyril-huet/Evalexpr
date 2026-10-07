#ifndef RPN_H
#define RPN_H

struct output;

int evaluate_rpn(struct output *output);
int evaluate_rpn_text(char *expression);

#endif /* ! RPN_H */