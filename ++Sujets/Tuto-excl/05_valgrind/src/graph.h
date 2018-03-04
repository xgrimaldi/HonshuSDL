
#ifndef GRAPH_H
#define GRAPH_H

/**
* \file graph.h
* 
* Interface pour le type graphe. Cette interface définit un type graph. 5 fonctions sont définies:
* - \b create_graph permet d'allouer de la mémoire et de créer un graphe à cet emplacement.
* - \b free_graph permet de libérer la mémoire relative à un graphe.
* - \b add_edge permet d'ajouter une arête au graphe
* - \b remove_edge permet de supprimer une arête au graphe
* - \b is_edge permet de vérifier si une arête est dans un graphe.
* - \b create_graph permet de créer un graphe
* - \b create_graph permet de créer un graphe
*/


/**
* \typedef graph
* Type représentant un graphe non orienté. Il est possible d'ajouter et de supprimer des arêtes de ces graphes. Enfin il est possible de demander 
*/
typedef struct graph_s* graph;

/**
* \brief Crée puis renvoie une graphe de taille \a size
*
* Alloue la mémoire nécessaire à la création d'un graphe de taille \a size, crée le graphe et le renvoie.
*
* \param size Taille du graphe souhaité.
* \return Un nouveau graphe de taille \a size.
*/
graph create_graph(int size);

/**
* \brief Libère la mémoire du graphe \a g
* \attention Le graphe g doit avoir été créé avec la fonction \a create_graph et ne doit pas déjà avoir été détruit avec la fonction \a free_graph.
* \param g Un graphe que l'on souhaite détruire.
*/
void free_graph(graph g);

/**
* \brief Renvoie la taille du graphe \a g
* \attention Le graphe g doit avoir été créé avec la fonction create_graph.
* \param g Un graphe.
* \return Le nombre de noeuds de \a g
*/
int size(graph g);


/**
* \brief Ajoute une arête entre les noeuds d'indices \a u et \a v dans le graphe \a g.
*
* Ajoute une arête entre les noeuds d'indices \a u et \a v dans le graphe \a g si cette arête n'existe pas déjà et ne fait rien sinon.
*
* \attention Le graphe g doit avoir été créé avec la fonction \a create_graph et ne doit pas déjà avoir été détruit avec la fonction \a free_graph. \a u et \a v doivent être entre 0 et la taille du graphe moins 1.
* \param g Un graphe.
* \param u L'indice d'un noeud du graphe \a g
* \param v L'indice d'un noeud du graphe \a g
*/
void add_edge(graph g, int u, int v);

/**
* \brief Retire une arête entre les noeuds d'indices \a u et \a v dans le graphe \a g.
*
* Retire une arête entre les noeuds d'indices \a u et \a v dans le graphe \a g si cette arête existe et ne fait rien sinon.
*
* \attention Le graphe g doit avoir été créé avec la fonction \a create_graph et ne doit pas déjà avoir été détruit avec la fonction \a free_graph. \a u et \a v doivent être entre 0 et la taille du graphe moins 1.
* \param g Un graphe.
* \param u L'indice d'un noeud du graphe \a g
* \param v L'indice d'un noeud du graphe \a g
*/
void remove_edge(graph g, int u, int v);

/**
* \brief Vérifie s'il existe une arête entre les noeuds d'indices \a u et \a v dans le graphe \a g.
*
* \attention Le graphe g doit avoir été créé avec la fonction \a create_graph et ne doit pas déjà avoir été détruit avec la fonction \a free_graph. \a u et \a v doivent être entre 0 et la taille du graphe moins 1.
* \param g Un graphe.
* \param u L'indice d'un noeud du graphe \a g
* \param v L'indice d'un noeud du graphe \a g
* \return 1 s'il existe une arête entre les noeuds d'indices \a u et \a v dans \a g et 0 sinon.
*/
int is_edge(graph g, int u, int v);
#endif
