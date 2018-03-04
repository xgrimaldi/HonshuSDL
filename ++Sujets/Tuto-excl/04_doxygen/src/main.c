/**
* \file main.c
* 
* Fichier pour tester deux implémentations de \b graphes.
* \author Dimitri Watel
* \date 02 mars 2018
*/


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/**
* \brief Fonction d'affichage d'un graphe.
*
* Cette fonction affiche un graphe sous la forme suivante : 
* - Une première ligne avec le nombre n de noeuds.
* - n lignes, une par noeud v, listant les voisins de v.
*
* \param g Graphe non orienté 
*/ 
void print_graph(graph g){
  printf("Nb nodes : %d\n", size(g));
  int i,j;
  for(i = 0; i < size(g); i++){
    printf("Voisins du noeud %d :", i);
    for(j = 0; j < size(g); j++)
      if(is_edge(g, i, j))
        printf("%d ", j);
    printf("\n");   
  }
}

int main(void){
  graph g = create_graph(4);
  add_edge(g, 0, 1); 
  add_edge(g, 0, 2); 
  add_edge(g, 0, 3); 
  add_edge(g, 2, 3); 
  add_edge(g, 3, 3); 

  remove_edge(g, 3, 3); 

  print_graph(g);
  free_graph(g);

  return EXIT_SUCCESS;
}
