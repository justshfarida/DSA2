/**
 * \file graph.c
 * \author Stephane Genaud
 */
#include "graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


struct graph {
    size_t count;  // number of vertices 
    bool undirected;
    adj_node** adj_list; // the start of the vertices list //array of linked lists' pointers
};

// private functions
static adj_node* adj_find_node(adj_node *start, int id, adj_node **pred);
static size_t adj_list_len(adj_node *head);
static adj_node *adj_node_clone(adj_node *orig);
static adj_node *adj_list_clone(adj_node *orig);


/**
 * @brief create a graph with `count` vertices
 * 
 * @param count the number of vertices
 * @param undirected if the graph is undirected of directed
 * @return graph* 
 */
graph * graph_create(size_t count, bool undirected) {
    graph* g = malloc(sizeof(graph));
    assert(g != 0);
    g->undirected = undirected;
    g->adj_list = calloc(count, sizeof(adj_node));
    g->count = count;
    return g;
}

// public
graph *graph_clone(graph *g) {
    assert(g);
    graph *g_cpy = malloc(sizeof(graph)); // the graph copy
    assert(g_cpy); 
    g_cpy->undirected = g->undirected;
    g_cpy->adj_list = calloc(g->count, sizeof(adj_node));
    g_cpy->count = g->count;
    for (size_t i=0; i<g->count; i++) {
        if (g->adj_list[i])
            g_cpy -> adj_list[i] = adj_list_clone(g->adj_list[i]);
    }
    return g_cpy;
}


/**
 * @brief delete the graph
 * 
 * @pre g is not null
 * @param g 
 * @return 0 
 */
graph *graph_delete(graph* g) {
    assert(g != 0);
    adj_node * current = g->adj_list[0];
    while (current) {
        adj_node* tmp = current->next;
        free(current);
        current = tmp->next;
    }
    free(g);
    return 0;
}


/**
 * @brief add an edge to the graph.
 * @details if the edge already exists,
 * @param g 
 * @param from the source vertex
 * @param to the destination vertex
 * @param weight 
 * @return true if the edge could be added (g is thus modified), 
 *         false otherwise (the edge already existed).
 */
bool graph_add_edge(graph *g, int from, int to, int weight) {
    adj_node* head = g->adj_list[from];
    adj_node* current;
    adj_node* prev = 0;
    /* test pointer to the adjacency list of node `from`. 
       Scan the list until we find a NULL pointer, at which
       point we add a node to the list.
    */

   // TO DO : use internal function find_lnode() to factorize code

    current = head; // if NULL in first place, this vertex has no edge
    while (current != 0 && current->id != to) {
        prev = current;
        current = current->next;
    }
    if (!current) { // we have reached end of adj_list
        current = malloc(sizeof(adj_node)); 
        assert(current);
        current->next = 0;
        current->id = to;
        current->weight = weight;

        if (prev) { // if an adj list already existed
            prev -> next = current;
        }
        else { // if the node was not connected
            g->adj_list[from] = current;
        }
    }
    else { // the edge already existed since we found the
           // `to` node in the adj list. 
        return false;
    }
    // Do the same symetrically if undirected
    // ....
    return true;
}

/**
 * @brief remove an edge
 * 
 * @details if we have A node n that has the following linkage n -> u -> v -> w
 *          means we have the vertices n->u, n->v and n->w. Removing
 *          an edge, e.g n->v means we just have to modify the linkage
 *          as n->u->w.
 * @param g the graph
 * @param from the source vertex
 * @param to   the destination vertex
 */
void graph_remove_edge(graph *g, int from, int to) {
    // Access the adjacency list for 'from'
    adj_node* head = g->adj_list[from];
    adj_node* current = head;
    adj_node* prev = NULL;

    if (head == NULL) {
        return; // No neighbors for 'from', nothing to remove
    }

    // If the first node is the one to remove
    if (current != NULL && current->id == to) {
        g->adj_list[from] = current->next; // Update head of the list
        current->next = NULL; // Disconnect the node
        free(current); // Free the node
        return;
    }

    // Traverse the list to find the node to remove
    while (current != NULL && current->id != to) {
        prev = current;
        current = current->next;
    }

    // If we found the node (i.e., current != NULL)
    if (current != NULL) {
        prev->next = current->next; // Remove the node from the list
        current->next = NULL; // Disconnect the node
        free(current); // Free the node
    }

    // If the graph is undirected, remove the reverse edge
    if (g->undirected) {
        graph_remove_edge(g, to, from); // Recursively remove reverse edge
    }
}


