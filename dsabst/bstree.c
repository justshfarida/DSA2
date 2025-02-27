/**
 * A tree data structure implementation with nodes containing a key,value pair
 *
 **/ 

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "bstree.h"
#include "key_value.h"

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
	  key       *k;
	  value 	*v;
	  node      *lchild;   /**< the left child */
	  node      *rchild;   /**< the right child */
	  node_type ntype;     /**< to handle special nodes */
	  int       unbalance; /**< to handle unblance in AVL trees */
};

node* node_init(node* n, key const *key, value const *value) {
  if (n) {
	    /* Initializes the whole structure. */
	    *n = (node){
			.k = key_create(key_string(key)),
			.v = value_create(value_string(value)),
			.lchild = 0,
			.rchild = 0,
		};
   }
   return n;
}

/**
 ** @brief create a new node with initial value @a val
 **/
node* node_create(key const *k, value const *v) {
	  node * ret = node_init(malloc(sizeof *ret), k, v);
	  return ret;
}



void node_delete(node* n) {
	  if (n) {
		    assert(!n->lchild);
		    assert(!n->rchild);
	  };
	  free(n);
}

node* node_insert(node *root, key const* k, value const *v, direction dir) {
	  assert(root);
	  node * ret = node_create(k,v);
	  if (dir == left) {
		    ret->lchild = root->lchild;
		    root->lchild = ret;
	  } else {
		    ret->rchild = root->rchild;
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


void tree_delete(node* n) {
	  if (n) {
		    tree_delete(n->lchild);
		    tree_delete(n->rchild);
		    n->lchild = 0;
		    n->rchild = 0;
		    node_delete(n);
	  };
}

size_t tree_height(node* root) {
	  size_t height = 0;
	  if (root) {
		    return max(1+tree_height(root->lchild),
				   1+tree_height(root->rchild));
	  }
	  return height;
}



size_t tree_size(node const* root) {
	  size_t size = 0;
	  if (root) {
		    size_t sl = tree_size(root->lchild);
		    size_t sr = tree_size(root->rchild);
		    size = sl + sr + 1;
	  }
	  return size;
}


/**
 ** @brief insert a key @k and value @v pair into a Binary Search Tree.
 **/
node *tree_bst_insert(node *root, key* const k, value* const v) {
	 //node *n=0;
    assert(root);  
	 /* specific case: a node with (k=0,v=0) 		   return root;
marks an initial node,
	  * replace its null values at first insertion.
	  * Might be set by a function e.g dict_create() 
	  **/ 
	 
	 if (node_isleaf(root) && !root->k && !root->v) {
		   root->k = k;
		   root->v = v;
	 }
	 int comp=key_cmp(k, root->k);
	 printf("k: %s; root->k: %s; comp: %d\n", k->key, root->k->key, comp);
	 /* normal case */
	  /* k < root->k, take left branch */
	 	if(comp<0)
		{
			if(root->lchild)
			{
				return tree_bst_insert(root->lchild, k, v);
			}
			else{
				printf("Inserted value %s at left of %s\n", k->key, root->k->key);
				node* new =node_create(k, v);
				root->lchild=new;
				return new;
			}
		}
      // ... to complete ...

	   /* k > root->k, take right branch */
	    else if(comp>0)
		{
			if(root->rchild)
			{
				return tree_bst_insert(root->rchild, k, v);
			}
			else{
				printf("Inserted value %s at right of %s\n", k->key, root->k->key);

				node* new =node_create(k, v);
				root->rchild=new;
				return new;
			}
		}

      // ... to complete ...
      //
	  return root;
}


/**
 ** @brief search a key @a k in a Binary Search Tree and return the associated value.
 **/
value *tree_bst_search(node *root, key* const k) {

    //
    // ... to complete ...
    //
	int comp=key_cmp(root->k, k);
	if(comp==0)
	{
		return root->v;
	}
	else if(comp<0)
	{
		if(root->rchild)
		{
			return tree_bst_search(root->rchild, k);
		}
		else{
			return NULL;
		}
	}
	else if(comp>0)
	{
		if (root->lchild)
		{
			return tree_bst_search(root->lchild, k);
		}
		else
		{
			return NULL;
		}
	}
}
				


static
void tree_print_rec(node* root, char const* pre) {
	  if (root) {
		    size_t depth = pre ? strlen(pre) : 0;
		    char npre[depth + 2];
		    if (pre) strcpy(npre, pre);
		    npre[depth + 1] = 0;

		    printf("%s(%s,%s)\n", pre, key_string(root->k), value_string(root->v));
		    if (depth) npre[depth - 1] = '-';
		    npre[depth] = '<';
		    tree_print_rec(root->lchild, npre);
		    npre[depth] = '>';
		    tree_print_rec(root->rchild, npre);
	  }
}

/**
 * @brief print the tree
 **/
void tree_print(node* root) {
	  tree_print_rec(root, "");
}

