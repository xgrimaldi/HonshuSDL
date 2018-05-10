/*
* PROJET INFO - LES TUILEURS
*/

#include "../game.h"
#include "../tuile.h"
#include "../plateau.h"
#include "../struct.h"
#include "SDL.h"

/*
#define STATE_EXIT 0
#define STATE_MENU 1
#define STATE_LOADED_GAME 2
#define STATE_PERSO_GAME 3
*/

int main(int argc, char *argv[]) {
	if(argc>=1){
		int state=1;
		unsigned int frameLimit = SDL_GetTicks() + 16;
		chdirToExecutable(argv[0]);

		 // Initialisation de la SDL
		initHonshu("Honshu");
		 
		// Chargement des ressources (graphismes, sons)
		initGameSDL();
		loadMenu();
		loadMenuCfg();

		// Appelle la fonction cleanup à la fin du programme
		atexit(cleanup);
		 
 		//If there is no music playing 
		if( Mix_PlayingMusic() == 0 ) { 
			//Play the music
 		 	Mix_PlayMusic( menu.gMusic, -1 );
 		}
		// Boucle infinie, principale, du jeu
		while (state != STATE_EXIT)
		{	 	
		 	if(state==1){
		 		if(menu.background==NULL){
		 			loadMenu();
		 		}
				//Gestion des inputs clavier
				getInputsMenu(&input,&state);
				//On dessine tout
				drawMenu();
			}
			
			else if(state==2){
				if(!jeu.started) {
					loadRandomGameSDL();
				}
				else{
					getInputsGame(&input,&state);
					drawGame();
					if(state!=2){
						cleanScreenSDL();
					}
				}
			}
			else if(state==3){
				if(!jeu.started) {
					if(selectCfgGame(&state)== EXIT_FAILURE){
						state=STATE_MENU;
					}
					loadGameSDL();
				}
				else{
					getInputsGame(&input,&state);
					drawGame();
				}
			}
			// Gestion des 60 fps (1000ms/60 = 16.6 -> 16)
			delay(frameLimit);
			frameLimit = SDL_GetTicks() + 16;
		}

		// On quitte
		exit(0);
 	}
	return 0;
}
