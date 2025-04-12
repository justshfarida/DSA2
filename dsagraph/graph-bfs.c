/**
 * \file graph-bfs.c
 * \author Stephane Genaud
 */

#include "graph.h"
#include "queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// opaque structure (we keep it in the implementation)
struct graph {
    size_t count;       //< number of vertices 
    bool undirected;    //< is it an undirected graph
    adj_node** adj_list;//< the start of the vertices list
};

/**
 * @brief Perform a BFS from a given `source` vertex 
 * 
 * @details in the following every variable name finishing in `_id`
 * are integers that identify vertices.
 * 
 * @param g The graph.
 * @param source an integer
 * @return pointer to the info_node computed 
 */
info_node  *graph_bfs(graph *g, int source) {
    assert(g);                  // non-empty graph
    assert(source < g->count);  // s must belong to graph's vertices

    // we use an auxiliary struct to store info during the search
    // info_arr[i] contains info on vertex i \in [O,..,g.count-1]
    info_node *info_arr = malloc(g->count * sizeof(info_node)); 
    // We will need a queue of node_info elements
    queue *q = queue_create(fifo);
    
    // for each vertex u \in g.V - {source}
    for (int i=0; i<g->count; i++) {
        // initialize all node info excepted source
        if (i != source) {
            info_arr[i] = (info_node)\
                {.id = i, .predecessor = -1, .color = WHITE, .d=__INT_MAX__};
        }
    }
    // initialize info for the source vertex
    info_arr[source] = (info_node)\
                {.id = source, .predecessor=-1, .color = GRAY, .d = 0 };
    queue_enqueue(q, &(info_arr[source]) );

    // Now process iteratively the nodes in queue
    while (!queue_isempty(q)) {
        info_node *u = queue_dequeue(q);
        // Now find all nodes in adjacency list for vertex u :
        // for each vertex v \in g.Adj[u] do
        adj_node *v = g->adj_list[u->id];

        while (v) {
            int info_v_id = v->id;
            printf("->v exists : %d, color=%d\n", v->id, info_arr[info_v_id].color);
            // lookup and update vertex properties in info_node
            if (info_arr[info_v_id].color == WHITE) {
                printf("-> set color to GRAY\n");
                info_arr[info_v_id].color = GRAY;
                info_arr[info_v_id].d = u->d + 1;
                info_arr[info_v_id].predecessor = u->id;
                queue_enqueue(q, &(info_arr[info_v_id]));
            }
            v = v->next; // Move to next neighbor of u
        }
        u->color = BLACK;
    }
    return info_arr;
}


// Should be better to store count into the info_node
static void print_node_info(info_node *arr, size_t count) {
    printf(">---------------------------------------------------\n");
    for (size_t i=0; i<count; i++){
        printf("> id=%d predecessor=%d color=%d, d=%ld\n", 
            arr[i].id, arr[i].predecessor, arr[i].color, arr[i].d);
    }
    printf(">---------------------------------------------------\n");
}
/**
 * @brief 
 * 
 * @param info_arr the struct constructed by BFS
 * @param s 
 * @param v 
 */
void print_path(info_node *info_arr, int s, int v) {
    if (v == s)
        printf("%d ", s);
    else {
        if (info_arr[v].predecessor == -1)
            printf("No path from %d to %d\n", s, v);
        else {
            print_path(info_arr, s, info_arr[v].predecessor);
            printf("%d ", v);
        }
    }
    printf("\n");
}

/**
 */
int main(int argc, char **argv) {

    int weight = 1;
    // create a graph with 6 vertices {0, .., 5}
    graph *g = graph_create(6, false); // directed
    graph_add_edge(g, 0, 1, weight);
    graph_add_edge(g, 1, 2, weight);
    graph_add_edge(g, 2, 3, weight);
    graph_add_edge(g, 1, 4, weight);
    graph_add_edge(g, 4, 3, weight);
    graph_add_edge(g, 3, 5, weight);
    graph_add_edge(g, 4, 5, weight);
    
    // Small
    /*
    graph_add_edge(g, 0, 1, weight);
    graph_add_edge(g, 1, 2, weight);
    graph_add_edge(g, 2, 3, weight);
    // create a shortcut
    graph_add_edge(g, 1, 3, weight);
    */

    graph_print(g);

    graph_print_struct(g, true);

    printf("* Performing BFS ...\n");
    const int source = 0;
    const int dest = 5;
    info_node* search_info = graph_bfs(g, source);

    printf("* Printing shortest path from %d to %d ...\n", source, dest);
    print_node_info(search_info, g->count);
    print_path(search_info, source, dest);

    return 0;
}
