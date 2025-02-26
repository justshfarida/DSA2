#include <stdio.h>
#include <string.h>
#include "tree.h"


/* N O T I C E
 * queue.{c,h} is used for breadth-first traversal (e.g function 
 * tree_breadthfirst_print()). 
 * At compile-time, queue.h should be configured to store struct node as values.
 * See queue.h to check what symbol guards the definition
 *   typedef node queue_element_type;
 * (currently __QUEUES_OF_TREES__)
 *
 * Configuration is done through conditional compilation (using #ifdef symbols)
 * You might want to define the symbol at compile time :
 * gcc -D__QUEUES_OF_TREES__ tree.c tree-main.c queue.c -o tree-main
 */

#include "tree-examples.h"


int main (int argc, char ** argv){

  if (argc != 2) {
	    fprintf(stderr,"usage: %s <tree_size>\n",argv[0]);
	    exit(1);
  }
  size_t size = strtoul(argv[1], 0, 0);

  printf("\n** Testing tree creation with tree_create_from_size(%zu) ...\n",size);
  node *root = tree_create_from_size(size);

  printf("max tree size:\t%zu\n", tree_size(root));
  size_t height = tree_height(root);
  printf("max tree height:\t%zu\n", height);

  tree_print(root);
  tree_delete(root);


  printf("\n** Testing tree creation with tree_create_from_height(%zu) ...\n",height);
  root = tree_create_from_height(height);

  printf("max tree size:\t%zu\n", tree_size(root));
  printf("max tree height:\t%zu (should be %zu)\n", tree_height(root),height);

  tree_print(root);

  printf("------- Print in Breadth-First Order -------\n"); 
   
  tree_breadthfirst_print(root);
  
  printf("------- Print in Breadth-First Order -------\n"); 
  node *tree1 =  build_tree_1(); /* incomplete tree */
  node *tree2 =  build_tree_2(); /* incomplete tree */
  printf("\n** Testing is_complete_tree( tree1 ) ...");
  if (is_complete_tree(tree1) == false)
    printf(" OK.\n");
  else
    printf("KO.\n");
  printf("\n** Testing is_complete_tree( tree2 ) ...");
  if (is_complete_tree(tree2) == false)
    printf(" OK.\n");
  else
    printf("KO.\n");

  tree_delete(tree1);
  tree_delete(tree2);

  tree_delete(root);
}
