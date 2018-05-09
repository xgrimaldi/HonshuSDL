/**
* \file tuile.h
* 
* - \b newTuile crée une nouvelle tuile
* - \b randomTuile créer des tuiles aléatoirement
* - \b LoadTuiles charge un fichier tuile
* - \b copyTuile copie une tuile
* - \b rotateTuile oriente une tuile
* - \b printTuiles affiche les tuiles
* - \b printIntToCharColor affiche en couleur un caractère donné
* - \b placeTuile place une tuile
* - \b canPlaceTuile vérifie la possibilité de placer une tuile
*/

#ifndef TUILE_H
#define TUILE_H

#include "struct.h"
#include "game.h"
#include "plateau.h"

/**
* \brief Importe un fichier de tuile 
*
* Récupère le fichier et importe les tuiles dans le tableau de tuiles et renvoie le nombre de tuiles crées.
*
* \param filepath Chemin du fichier.
* \param gameTuiles Tableau de tuiles.
* \return le nombre de tuiles crée.
*/
int LoadTuiles(char* filepath,Tuile* gameTuiles);

/**
* \brief Copie une tuile dans une autre
*
* \param tuileACopier tuile qui doit être copié
* \return retourne la tuile copiée
*/
Tuile copyTuile(Tuile tuileACopier);

/**
* \brief Permet de changer l'orientation d'une tuile
*
* \param t Tuile qui doit subir la rotation
* \return La tuile modifiée
*/
Tuile rotateTuile(Tuile t,char direction);

/**
* \brief Créer une nouvelle tuile
* \param id identifiant de la tuile
* \param x1 case 1
* \param x2 case 2
* \param x3 case 3
* \param x4 case 4
* \param x5 case 5
* \param x6 case 6
* \return retourne la nouvelle tuile
*/
Tuile newTuile(int id, char x1, char x2, char x3, char x4, char x5, char x6);


/**
* \brief Affiche les tuiles paramètrées
* \attention Si aucune tuiles, message d'erreur affiché.
* \param gameTuiles Le tableau de tuiles.
* \param nbTuiles Le nombre de tuiles
*/
void printTuiles(Tuile gameTuiles[MAXTUILES],int nbTuiles);

/**
* \brief Affiche les int en caractères en couleur
* \param car Entier correspondant à la valeur ASCII d'un caractère
*/
void printIntToCharColor(int car);

/**
* \brief Affiche id des tuiles disponibles 
* \param gameTuiles Le tableau de tuiles.
* \param nbTuiles Le nombre de tuiles
*/
void printTuilesNonDisponibles(Tuile gameTuiles[MAXTUILES],int nbTuiles);

/**
* \brief Place la tuile d'id \a id à la position \a x , \a y du jeu pointé par \a game
* \param game Pointeur vers le tableau de jeu (Game*)
* \param id l'identifiant de la tuile a placer (int)
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \param solv = 1 si c'est le solveur qui l'utilise, 0 sinon
* \return 0 si l'exécution s'est bien passée, 1 sinon
*/
int placeTuile(Game* game, int id, int x, int y, int solv);

/**
* \brief Vérifie que le placement de la tuile d'id\a id est autorisé à la position \a x , \a y du jeu \a game
*
* La position a renseigner est celle du coin le plus en haut à gauche de la tuile, après rotation.
*
* \param game représente la structure de jeu (Game)
* \param id L'identifiant de la tuile a placer (int)
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \param solv = 1 si c'est le solveur qui l'utilise, 0 sinon
* \return 1 si le placement est autorisé, 0 sinon
*/
int canPlaceTuile(Game game, int id, int x,int y,int solv); 

/**
* \brief Génère \a nb_Tuile tuile(s) aléatoirement
* \param nb_Tuile > 0 nombre de tuile à générer (int)
* \return un tableau de \a nb_Tuile tuile(s)
*/
Tuile* randomTuile(int nb_Tuile);

void initTuileJoue(Game* game);
void hideTuileJoue(Game* game);
void firstTuileAvailable(Game* game);
void changeOrientationTuileJoue(Game* game);

/**
* \brief Prochaine tuile disponible
* \param game
*/
void nextTuileAvailable(Game* game);

/**
* \brief Place la tuile en cours de jeu dans le plateau Bis (qui sert de copie)
* \param game Pointeur vers le tableau de jeu (Game*)
* \return 0 si l'exécution s'est bien passée, 1 sinon
*/
int placeTuileJoue(Game* game);

/**
* \brief Déplace la tuile en vérifiant les contraintes du plateau
* \param game Pointeur vers le tableau de jeu (Game*)
* \param x position x à incrémenter ou décrémenter
* \param y position y à incrémenter ou décrementer
* \return 0 si l'exécution s'est bien passée, 1 sinon
*/
void moveTuileJoue(Game* game,int x,int y);

#endif