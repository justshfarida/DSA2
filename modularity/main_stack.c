#include <stdio.h>
#include "stack.h"

int main() {
    printf("Checking properties for stack\n");
    printf(">============================\n");
    printf("* is_empty(create()) \n   -> %s ... should be true\n", 
           is_empty(create()) ? "true" : "false");

    stack q = create();  // Initialize stack before using
    push(&q, 42);

    printf("* stack q;\n   push(&q, 42);\n   is_empty(q);\n   -> %s ... should be false\n", 
           is_empty(q) ? "true" : "false");

    return 0;
}
