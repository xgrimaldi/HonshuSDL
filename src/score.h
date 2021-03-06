#include "struct.h"

#ifndef SCORE_H
#define SCORE_H


/**
* \brief renvoie le score atteint sur le plateau 
* 
*
* \param game la structure de jeu (Game*)
* \param ville un tableau permettant de récuperer les cordonnées des villes associées au plus grand village (int**)
* \param solv = 1 si c'est le solveur qui l'utilise, 0 sinon (int)
* \return le score atteint (int)
*/
int getScore(Game* game, int** ville, int solv, int* villageMax);

/**
* \brief Renvoie le nombre de carré de quatres cases contenu dans un village
*
* \param game 
* \param maxTown
* \param ville
*/	
int nombreCarre (Game* game, int maxTown, int** ville, int solv);

/**
* \brief Vérifie que la position x y est dans le plateau de jeu
*
*
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \param positions du plateau de jeu
* \param nbPos
* \return booleen
*/
int inPos(int x , int y, Position* positions,int nbPos);

/**
* \brief parcours le plateau de jeu afin de trouver le village associé à une ville
*
*
* \param game la structure de jeu (Game*)
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \param positions du plateau de jeu déjà traitées
* \param nbPos 
* \param ville un tableau permettant de récuperer les cordonnées des autres villes assovcié au plus grand village (int**)
* \param solv = 1 si c'est le solveur qui l'utilise, 0 sinon
* \param c un compteur servant à placer les villes dans ville dans l'ordre de leur parcours (int)
*/
int Add_Case_And_Check_Around(Game* game,char lettre,int x, int y,Position* positions,int* nbPos, int** ville, int solv, int c);

/**
* \brief impression des cordonnées des villes associées à une autre passée en paramètre se sont les coordonnées du village associé
*
* \param ville un tableau permettant de récuperer les cordonnées des villes assovcié au plus grand village (int**)
* \param n taille du village à imprimer
*/
void printVillage (int** ville, int n);

/**
* \brief Fonction d'impression d'un rappel des moyens de gagner des points
* \param variante la version des règles (int)
*/
void printRules (int variante);

#endif