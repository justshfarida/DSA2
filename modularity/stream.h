#ifndef STREAM_H
#define STREAM_H

#include <stdbool.h>

#define MAX_TOKEN_LENGTH 100

typedef struct stream_t stream;
stream * stream_open(char const * s);
void stream_close(stream * f);
char *stream_get_token(stream * f);
int end_of_file(stream  * f) ;

#endif
