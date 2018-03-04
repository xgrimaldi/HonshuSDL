#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct edge{
  int u;
  int v;
};

struct graph_s{
  int size;
  int nbedges;
  struct edge * edges;
};

typedef struct graph_s* graph;

graph create_graph(int size){
  graph g = (graph) malloc(sizeof(struct graph_s));
  g->size = size;
  g->nbedges = 0;
  g->edges = (struct edge *) malloc(sizeof(struct edge) * size * size);
  return g;
}


void free_graph(graph g){
  free(g->edges);
  free(g);
}

int size(graph g){
  return g->size;
}

void add_edge(graph g, int u, int v){
  if(is_edge(g, u, v) == 1)
    return;
  
  if(0 <= u && u < g->size && 0 <= v && v < g->size){
    g->edges[g->nbedges].u = u;
    g->edges[g->nbedges].v = v;
    g->nbedges += 1;
  }
}


void remove_edge(graph g, int u, int v){
  int i;
  int remove_index = -1;

  for(i = 0; i < g->nbedges; i++){
    struct edge e = g->edges[i];
    if((e.u == u && e.v == v ) || (e.u == v && e.v == u)){
      remove_index = i;
      break;
    }
  }

  if(remove_index == -1)
    return;
  
  g->edges[remove_index].u = g->edges[g->nbedges - 1].u;
  g->edges[remove_index].v = g->edges[g->nbedges - 1].v;

  g->nbedges -= 1;
}


int is_edge(graph g, int u, int v){
  int i;
  for(i = 0; i < g->nbedges; i++){
    struct edge e = g->edges[i];
    if((e.u == u && e.v == v ) || (e.u == v && e.v == u))
      return 1;
  }
  return 0;
}


