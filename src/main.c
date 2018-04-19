/*
* PROJET INFO - LES TUILEURS
*/

#include "game.h"
#include "tuile.h"
#include "plateau.h"
#include "struct.h"
#include "SDL.h"

int main() {
	/*********************************
	* Déclaration des variables
	*********************************/
	int choix=0;
	srand(time(NULL)); 

	/**********************************
	* Lancement du jeu 
	**********************************/
	int stop = 0;
	while(stop == 0){
		clearScreen();
		HonshuScreen();
		
		LOG_BOLDRED("\n\t\t\t\tMenu de sélection\n");
		printf("\t\t\t1 - Créer une partie personnalisée\n");
		printf("\t\t\t2 - Charger une partie d'un fichier\n");
		printf("\t\t\t3 - Démarrer une partie graphique (SDL)\n");
		printf("\t\t\t0 - Quitter le programme\n");
		scanf("%d", &choix);
		purger();
		switch(choix){
			case 1:{
				startGame(choix);
				break;
			}
			case 2:{
				startGame(choix);
				break;
			}
			case 3:{
				startGameSDL();
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
