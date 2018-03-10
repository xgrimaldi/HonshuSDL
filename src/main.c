/*
* PROJET INFO - LES TUILEURS
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game.h"

int main() {
	//*********************************
	// Déclaration des variables
	//*********************************
	int choix=0;

	//**********************************
	// Lancement du jeu 
	//**********************************
	int stop = 0;
	while(stop == 0){
		clearScreen();
		HonshuScreen();
		
		printf("\nQue voulez-vous faire ?\n");
		printf("0 - Quitter le programme\n");
		printf("1 - Lancement d'une partie\n");
		scanf("%d",&choix);
		switch(choix){
			case 1:{
				Game newgame = initGame();
				startGame(newgame);
				break;
			}
			case 0:{
				stop = 1;
				break;
			}
		}
	}

	return 0;
}
