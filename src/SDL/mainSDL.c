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
		//Initialisation du srand
		srand(time(NULL)); 
		// Initialisation de la variable d'état du jeu
		int state=STATE_MENU;
		// Initialisation de la variable de gestion FPS
		unsigned int frameLimit = SDL_GetTicks() + 16;
		// Redirection du dossier d'éxécution 
		chdirToExecutable(argv[0]);

		// Appelle la fonction cleanup à la fin du programme
		atexit(cleanup);

		// Initialisation de la SDL
		initHonshu("Honshu");
		 
		// Chargement des ressources (graphismes, sons)
		initGameSDL();
		initMenu();
		initRessources();
		loadMenu();
		loadMenuCfg();
		 
 		//If there is no music playing 
		if( Mix_PlayingMusic() == 0 ) { 
			//Play the music
 		 	Mix_PlayMusic( gameRes.musicGame, -1 );
 		}

		// Boucle infinie, principale, du jeu
		while (state != STATE_EXIT)
		{	 	
			//STATE_MENU
		 	if(state==STATE_MENU){
				//Gestion des inputs clavier
				getInputsMenu(&input,&state);
				//On dessine tout
				drawMenu();
			}
			
			// STATE_PERSO_GAME
			else if(state==STATE_PERSO_GAME){
				if(!jeu.started){
					int size = runTextInput();
					if(size>=7 && size<=30)
						loadRandomGameSDL(size);
					else
						state=STATE_MENU;
				}
				else{
					getInputsGame(&input,&state);
					if(state == STATE_PERSO_GAME) 
						drawGame();
				}
			}

			// STATE_LOADED_GAME
			else if(state==STATE_LOADED_GAME){
				if(!jeu.started)
				{
					if(selectCfgGame(&state)== EXIT_FAILURE){
						state=STATE_MENU;
					}
					else{
						loadGameSDL();
					}
				}
				else
				{
					getInputsGame(&input,&state);
					if(state == STATE_LOADED_GAME) 
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
