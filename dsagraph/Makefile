
TARGET1 = graph-main
TARGET2 = graph-bfs
TARGETS = $(TARGET1) $(TARGET2)

CFLAGS = -Wall  -g -std=c99
LDFLAGS= -lm

# Incomplete list, these are the files given to students
DIST_FILES = graph.h\
		     graph.c\
			 queue.h\
			 queue.c\
			 graph-main.c\
			 Makefile

GRAPH_SRC=graph.c
GRAPH_HDR=graph.h
QUEUE_SRC=queue.c
QUEUE_HDR=queue.h
DSYMBOL_QUEUE=__QUEUES_OF_ADJNODES__  # to configure queues to store adj_nodes


all : $(TARGETS)

$(TARGET1) : $(GRAPH_HDR) $(TARGET1).c
	@echo "Building $@"
	$(CC) $(CFLAGS) $(GRAPH_SRC) $(TARGET1).c -o $@

$(TARGET2): $(TARGET2).c $(GRAPH_HDR) $(QUEUE_HDR) 
	@echo "Building $@"
	$(CC) $(CFLAGS) $(TARGET2).c $(GRAPH_SRC) $(QUEUE_SRC) -o $@


SUFFIXES:.c .o

.c.o :
	$(CC) $(CFLAGS) -c $<


clean :
	@rm -f $(TARGETS) *.o *~
	@rm -rf *.dSYM


dist: $(DIST_FILES)
	@echo "* creating $(DIR)"
	@rm -rf $(DIR)
	@mkdir $(DIR)
	@cp $(DIST_FILES) $(DIR)
	@tar cvfz $(DISTNAME) $(DIR)
	@rm -rf $(DIR)
	@echo "* -> $(DISTNAME) built."
