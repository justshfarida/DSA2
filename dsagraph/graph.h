/**
 * \file graph.h
 * \author Stephane Genaud
 */

#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stddef.h>
#include <stdbool.h>


/** 
  * A structure to represent an adjacency list 
 **/
typedef struct adj_node adj_node;
struct adj_node
{ 
    int id;   // an integer from 0 to max_number of vertices
    //int pred_id; // predecessor has a vertice number
    int weight;
    int d; // distance from source: used for graph visits
    adj_node* next;  
    //adj_node* pred;
}; 

typedef struct graph graph;

/**  
 * For search algorithms.
 * A struct where relevant information to BFS is stored for each node.
 * For a graph G=(V,E), we have an array of length |V|, each
 * array element pointing to a search_info struct. 
 **/
enum color_type {WHITE, GRAY, BLACK};

typedef struct info_node info_node;
struct info_node {
    int id;          //< vertex id
    size_t d;        //< distance from source in search
    enum color_type color; //< visited status, WHITE is unvisited
    int predecessor; //< a value of -1 means NIL
};

// ------------------ API ------------------------
/**
 * @brief Create a graph.
 * @details just alloc a `count` array for vertices, next step
 * is to add edges.
 * 
 * @param count number of vertices
 * @param undirected true for an undirected g., false for a digraph.
 */
graph *graph_create(size_t count, bool undirected);

/**
 * @brief clone the graph using new memory locations.
 * 
 * @param g 
 * @return the new graph*
 */
graph *graph_clone(graph *g);

/**
 * @brief free all memory allocated.
 * 
 * @param g 
 * @return graph* 
 */
graph *graph_delete(graph* g);

/**
 * @brief tell if a graph is undirected or not
 * 
 * @param g 
 * @return true if undirected, false if directed
 */
bool graph_is_undirected(graph *g);


/* NOT YET IMPLEMETED
graph* graph_add_vertex(graph* g, key node_key);
graph* graph_remove_vertex(graph* g, key node_key);
*/
/**
 * @brief Return the degree of a vertex of the graph
 * @param graph G=(V,E)
 * @param vertex_id an integer \in [O,..,|V|-1]
 * @return size_t 
 */
size_t graph_vertex_out_degree(graph *g, int vertex_id);

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
bool graph_add_edge(graph* g, int from, int to, int weight);

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
void graph_remove_edge(graph* g, int from, int to);

/**
 * @brief tell if an edge (from,to) exists
 * 
 * @param g 
 * @param from the source vertex
 * @param to the destination vertex
 * @return true if the edge exists, false otherwise 
 */
bool graph_has_edge(graph* g, int from, int to);

/**
 * @brief prints the graph to stdout in a simple graphviz format
 * 
 * @param g the graph
 */
void graph_print(graph* g);

/**
 * @brief prints the graph memory structure to stdout
 *
 * @param g the graph
 * @param detailed if true, prints predecessor info.
 */
void graph_print_struct(graph *g, bool detailed);

#endif // GRAPH_H_
