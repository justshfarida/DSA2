#include "stream.h"
#include "evaluation.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Main function to evaluate an expression from a file.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 on success, 1 on error.
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    stream *s = stream_open(argv[1]);
    if (s == NULL) {
        fprintf(stderr, "Error: Unable to open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    int result = eval(s);
    stream_close(s);

    return result;
}
