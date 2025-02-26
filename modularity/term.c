#include "term.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum type { CST, PLUS };

struct term {
  enum type t;
  int val;
};

term* string_to_term(char * s) {
  term * r = malloc(sizeof *r);
  if (strcmp(s, "+") == 0) {
    r->t = PLUS;
  }
  else {
    char * rest;
    int i = strtol(s, &rest, 0);
    if (rest == s) {
      fprintf(stderr, "Operator '%s' not recognized.\n", s);
      exit(1);
    }
    r->t = CST;
    r->val = i;
  }
  return r;
}

int is_constant(term * l) {
  return (CST == l->t);
}

int is_plus(term* l) {
  return (PLUS == l->t);
}

int val_constant(term * l) {
  return (l->val);
}

void free_term(term * l) {
  free(l);
}
