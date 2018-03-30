
#ifndef GAME_H
#define GAME_H

#define MAXTUILES 100

#define L "LAC"
#define P "PLAINE"
#define F "FORET"
#define V "VILLE"
#define U "USINE"
#define R "RESSOURCE"

#define Color_Bold_Red "\033[1m\033[31m"
#define Color_Bold_Green "\033[1m\033[32m" 
#define Color_Bold_Yellow  "\033[1m\033[33m" 
#define Color_Bold_Blue "\033[1m\033[34m" 
#define Color_Bold_Magenta "\033[1m\033[35m"
#define Color_Bold_White "\033[1m\033[37m" 
#define Color_end "\033[0m" // To flush out prev settings
#define LOG_BOLDRED(X) printf("%s %s %s",Color_Bold_Red,X,Color_end)

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
  int nbCasesRecouvertes;
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
  int** plateauIDmax;
  Tuile* tuiles;
  int nbTuiles;
  int nbTuilesPose;
  int taille;
} Game;

/**
* \brief Alloue un triple pointeur de char de taille \a x  * \a y
*
* \param x La taille du premier pointeur (int**)
* \param y La taille du deuxième pointeur (int*) 
* \return Un int **
*/
int **alloc_int_array(int x, int y);

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
* \return 0 si l'exécution s'est bien passée, 1 sinon
*/
int rotateTuile(Tuile t,char direction);

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
* \brief Initialise le plateau de jeu
*
* \param val Est la valeure que va contenir toutes les cases du plateau
*/
void initPlateau(int** gamePlateau,int taille, int val);

/**
* \brief Initialise une partie
*
*\param typeGame Désigne le type de partie à lancer
*\return 0 si l'exécution s'est bien passée, 1 sinon
*/
int startGame(int typeGame);

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
* \brief Affiche les int en caractères en couleur
* \param car Entier correspondant à la valeur ASCII d'un caractère
*/
void printIntToCharColor(int car);

/**
* \brief Place la tuile d'id \a id à la position \a x , \a y du jeu pointé par \a game
* \param game Pointeur vers le tableau de jeu (Game*)
* \param id l'identifiant de la tuile a placer (int)
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \param previous un tableau permetant de sauvegarder le dernier plateau de jeu (int**)
* \param previousIDmax un tableau permetant de sauvegarder le dernier plateau des ids max des tuiles (int**) 
* \param previousNBCasesRec Un tableau contenant les nb de cases recouvertes des tuiles anciennements recouvertes pour gérer le undo (int*)
* \return 0 si l'exécution s'est bien passée, 1 sinon
*/
int placeTuile(Game* game, int id, int x, int y, int ** previous,int** previousIDmax,int* previousNBCasesRec);

/**
* \brief Vérifie que le placement de la tuile d'id\a id est autorisé à la position \a x , \a y du jeu \a game
*
* La position a renseigner est celle du coin le plus en haut à gauche de la tuile, après rotation.
*
* \param game représente la structure de jeu (Game)
* \param id L'identifiant de la tuile a placer (int)
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \return 1 si le placement est autorisé, 0 sinon
*/
int canPlaceTuile(Game game, int id, int x,int y); 

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
* \param previousNBCasesRec un tableau contenant les nombres de cases recouvertes des tuiles avant d'être recouvertes (int*) 
* \return -1 si aucune tuile n'est entièrement recouverte, l'id de la tuile entièrement recouverte sinon.
*/
int testRecouvrementTotal(Game* game, int id, int x,int y,int* previousNBCasesRec); 

/**
* \brief Vérifie que la position x y est dans le plateau de jeu
*
* La position a renseigner est celle du coin le plus en haut à gauche de la tuile, après rotation.
*
* \param x l'abcisse de la position ou placer la tuile (int)
* \param y l'ordonnée de la position ou placer la tuile (int)
* \param taille Taille du plateau de jeu
* \return 1 si le placement est autorisé, 0 sinon
*/
int inPlateau(int x, int y,int taille);

/**
* \brief Génère \a nb_Tuile tuile(s) aléatoirement
* \param nb_Tuile > 0 nombre de tuile à générer (int)
* \return un tableau de \a nb_Tuile tuile(s)
*/
Tuile* randomTuile(int nb_Tuile);

/**
* \brief sauvgarde le plateau de jeux actuel case par case dans un tableau 
* \param game un pointeur vers le tableau de jeu (Game)
* \param previous un tableau de la meme taille que le plateau de jeu (int**)
* \param previousIDmax un tableau de la meme taille que le plateau des id max des tuiles posées (int**)
* \return un tableau de sauvgarde du dernier plateau de jeu (int**)
*/
void saveGame(Game* game, int** previous, int** previousIDmax);

/**
* \brief modifie les cases d'un plateau de jeu en les remplaçant case par case par celle d'un tableau passé en paramètre
* \param game le tableau de jeu (Game)
* \param previous un tableau de la meme taille que le plateau de jeu (int**)
* \param previousIDmax un tableau de la meme taille que le plateau des ids max des tuiles (int**)
* \param id_tuile_removed L'id de la dernière tuile ajoutée (int)
* \param previousNBCasesRec un tableau contenant les nombres de cases recouvertes des tuiles avant d'être recouvertes (int*)
* \param x l'abscisse de la tuile qui doit être enlevée (int)
* \param y l'ordonné de la tuile qui doit être enlevée (char)
* \return 1 si tout s'est bien passé (int)
*/
int getPrevious (Game* game ,int** previous,int** previousIDmax,int id_tuile_removed,int* previousNBCasesRec,int x, char y);

/**
* \brief variefie qu'un tableau ne contient que des 0
* \param previous un tableau de la meme taille que le plateau de jeu (int**)
* \param taille un entier représantant la taille du tableau (int)
* \return 0 si toutes les cases du table ne contiennent que des 0 et 1 si une des case de ce tableau contient autre chose que des 0
*/
int matchEmpty (int** previous, int taile);


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

#endif
