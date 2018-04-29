#ifndef SOLVNAIF_H
#define SOLVNAIF_H


#include "struct.h"
#include "game.h"
#include "plateau.h"
#include "score.h"
#include "tuile.h"

/**
* \brief Copie un plateau dans un autre
*
* \param array le tableau copié (int**)
* \param copieArray le tableau dans lequel est copié array (int**)
* \param size la taille du tableau (int)
* 
*/
void copiePlateau(int** array, int** copieArray, int size);

/**
* \brief Copie un game dans un autre
*
* \param partie le game copié (Game*)
* \param copie le game dans lequel est copié partie (Game*)
* 
*/
void copieGame2(Game* partie,Game* copie);

/**
* \brief calcul le tableau des ids des tuiles disponibles
*
* \param gameTuiles le tableau de tuiles (Tuile*)
* \param nbTuiles nombre de tuile (int)
* \return le tableau des ids des tuiles disponibles (int*)
* 
*/
int* IdsTuilesDisponibles(Tuile gameTuiles[MAXTUILES],int nbTuiles);

/**
* \brief compare game et resu et met le Game de score maximal dans resu
*
* \param game un Game (Game*)
* \param resu le Game qui contiendra le resultat (Game*)
* \param ville un tableau pour pouvoir calculer le score (int**)
*
*/
int maxScore(Game* game,Game* resu,int** ville);

/**
* \brief met dans resultat le resultat des i prochains coups du solveur
*
* \param partie le Game sur lequel le solveur doit travailler (Game)
* \param resultat le Game qui contiendra le resultat (Game*)
* \param ville un tableau pour pouvoir calculer le score (int**)
* \param i le nombre d'anticipation (int)
*/
int solveurNaif(Game partie,Game* resultat, int i, int** ville);

/**
* \brief met dans resultat le resultat du solveur pour la pose de toute les tuiles
*
* \param partie le Game sur lequel le solveur doit travailler (Game)
* \param resultat le Game qui contiendra le resultat (Game*)
* \param ville un tableau pour pouvoir calculer le score (int**)
* \param n le nombre d'anticipation (int)
*/
int iterSolvNaif(Game partie, Game* resultat, int n, int** ville);


#endif
