/*
* PROJET INFO - LES TUILEURS
*/

#include "../game.h"
#include "../tuile.h"
#include "../plateau.h"
#include "../struct.h"
#include "SDL.h"

int main() {

	int state=1;
	unsigned int frameLimit = SDL_GetTicks() + 16;

	 // Initialisation de la SDL
	initHonshu("Honshu");
	 
	// Chargement des ressources (graphismes, sons)
	loadMenu();
	LoadGameSDL();

	// Appelle la fonction cleanup à la fin du programme
	atexit(cleanup);
	 
	// Boucle infinie, principale, du jeu
	while (state != 0)
	{	 	
	 	if(state==1){
	 		if(menu.background==NULL){
	 			loadMenu();
	 		}
	 		//If there is no music playing 
 			if( Mix_PlayingMusic() == 0 ) { 
 				//Play the music
	 		 	Mix_PlayMusic( menu.gMusic, -1 );
	 		}
			//Gestion des inputs clavier
			getInputsMenu(&input,&state);
			//On dessine tout
			drawMenu();
		}
		
		else if(state==2){
			getInputsGame(&input,&state);
			drawGame();
			if(state!=2){
				cleanScreenSDL();
			}
		}
		// Gestion des 60 fps (1000ms/60 = 16.6 -> 16
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;
	}

	// On quitte
	exit(0);
 
	return 0;
}
