#ifndef TERM_H
#define TERM_H

#include <stdbool.h>

typedef struct term term;
term* string_to_term(char * s);
int is_constant(term * l);
int is_plus(term* l);
int val_constant(term * l);
void free_term(term * l);
#endif
