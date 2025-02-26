#ifndef __TREE_H__
#include <stdlib.h>
#include <stdbool.h>

typedef struct node node;

enum  direction { left, right };
typedef enum direction direction;

enum node_type { normal, empty };
typedef enum node_type node_type;

/**
 ** @brief initialize a node @a n with value @a val
 **
 ** @return @a n
 **
 ** Initializes all other fields to @c 0.
 **/
node* node_init(node* n, int val);

/**
 ** @brief create a new node with initial value @a val
 **/
node* node_create(int val);

/**
 ** @brief delete a node @a n
 **
 ** @pre both children must be empty
 **/
void node_delete(node* n);


/**
 ** @brief insert a new node at the @a dir side of @a root
 **
 ** If @a root already has a child @c x on that side, @c x becomes the
 ** child of the newly created node.
 **
 ** @return the newly created node.
 **/
node* node_insert(node *root, int val, direction dir);

/**
 ** @brief detect if @a n has at least one child
 **/
bool node_isinner(node *n);

/**
 ** @brief detect if @a n is a leaf
 **/
bool node_isleaf(node *n);


/**
 ** @brief create a new tree of size @a size
 ** Each node's value is set with the size of the tree rooted in this node.
 ** @return the root of the newly created tree. If @a height is 0, returns
 ** null.
 **/
node* tree_create_from_size(size_t size);
/**
 ** @brief create a balanced binary tree of @a height 
 ** Each node's value is set with the size of the tree rooted in this node.
 ** @return the root of the newly created tree. If @a height is 0, returns
 ** null.      
 **/
node *tree_create_from_height(size_t height);

/**
 ** @brief delete the whole tree pending at @a root
 **/
void tree_delete(node* root);

/**
 ** @brief compute the height of a tree
 **
 ** definition: height is the number of nodes on the longest branch.
 ** height of an empty tree is 0.
 **/
size_t tree_height(node* root);

/**
 ** @brief compute the number of nodes in a tree
 **/
size_t tree_size(node* root);

/**
 * @brief Tell if a tree is complete binary tree
 * 
 * @param n node to start with
 * @return true if the tree is complete
 * @return false otherwise
 */
bool is_complete_tree(node *n);


/**
 ** @brief pretty print a tree
 **/
void tree_print(node* root);
void tree_generic_print(void* root);


/**
 ** @brief Performs a depthfirst visit of nodes (does no actual/useful action)
 **/
void tree_depthfirst_visit(node *n);

/**
 ** @brief Performs a depthfirst visit of nodes (does no actual/useful action)
 **/
void tree_infix_visit(node *n);

/**
 ** @brief Performs a breadthfirst visit of nodes (does no actual/useful action)
 **/
void tree_breadthfirst_visit(node *n);
void tree_breadthfirst_print(node *n);


#define __TREE_H__
#endif
