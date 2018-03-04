#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define SIZEMAX 1000


struct graph_s{
  int edges[SIZEMAX][SIZEMAX];
  int size;
};

typedef struct graph_s* graph;

graph create_graph(int size){
  graph g = (graph) malloc(sizeof(struct graph_s));

  int i, j;
  for(i = 0; i < size; i++){
    for(j = 0; j < size; j++){
      g->edges[i][j] = 0;
    }
  }

  g->size = size; 
  return g;
}


void free_graph(graph g){
  free(g);
}

int size(graph g){
  return g->size;
}

/**
* \internal
* Complexité en O(1)
*/
void add_edge(graph g, int u, int v){
  if(0 <= u && u < g->size && 0 <= v && v < g->size){
    g->edges[u][v] = 1;
    g->edges[v][u] = 1;
  }
}


void remove_edge(graph g, int u, int v){
  if(0 <= u && u < g->size && 0 <= v && v < g->size){
    g->edges[u][v] = 0;
    g->edges[v][u] = 0;
  }
}


int is_edge(graph g, int u, int v){
  if(0 <= u && u < g->size && 0 <= v && v < g->size && g->edges[u][v] == 1)
    return 1;
  else
    return 0;
}


