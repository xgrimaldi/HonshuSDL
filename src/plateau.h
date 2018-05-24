/**
* \file plateau.h
* 
* Création des paramètres HONSHU. 5 fonctions sont définies:
* - \b alloc_int_array alloue un pointeur int**
* - \b initPlateau initialise le plateau de jeu.
* - \b initPlacementTuileRandom initialise les tuiles de facon aléatoire
* - \b initPlacementTuile initialise le placement d'une tuile
* - \b printPlateau affiche le plateau de jeu
* - \b printCase return une case du plateau
* - \b printData affiche plateau et tuiles paramétrées
* - \b copieNBCasesRec gestion des copies de cases
* - \b retablishNBCasesRec rétabli les anciennes valeurs
* - \b testRecouvrementTotal test qui permet de vérifier si une tuile est recouverte totalement
* - \b inPlateau vérifie si une coordonnée est dans un plateau
* - \b savePlateau sauvegarde le plateau de la partie
* - \b getPrevious récupère le plateau précédent
* - \b matchEmpty Vérifie l'absence de tuiles
*/

#ifndef PLATEAU_H
#define PLATEAU_H

#include "struct.h"
#include "game.h"
#include "tuile.h"

/**
* \brief Alloue un triple pointeur de char de taille \a x  * \a y
*
* \param x La taille du premier pointeur (int**)
* \param y La taille du deuxième pointeur (int*) 
* \return Un int **
*/
int **alloc_int_array(int x, int y);



/**
* \brief Initialise le plateau de jeu
*
* \param val Est la valeure que va contenir toutes les cases du plateau
*/
void initPlateau(int** gamePlateau,int taille, int val);

/**
* \brief Positionne une tuile aléatoirement
*
* Positionne une tuile au hasard au milieu du plateau
*
* \param partie variable représentant une partie (structure Game).
*/
void initPlacementTuileRandom(Game* partie);

/**
* \brief Positionne la tuile souhaitée
*
* Positionne une tuile au hasard au milieu du plateau
*
* \param partie variable représentant une partie (structure Game).
* \param numTuile vnuméro de la tuile à placer
*/
void initPlacementTuile(Game* partie,int numTuile);

/**
* \brief Affiche le plateau de jeu \a g
* \attention Au début du programme, un plateau vide est crée (composé que de "0")
* \param plateau Un plateau de jeu (triple pointeurs).
* \param taille la taille du plateau (taille*taille).
*/
void printPlateau(int** plateau,int taille);

/**
* \brief donne une case du plateau
* \param game représente la structure de jeu (Game)
* \param x l'abcisse de la position de la case (int)
* \param y l'ordonnée de la position de la case (int)
*/
char printCase(Game game, int x, int y);

/**
* \brief affiche le plateau et les tuiles paramétrées.
* \param game représente la structure de jeu (Game)
* \param ville un plateau permettant de calculer la plus grande ville (int**)
*/
void printData(Game* game,int** ville);


/**
* \brief copie les nombres de cases recouvertes des tuiles qui vont être recouvertes par la tuile d'id \a id posée en \a x \a y.
*
* \param game représente la structure de jeu (Game)
* \param id L'identifiant de la tuile a placer (int)
* \param x l'abcisse de la position où placer la tuile (int)
* \param y l'ordonnée de la position où placer la tuile (int)
* \param copie variable dans laquelle sera stockée les nombres de cases recouvertes (int*)
*/
void copieNBCasesRec(Game* game, int id, int x,int y,int* copie); 

/**
* \brief rétabli les anciennes valeures de nombres de cases recouvertes des tuiles qui allaient être recouverte par la tuile d'id \a id placée en position \a x \a y.
*
* \param game représente la structure de jeu (Game)
* \param id L'identifiant de la tuile a placer (int)
* \param x l'abcisse de la position où placer la tuile (int)
* \param y l'ordonnée de la position où placer la tuile (int)
* \param copie Le tableau des anciens nombres de cases recouvertes (int*)
*/
void retablishNBCasesRec(Game* game, int id, int x,int y,int* copie); 

/**
* \brief test si la tuile d'id \a id posée en \a x \a y ne reocuvre pas entièrement une tuile
*
* \param game représente la structure de jeu (Game)
* \param id L'identifiant de la tuile a placer (int)
* \param x l'abcisse de la position où placer la tuile (int)
* \param y l'ordonnée de la position où placer la tuile (int)
* \return -1 si aucune tuile n'est entièrement recouverte, l'id de la tuile entièrement recouverte sinon.
*/
int testRecouvrementTotal(Game* game, int id, int x,int y); 

/**
* \brief Vérifie que la position x y est dans le plateau de jeu
*
* La position a renseigner est celle du coin le plus en haut à gauche de la tuile, après rotation.
*
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \param taille Taille du plateau de jeu
* \param solv = 1 si c'est le solveur qui l'utilise, 0 sinon
* \return 1 si le placement est autorisé, 0 sinon
*/
int inPlateau(int x, int y,int taille,int solv);

/**
* \brief sauvgarde le plateau de jeux actuel case par case dans un tableau 
* \param game un pointeur vers le tableau de jeu (Game)
* \return un tableau de sauvgarde du dernier plateau de jeu (int**)
*/
void savePlateau(Game* game);

/**
* \brief Copie le plateau dans le plateauBis
*
*\param game Désigne le type de partie à lancer
*\return 0 si l'exécution s'est bien passée, 1 sinon
*/
int copyPlateauToPlateauBis(Game* game);


/**
* \brief modifie les cases d'un plateau de jeu en les remplaçant case par case par celle d'un tableau passé en paramètre
* \param game le tableau de jeu (Game)
* \param id_tuile_removed L'id de la dernière tuile ajoutée (int)
* \param x l'abscisse de la tuile qui doit être enlevée (int)
* \param y l'ordonné de la tuile qui doit être enlevée (char)
* \return 1 si tout s'est bien passé (int)
*/
int getPrevious (Game* game ,int id_tuile_removed,int x, char y);

/**
* \brief variefie qu'un tableau ne contient que des 0
* \param previous un tableau de la meme taille que le plateau de jeu (int**)
* \param taille un entier représantant la taille du tableau (int)
* \return 0 si toutes les cases du table ne contiennent que des 0 et 1 si une des case de ce tableau contient autre chose que des 0
*/
int matchEmpty (Game* game);

#endif
