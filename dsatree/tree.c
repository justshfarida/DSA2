#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "tree.h"
#include "queue.h"


/**
 * @brief maximum of 2 ints
 **/
int max(int a,int b) {
	  return(a>b ? a:b);
} 


/**
 ** @brief a simple DS for a tree node
 **/
struct node {
	  int       value;     /**< one value per node */
	  node      *lchild;   /**< the left child */
	  node      *rchild;   /**< the right child */
	  node_type ntype;     /**< to handle special nodes */
};

node* node_init(node* n, int val) {
	  if (n) {
		    /* Initializes the whole structure. */
		    *n = (node){
	                .value = val,
			        .lchild = 0,
			        .rchild = 0,
		    };
		    /* Here I easily forget one. */
		    // n->value = val;
		    // n->lchild = 0;
	  }
	  return n;
}

node* node_create(int val) {
	  node * ret = node_init(malloc(sizeof *ret), val);
	  return ret;
}

void node_delete(node* n) {
	  if (n) {
		    assert(!n->lchild);
		    assert(!n->rchild);
	  }
	  free(n);
}

node* node_insert(node *root, int val, direction dir) {
	  assert(root);

      // 
      //  complete
      // 
	  node* ret=node_create(val);
	  if(dir==0)
	  {
		ret->lchild=root->lchild;
		root->lchild =ret;
	  }
	  else if(dir==1)
	  {
		ret->rchild=root->rchild;
		root->rchild = ret;
	  }
	  return ret;
}

bool node_isinner(node *n) {
	  assert(n);
	  return (n->lchild || n->rchild) ;
}

bool node_isleaf(node *n) {
	  assert(n);
	  return !node_isinner(n);
}

node* tree_create_from_size(size_t n) {

    //
    // complete
    //
	
	if(n==0)
	{
		return NULL;
	}
	// if(((n+1)&n)==0)
	// {
	// 	return tree_create_from_size(n-1);
	// }
	int left_weight = n/2;
	int right_weight = n - left_weight;
	node* root=node_create(0);
	n--;
	root->lchild = tree_create_from_size(left_weight);
	root->rchild = tree_create_from_size(right_weight);
	return root;

}

/**
 * @brief create a balanced binary tree of height @a height from a given @a node
 * This is a helper function for tree_create.
 *
 * @return the root of the newly created tree
 **/
static
node *tree_create_from_height_rec (node *root, size_t height) {

    //
    // complete using 
    //    node_insert on the left
    //    node_insert on the right
    //    and calling recursively tree_create_from_height_rec on these nodes
    // 
	if(height == 0)
	{
		return NULL;
	}
	node *nodeleft =node_insert(root, 0, 0);
	node *noderight = node_insert(root, 0, 1);
	nodeleft->lchild = tree_create_from_height_rec(nodeleft->lchild, height-1);
	noderight->lchild = tree_create_from_height_rec(noderight->rchild, height-1);
	return nodeleft;
}

node *tree_create_from_height(size_t height) {
	  node *root;
	  if (0 == height)
		    return 0;
	  root = node_create(height);  /* we aribtrarily set the value in the node equal to the height */
	  return tree_create_from_height_rec(root, height-1);
}



void tree_delete(node* n) {
	  if (n) {
            //
            // complete
            // 
			tree_delete(n->lchild);
            tree_delete(n->rchild);
      }
      free(n);
}


size_t tree_height(node* root) {
	  size_t height = 0;
	  if (root) {

         //
         // complete
         //
		 size_t leftheight=tree_height(root->lchild);
		 size_t rightheight=tree_height(root->rchild);
		 height=1+max(leftheight,rightheight);

		 
	  }
	  return height;
}



size_t tree_size(node* root) {
	  size_t size = 0;
	  if (root) {

         //
         // complete
         //
		size_t leftsize=tree_size(root->lchild);
		size_t rightsize=tree_size(root->rchild);
		size=1+leftsize+rightsize;
	  }
	  return size;
}

static
void tree_print_rec(node* root, char const* pre) {
	  if (root) {
		    size_t depth = pre ? strlen(pre) : 0;
		    char npre[depth + 2];
		    if (pre) strcpy(npre, pre);
		    npre[depth + 1] = 0;

		    printf("%s%d\n", pre, root->value);
		    if (depth) npre[depth - 1] = '-';
		    npre[depth] = '>';
		    tree_print_rec(root->lchild, npre);
		    npre[depth] = '>';
		    tree_print_rec(root->rchild, npre);
	  }
}


/**
 * @brief Prints the the tree from node @a root
 **/
void tree_print(node* root) {
	  tree_print_rec(root, "");
}

/**
 * @brief Prints the the tree from node @a root
 **/
void tree_generic_print(void* root) {
node *Root = root;
	  tree_print(Root);
}


/**
 * @brief Performs a depthfirst visit of nodes (does no actual/useful action)
 **/

void tree_depthfirst_visit(node *n) {
	if (n) {
		tree_depthfirst_visit( n->lchild );
		tree_depthfirst_visit( n->rchild );
      }
}


/**
 * @brief Performs a breadthfirst visit of nodes (does no actual/useful action)
 **/
void tree_breadthfirst_visit(node *n) {
	  assert(n);
	  queue *q;
	  q = queue_create(fifo);
	  
	  while (n) {
		    if (n->lchild)
				queue_enqueue(q, n->lchild);
		    if (n->rchild)
			      queue_enqueue(q, n->rchild);

		    n = queue_dequeue(q); 
	  }    
	  queue_delete(q);
}


/**
 * @brief print the tree values in a breadth first traversal
 **/
void tree_breadthfirst_print(node *n) {
	  assert(n);
	  queue *q;
	  q = queue_create(fifo);
	  int level=1;
	  int nbnodes=0;

	  while (n) {
		    printf("[%d]  ",n->value);
		    if (n->lchild)
				queue_enqueue(q, n->lchild);
		    if (n->rchild)
			      queue_enqueue(q, n->rchild);
		    nbnodes= nbnodes+2;
		    n = queue_dequeue(q);
		    /* determine when to linebreak */
		    if (nbnodes==pow(2,level)) {
			  printf("\n");
			  nbnodes=0;
			  level++;
		   } 
	  }    
	  queue_delete(q);
}

/**
 * @brief Checks if a binary tree is complete (Perfect) using BFS.
 * @param root The root node of the tree.
 * @return True if the tree is complete, otherwise False.
 */
bool is_complete_tree(node *n) {
   
}
