/**
* \file struct.h
* 
* Gestion des constantes et des structures
* - \b Game structure d'une partie
* - \b Tuile structure d'une tuile
*/

#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>

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
#define Color_Bold_Gray "\033[1m\033[36m"
#define Color_end "\033[0m" // To flush out prev settings
#define LOG_BOLDRED(X) printf("%s %s %s",Color_Bold_Red,X,Color_end)

/**
* \typedef Position
* Type représentant une positon x et y
*/
typedef struct Position{
	int x;
	int y;
} Position;

/**
* \typedef Tuile
* Type représentant une tuile
*/
typedef struct Tuile {	
	int id;
	Position pos;
  int nbCasesRecouvertes;
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
  int** plateauIDmax;
  int** plateauBis;
  int** previous;
  int** previousIDmax;
  int* previousNBCasesRec;
  Tuile* tuiles;
  Tuile tuileJoue;
  int nbTuiles;
  int nbTuilesPose;
  int taille;
  int nivSolv;
} Game;

#endif