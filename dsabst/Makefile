# -*- Makefile -*-

FLAGS = -Wall -g
LIBS=

OBJS = tree-bst-main.o bstree.o key_value.o
EXE = tree-bst-main
all : $(EXE)


tree-bst-main: $(OBJS)
	@echo "Building $@"
	@$(CC) -o $@ $(OBJS) $(LIBS) $(FLAGS)

tree-bst-main.o : tree-bst-main.c bstree.h
	@echo "Building $@"
	@$(CC) $(FLAGS) -c  tree-bst-main.c 

bstree.o : bstree.c bstree.h key_value.h
	@echo "Building $@"
	@$(CC) $(FLAGS)  -c bstree.c

key_value.o : key_value.c key_value.h
	@echo "Building $@"
	@$(CC) $(FLAGS) -c key_value.c



clean:
	rm -rf $(EXE) *.o *.dSYM *~


