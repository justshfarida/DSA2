#include "stream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct stream_t {
  FILE *fp;
};

stream * stream_open(char const * s) {
  // stream r = malloc(sizeof(struct stream_t));//changed from   stream * r = malloc(sizeof *r);
  stream  *r=malloc(sizeof *r);
  r->fp = fopen(s, "r");
  if (!r->fp) 
      fprintf(stderr, "Error: can't open file %s\n", s);
  return r;
}

void stream_close(stream * f) {
  fclose(f->fp);
  free(f);
}


char *stream_get_token(stream * f) {
    // Static variables to maintain state between function calls
    static char buffer[MAX_TOKEN_LENGTH];
    static int index = 0;
    static bool is_first_call = true;

    // If it's the first call, read the input from input stream
    if (is_first_call) {
        fgets(buffer, sizeof(buffer), f->fp);
        is_first_call = false;
    }
    // Token extraction logic
    char * token = strtok(buffer + index, " \n");

    // If there are no more tokens, reset the state for the next call
    if (token == NULL) {
        is_first_call = 1;
        index = 0;
    } 
    else {
        index += strlen(token) + 1;
    }
    return token;
}



int end_of_file(stream *f) {
  return feof(f->fp);
}
//gcc -c stream.c -o stream.o manually compling stream file
//gcc -o evaluate stack.o stream.o term.o evaluation.o main.o links all compiled files into one executable file "evaluate:"

