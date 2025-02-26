/**
 * Stack implementation
 * DSA2 UFAZ course
 * S. Genaud
 **/

#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

struct stack_t {
  int val;
  stack next;
};

stack create(void) {
  return 0;
}

bool is_empty(stack s) {
  return (0 == s);
}

void push(stack * sp, int v) {
  stack r = malloc(sizeof * r);
  r->val = v;
  r->next = *sp;
  *sp = r;
}

int pop(stack * sp) {
  assert(*sp != NULL);
  stack tmp;
  int r = (*sp)->val;
  tmp = (*sp)->next;
  free(*sp);
  *sp = tmp;
  return r;
}

