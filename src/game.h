#ifndef GAME_H
#define GAME_H

#include <dirent.h>
#include "struct.h"
#include "tuile.h"
#include "plateau.h"
#include "SolvNaif.h"

/**
* \brief Importe un fichier de tuile 
*
* Récupère le fichier et importe les tuiles dans le tableau de tuiles et renvoie le nombre de tuiles crées.
*
* \param filepath Chemin du fichier.
* \param gameTuiles Tableau de tuiles.
* \return le nombre de tuiles crée.
*/
int LoadGame(char* filepath,char* filepathTuile,Game* game);

/**
* \brief Importe un fichier de tuile 
*
* Libère les ressources du jeu
* \param solv = 1 si c'est le solveur qui utilise la fonction 0 sinon
*/
void freeGame(Game* game,int solv);


/**
* \brief Initialise une partie
*
*\param typeGame Désigne le type de partie à lancer
*\return 0 si l'exécution s'est bien passée, 1 sinon
*/
int startGame(int typeGame);


/**
 * \brief Vérifie si le fichier existe en utilisant stat.h
 * \return retourne 1 si le fichier existe, 0 sinon
 */
int fileExist(const char* filename);

/**
* \brief Génére un nombre aléatoire borné
*
* Créer un nombre pris au aléatoirement entre deux bornes \a a et \a b
*
* \param a MIN.
* \param b MAX.
* \return le nombre random.
*/
int randomMinMax(int a,int b);

/**
* \brief Permet de purger le buffer après un scanf
*
* Purge du buffer
*
*/
void purger(void);

/**
* \brief Affiche le logo Honshu
*
* Print du logo Honshu en ASCII ART
*
*/
void HonshuScreen();

/**
* \brief Clear l'écran
*
* Clear l'écran terminal/bash
*
*/
void clearScreen();


int check_directory (char* dossier_programme);
void chdirToExecutable(char* chemin_programme);
int scan_files(char* path,char** files,char* optTextIn);

#endif