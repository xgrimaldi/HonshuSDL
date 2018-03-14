
#ifndef GAME_H
#define GAME_H

#define n 20
#define MAXTUILES 100

#define L "LAC"
#define P "PLAINE"
#define F "FORET"
#define V "VILLE"
#define U "USINE"
#define R "RESSOURCE"

#define Color_Red "\033[1m\033[31m" // Color Start
#define Color_end "\033[0m" // To flush out prev settings
#define LOG_BOLDRED(X) printf("%s %s %s",Color_Red,X,Color_end)

/**
* \file game.h
* 
* Création des paramètres HONSHU. 5 fonctions sont définies:
* - \b LoadTuiles Importe un fichier de tuile en paramètre du jeu.
* - \b printTuiles permet d'afficher les tuiles paramètréss.
* - \b printPlateau permet d'afficher le plateau de jeu actuel.
* - \b alloc_array permet d'allouer un triple pointeur de char.
*/

/**
* \typedef Tuile
* Type représentant une tuile
*/
typedef struct Tuile {	
	int id;
	char orientation;
	char X_1;
	char X_2;
	char X_3;
	char X_4;
	char X_5;
	char X_6;
} Tuile;

/**
* \typedef Game
* Type représentant une partie
*/
typedef struct Game {
	int** plateau;
	Tuile* tuiles;
	int nbTuiles;
	int taille;
} Game;


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

/**
* \brief Génére la tuile aléatoirement
*
* Positionne une tuile au hasard au milieu du plateau
*
* \param partie variable représentant une partie (structure Game).
*/
void initPlacementTuileRandom(Game partie);

/**
* \brief Génére un nombre aléatoire borné
*
* Créer un nombre pris aléatoirement entre deux bornes \a a et \a b compris
*
* \param a MIN (int)
* \param b MAX (int)
* \return le nombre random.
*/
int randomMinMax(int a,int b);

/**
* \brief Importe un fichier de tuile 
*
* Récupère le fichier et importe les tuiles dans le tableau de tuiles et renvoie le nombre de tuiles crées.
*
* \param filepath Chemin du fichier.
* \param gameTuiles Tableau de tuiles.
* \return le nombre de tuiles crée.
*/
int LoadTuiles(char* filepath,Tuile gameTuiles[MAXTUILES]);

/**
* \brief Initialise le plateau de jeu
*
*/
void initPlateau(int** gamePlateau);

/**
* \brief Initialise une partie
*/
void startGame(Game game);

/**
* \brief Initialise une partie
*/
Game initGame();

/**
* \brief Affiche le plateau de jeu \a g
* \attention Au début du programme, un plateau vide est crée (composé que de "0")
* \param plateau Un plateau de jeu (triple pointeurs).
* \param taille la taille du plateau (taille*taille).
*/
void printPlateau(int** plateau,int taille);

/**
* \brief Affiche les tuiles paramètrées
* \attention Si aucune tuiles, message d'erreur affiché.
* \param gameTuiles Le tableau de tuiles.
* \param nbTuiles Le nombre de tuiles
*/
void printTuiles(Tuile gameTuiles[MAXTUILES],int nbTuiles);


/**
* \brief Alloue un triple pointeur de char de taille \a x  * \a y
*
* \param x La taille du premier pointeur (int**)
* \param y La taille du deuxième pointeur (int*) 
* \return Un int **
*/
int **alloc_int_array(int x, int y);


/**
* \brief Place la tuile d'id \a id à la position \a x , \a y du jeu pointé par \a game
* \param game Pointeur vers le tableau de jeu (Game*)
* \param id l'identifiant de la tuile a placer (int)
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \return 0 si l'exécution s'est bien passée, 1 sinon
*/
int placeTuile(Game* game, int id, int x, int y);

/**
* \brief Vérifie que le placement de la tuile d'id\a id est autorisé à la position \a x , \a y du jeu \a game
*
* La position a renseigner est celle du coin le plus en haut à gauche de la tuile, après rotation.
*
* \param le tableau de jeu (Game)
* \param id L'identifiant de la tuile a placer (int)
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \return 1 si le placement est autorisé, 0 sinon
*/
int canPlaceTuile(Game game, int id, int x,int y); //Pas entièrement implémentée

/**
* \brief Génère \a nb_Tuile tuile(s) aléatoirement
* \param nb_Tuile > 0 nombre de tuile à générer (int)
* \return un tableau de \a nb_Tuile tuile(s)
*/
Tuile* randomTuile(int nb_Tuile);
#endif
