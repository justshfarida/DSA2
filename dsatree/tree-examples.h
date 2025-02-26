#include "tree.h"
/*
 *
 */
node *build_tree_1() {
  /** tree 1 (incomplete)
   *      1
   *     / \
   *    2   5
   *   / \
   *  3   4
  **/
  node *n1 = node_create(1);
  node *n2 = node_insert(n1, 2, left);
  node_insert(n2, 3, left);   // 3
  node_insert(n2, 4, right);  // 4
  node_insert(n1, 5, right);  // 5 
  return n1;
}

/*
 *
 */
node *build_tree_2() {
  /** tree 2 (incomplete)
   *      1
   *     / \
   *    2   5
   *   / \   \
   *  3   4   6
  **/
  node *n1 = node_create(1);
  node *n2 = node_insert(n1, 2, left);
  node_insert(n2, 3, left);      // 3
  node_insert(n2, 4, right);     // 4
  node *n5 = node_insert(n1, 5, right);
  node_insert(n5, 6, right);     // 6

  return n1;
}
