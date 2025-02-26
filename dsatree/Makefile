CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lm
EXE=queue-int-main queue-tree-main tree-main

TREE_SRC=tree.c 
TREE_HDR=tree.h
QUEUE_SRC=queue.c 
QUEUE_HDR=queue.h

DSYMBOL_INT=__QUEUES_OF_INTS__
DSYMBOL_TREE=__QUEUES_OF_TREES__

all: $(EXE)


queue-int-main: queue-int-main.c $(QUEUE_SRC) $(QUEUE_HDR) 
	$(CC) $(CFLAGS) -D$(DSYMBOL_INT) queue-int-main.c $(QUEUE_SRC) -o $@

queue-tree-main: queue-tree-main.c $(QUEUE_SRC) $(QUEUE_HDR) 
	$(CC) $(CFLAGS) -D$(DSYMBOL_TREE) queue-tree-main.c $(QUEUE_SRC) $(TREE_SRC) -o $@ $(LDFLAGS)

tree-main: tree-main.c $(TREE_SRC) $(TREE_HDR) $(QUEUE_SRC) 
	$(CC) $(CFLAGS) -D$(DSYMBOL_TREE) tree-main.c $(QUEUE_SRC) $(TREE_SRC) -o $@ $(LDFLAGS)



SUFFIXES:.c .o

.c.o :
	$(CC) $(CFLAGS) -c $<


clean:
	rm -rf $(EXE) *.o *.dSYM *~ 
