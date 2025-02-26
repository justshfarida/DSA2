#include "stack.h"
#include "stream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Evaluates an arithmetic expression from a stream using Reverse Polish Notation (RPN).
 * @param stream The input stream (pointer to a stream).
 * @return The computed integer result, or an error code.
 */
int eval(stream *stream) {
    stack s = create();
    char *token;
    int val;

    while ((token = stream_get_token(stream)) != NULL) {
        if (sscanf(token, "%d", &val) == 1) {
            push(&s, val);
        } else if (strcmp(token, "+") == 0) {
            if (is_empty(s)) {
                fprintf(stderr, "Error: Stack underflow (not enough operands for '+')\n");
                return 1;
            }
            int a = pop(&s);

            if (is_empty(s)) {
                fprintf(stderr, "Error: Stack underflow (not enough operands for '+')\n");
                return 1;
            }
            int b = pop(&s);

            push(&s, a + b);
        } else {
            fprintf(stderr, "Error: Invalid token '%s'\n", token);
            return 1;
        }
    }

    if (is_empty(s)) {
        fprintf(stderr, "Error: No result computed (empty expression)\n");
        return 1;
    }

    int result = pop(&s);
    if (!is_empty(s)) {
        fprintf(stderr, "Error: Too many operands, invalid expression\n");
        return 1;
    }

    printf("Result: %d\n", result);
    return 0;
}
