/**
 *
 * file : queue-tree-main.c
 *
 * This file provide a main() function to test the queue data structure
 * with trees as values in the queues.
 *
 **/ 


#include <stdio.h>


/* N O T I C E
 * At compile-time, queue.h should be configured to store struct node as values.
 * See queue.h to check what symbol guards the definition
 *   typedef node queue_element_type;
 * (currently __QUEUES_OF_TREES__)
 *
 * Configuration is done through conditional compilation (using #ifdef symbols)
 * You might want to define the symbol at compile time :
 * gcc -D__QUEUES_OF_TREES__ tree.c queue.c queue-tree-main.c -o queue-tree-main
 */
#include "queue.h"
#include "tree.h"

int main() {

  printf("\n** Creating a single-node tree with tree_create_from_size(1) ...\n");
  node *mytree1 = tree_create_from_size(1);
  node *mytree2 = tree_create_from_size(2);
  node *mytree3 = tree_create_from_size(3);

  printf("\n** Creating FIFO queue ...\n");
  queue *myqueue = queue_create( fifo );


  printf("\n** Enquing a tree\n");
  queue_enqueue(myqueue, mytree1);

/*
 * Also, the queue_print() function should use the appropriate
 * print function, i.e here, one that can print an element of type tree
 * of the queue.
 */
 
  queue_print_generic(myqueue, tree_generic_print);
  printf("** Queue len:%zu\n",queue_length(myqueue));

  printf("\n** Enquing a tree\n");
  queue_enqueue(myqueue, mytree2);

  queue_print_generic(myqueue, tree_generic_print);
  printf("** Queue len:%zu\n",queue_length(myqueue));

  tree_delete(mytree1);
  tree_delete(mytree2);
  tree_delete(mytree3);

  queue_delete(myqueue);
}
