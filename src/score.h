#include "struct.h"

#ifndef SCORE_H
#define SCORE_H


/**
* \brief renvoie le score atteint sur le plateau 
* 
*
* \param game la structure de jeu (Game*)
* \param ville un tableau permettant de récuperer les cordonnées des villes assovcié au plus grand village (int**)
* \return le score atteint (int)
*/
int getScore(Game* game,int** ville);

/**
* \brief Vérifie que la position x y est dans le plateau de jeu
*
*
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \param positons du plateau de jeu
* \param nbPos
* \return 
*/
int inPos(int x , int y, Position* positions,int nbPos);

/**
* \brief parcours le plateau de jeu afin de trouver le village associé à une ville
*
*
* \param game la structure de jeu (Game*)
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \param positons du plateau de jeu
* \param nbPos 
* \param ville un tableau permettant de récuperer les cordonnées des autres villes assovcié au plus grand village (int**)

*/
int Add_Case_And_Check_Around(Game* game,char lettre,int x, int y,Position* positions,int* nbPos, int** ville);

/**
* \brief impression des cordonnées des villes associées à une autre passée en paramètre se sont les coordonnées du village associé
*
* \param ville un tableau permettant de récuperer les cordonnées des villes assovcié au plus grand village (int**)
* \param n taille du village à imprimer
*/
void printVillage (int** ville, int n);

/**
* \brief Fonction d'impression d'un rappel des moyens de gagner des points.
*
*/
void printRules (void);

#endif
