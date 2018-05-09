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
					printf("OK");
					jeu.data->tuiles = malloc(MAXTUILES * sizeof(Tuile));
					jeu.ville = alloc_int_array(jeu.data->taille, jeu.data->taille);
					initPlateau(jeu.ville,jeu.data->taille,-1);
					char tuiles[100]="../files/";
					char partie[100]="../files/";
					strcat(tuiles,jeu.fileTuiles);
					strcat(partie,jeu.filePartie);
					LoadGame(partie,tuiles,jeu.data);
					jeu.data->tuileJoue.id = -1;
					jeu.data->tuileJoue.pos.x=-1;
					jeu.data->tuileJoue.pos.y=-1;
					jeu.started=1;
					jeu.data->score = getScore(jeu.data,jeu.ville,0);

					// Gestion des cases du plateau SDL
					jeu.casePlateau= malloc(jeu.data->taille * sizeof(Case));
					for (int i=0; i<jeu.data->taille; i++)
					    jeu.casePlateau[i] = malloc(jeu.data->taille * sizeof(Case));

					// Attribution des positions de chaque case
				    for(int row=0; row < jeu.data->taille; row++)
				    {
				        for( int column=0; column < jeu.data->taille; column++)
				        {
							jeu.casePlateau[row][column].Outline.x=(column * (SCREEN_WIDTH*0.7/jeu.data->taille))+SCREEN_WIDTH*0.3;
							jeu.casePlateau[row][column].Outline.y=row * SCREEN_HEIGHT/jeu.data->taille;
							jeu.casePlateau[row][column].Outline.w=SCREEN_WIDTH*0.7/jeu.data->taille;
							jeu.casePlateau[row][column].Outline.h=SCREEN_HEIGHT/jeu.data->taille;
						}
					}
				}
				else{
					getInputsGame(&input,&state);
					drawGame();
				}
			}
			// Gestion des 60 fps (1000ms/60 = 16.6 -> 16
			delay(frameLimit);
			frameLimit = SDL_GetTicks() + 16;
		}

		// On quitte
		exit(0);
 	}
	return 0;
}
