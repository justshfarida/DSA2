CC=gcc
CFLAGS=-std=c11 -Wall -g 

EXE=queue-int-main 

QUEUE_SRC=queue.c 
QUEUE_HDR=queue.h

DSYMBOL_INT=__QUEUES_OF_INTS__

all: $(EXE)


queue-int-main: queue-int-main.c $(QUEUE_SRC) $(QUEUE_HDR) 
	$(CC) $(CFLAGS) -D$(DSYMBOL_INT) queue-int-main.c $(QUEUE_SRC) -o $@


SUFFIXES:.c .o

.c.o :
	$(CC) $(CFLAGS) -c $<


clean:
	rm -rf $(EXE) *.o *.dSYM *~ 
