#include "graph.h"
#include <stdbool.h>
#include <stdio.h>


int main(int argc, char **argv) {
    const size_t nb_vertices = 7;

    graph *g = graph_create(nb_vertices, false); // directed

    int weight = 1;
    graph_add_edge(g, 1, 2, weight);
    graph_add_edge(g, 1, 4, weight);
    graph_add_edge(g, 1, 6, weight);
    graph_add_edge(g, 4, 2, weight);
    graph_add_edge(g, 2, 5, weight);
    graph_add_edge(g, 3, 5, weight);
    graph_add_edge(g, 3, 6, weight);
    graph_add_edge(g, 6, 6, weight);

    graph_print_struct(g, false);
    graph_print(g);

    // test out-degree, only for digraphs
    if (graph_is_undirected(g)) {
        for (size_t i=0; i<nb_vertices;i++) {
            printf("* out_degree(%ld) = %ld\n", i, graph_vertex_out_degree(g, i));
        }
    }

    // test edge existence
    printf("Does edge 1-5 exists?  %d\n", graph_has_edge(g, 1, 5));
    printf("Does edge 1-4 exists?  %d\n", graph_has_edge(g, 1, 4));

    printf("* removing edge 1->4 ...\n");
    graph_remove_edge(g, 1,4);
    graph_print_struct(g, false);

    printf("* removing edge 1->2 ...\n");
    graph_remove_edge(g, 1,2);
    graph_print_struct(g, false);

    printf("* removing edge 1->6 ...\n");
    graph_remove_edge(g, 1, 6);
    graph_print_struct(g, false);

    printf("1-4: %d\n", graph_has_edge(g, 1, 4));


    // // Test clone of graph
    // graph *h = graph_clone(g);
    // printf("\n* Testing cloning g. The clone graph is:\n");
    // graph_print_struct(h, true);

    return 0;
}