/**
 * @brief tell if an edge (from,to) exists
 * 
 * @param g 
 * @param from the source vertex
 * @param to the destination vertex
 * @return true if the edge exists, false otherwise 
 */
bool graph_has_edge(graph* g, int from, int to) {
    adj_node* current;

    if (from >= g->count) // node `from` exceed number of nodes in g
        return false;
    current = g->adj_list[from];
    while (current != 0) { 
        if (current->id == to) 
            return true;
        current = current->next;

    }
    return false;
}


/**
 * @brief Return the degree of a vertex of the graph
 * @param graph G=(V,E)
 * @param vertex_id an integer \in [O,..,|V|-1]
 * @return size_t 
 */
size_t graph_vertex_out_degree(graph *g, int vertex_id) {
    if (g->undirected) {
        fprintf(stderr, "* Error: out-degree only defined for digraphs.\n");
        exit(1);
    }
    assert(vertex_id < g->count); // vertex must belong to the graph
    if (g->adj_list[vertex_id]) {
        return adj_list_len(g->adj_list[vertex_id]);
    }
    else
        return 0; // no connected vertices
}

/**
 * @brief Return the degree of a vertex of the graph
 * @param graph G=(V,E)
 * @param vertex_id an integer \in [O,..,|V|-1]
 * @return size_t 
 */
size_t graph_vertex_degree(graph *g, int vertex_id) {
    if (!g->undirected) {
        fprintf(stderr, "* Error: vertices in digraph do not have a degree. Use in-/out-degree instead\n");
        exit(1);
    }
    assert(vertex_id < g->count); // vertex must belong to the graph
    return graph_vertex_out_degree(g, vertex_id); 
           //+ graph_vertex_in_degree(g, vertex_id); TO BE DONE
}


/**
 * @brief prints the graph to stdout in a simple graphviz format
 * 
 * @param g the graph
 */
void graph_print(graph* g) {
    adj_node * curr;
    char *edge_type[] = {"->", "--"};

    printf("digraph { #%ld nodes\n", g->count);
    for (int i=0; i<g->count; i++) {
        curr = g->adj_list[i];
        while (curr) {
            printf("%d %s %d;\n", i, edge_type[g->undirected], curr->id);
            curr = curr->next;
        }
    }
    printf("}\n");

}


void graph_print_struct(graph *g, bool detailed) {
    printf(">--------------------------------------------------------<\n");
    for (int i=0;i<g->count; i++) {
        adj_node * curr = g->adj_list[i];
        printf("%d : [%p]->\n", i, g->adj_list[i]);
        while (curr) {
            printf("\t%p [id=%d, next=%p", curr,curr->id, curr->next);
            printf("]\n");
            curr = curr->next;
        }
        printf("\tNULL\n");
    }
    printf(">--------------------------------------------------------<\n");
}

// ---------------- P R I V A T E -------------------

/**
 * @brief find the node with a given id.
 * 
 * @param start the a address of the first node to start
 * @param id an int 
 * @return 0 if not found, and predecessor is meaningless
 *         otherwise the address of the adj_node, and pred
 *         contains the address of the predecessor or NULL
 *         if the list has only one element.
 *         If the node found is the first of the linked list,
 *         pred is NULL.  
 */
// private
static adj_node* adj_find_node(adj_node *start, int id, adj_node **pred) {
    adj_node *current = start;
    *pred = 0 ;
    while (current != 0 ) {
        if (current->id == id) {
            return current; // early return the found node addr
        }
        *pred = current; // updated as soon as we've progressed beyond 1st elem 
        current = current->next;
    }
    return 0;
}

static size_t adj_list_len(adj_node *head) {
    size_t count = 0;
    while (head) {
        head = head-> next;
        count++;
    }
    return count;
}

// private
static adj_node *adj_node_clone(adj_node *orig) {
    adj_node *cpy = malloc(sizeof(adj_node));
    *cpy = (adj_node){.id = orig->id, \
                      .weight = orig->weight, \
                      .d = orig->d};
    return cpy;
}   


// private
static adj_node *adj_list_clone(adj_node *orig) {
    bool first = true;
    adj_node *head;
    adj_node *cpy = 0;
    adj_node *prev = 0;

    while (orig) {
        prev = cpy;
        cpy = adj_node_clone(orig);
        if (first) {
            first = false;
            head = cpy;
        }
        else {
            prev -> next = cpy;
        }
        orig = orig ->next; // progress in the original list
    }
    return head;
}
// Function to check if the graph is undirected
bool graph_is_undirected(graph *g) {
    return g->undirected;
}
