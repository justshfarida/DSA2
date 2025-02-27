#include <stdio.h>
#include <string.h>
#include "bstree.h"
#include "key_value.h"

#define MAX_TEXT_LEN 64

int main (int argc, char ** argv){

  /*
   * We are going tp create key-value pairs based on a letter 
   * For key "A", associated value is "val of A".
   */
  //char * letters[] = {"D","A","B","G","H","E"};
  //char * letters[] = {"J","F","D","I","G","M","O","W","P","U","Z"};
  char * letters[] = {"J","F","D","I","G","M","L","O","W","P","U","Z"};

  //char * letters[] = {"J","F","D","I","G","M","O","Q"};

  //char * letters[] = {"J","F","D","I","G","M","O","K"};

  //char * letters[] = {"D","E","A"};

  /**
   *       D
   *     /   \
   *    A     G
   *     \   / \
   *      B E   H
   *
   **/
  size_t size = sizeof(letters)/sizeof(letters[0]);

  //------------------------------------------------------
  printf("== 1. test insert\n");

  printf("* %zu elements to insert ...\n", size);
  node *root = node_create(0,0);
  // insert a kv into the BST
  for (size_t i=0; i < size; i++) {
      // make a string depending on the letter
      char vtext[MAX_TEXT_LEN] = "val of ";
      strncat(vtext,letters[i],MAX_TEXT_LEN);
      // insert kv 
      printf("  - key:%s\n", letters[i]);
      printf("%s\n", letters[i]);
      tree_bst_insert(root, key_create(letters[i]), value_create(vtext));
     
  }

  //------------------------------------------------------
  printf("\n== 2. tree_print\n");
  tree_print(root);


  //------------------------------------------------------
  char input [20];
  printf("\n== 3. search\n");
  printf("* type in one character to retrieve its value:");
  scanf("%[^\n]s", input);
  value *v = tree_bst_search(root, key_create(input));
  if (v != 0) {
    printf("* found : %s\n", value_string(v));
  }
  else
    printf("* not found\n");


  /* to test bst_min_key() individually*/
  /* printf("\n == 3'. min\n");
  key *k = tree_bst_min_key(root);
  printf("min key=%s\n", key_string(k));
  */

  //------------------------------------------------------
  printf("\n== 4. deletion\n");
  printf("* type in the key for the node to delete:");

  scanf(" %[^\n]s", input);  
  // root = tree_bst_delete(root, key_create(input));
  tree_print(root);

  tree_delete(root);
  return 0;
}
