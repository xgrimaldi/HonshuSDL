#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph_s* graph;

graph create_graph(int size);
void free_graph(graph g);

int size(graph g);
void add_edge(graph g, int u, int v);
void remove_edge(graph g, int u, int v);
int is_edge(graph g, int u, int v);

#endif
