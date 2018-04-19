#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "game.h"
#include "struct.h"
#include "plateau.h"
#include "tuile.h"
#include "score.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480


 // Structure pour gérer la map à afficher (à compléter plus tard)
typedef struct Menu{
	SDL_Texture *background;
	Mix_Music *gMusic;
} Menu;

typedef struct Case{
	SDL_Rect Outline;
	char type;	
} Case;

typedef struct GameSDL{
	SDL_Texture **img;
	SDL_Texture *txt_title;
	SDL_Texture *txt_idSelected;
	SDL_Rect leftPanel;
	SDL_Rect background;
	TTF_Font *font;
	Case **casePlateau;
	Game* data;
} GameSDL;


// Structure pour gérer l'input (clavier puis joystick)
typedef struct Input
{
    int left, right, up, down, jump, attack, enter, erase, pause;
 
} Input;

void drawPlateau();
void cleanScreen(void);
void getInputsGame(Input *input,int* state);
void getInputsMenu(Input *input,int* state);
void drawLeftPanelGame(void);
SDL_Texture *loadImage(char *name);
void delay(unsigned int frameLimit);
void drawMenu(void);
void drawGame();
void cleanup();
void cleanGame();
void cleanMenu();
void initHonshu(char *title);
SDL_Renderer *getrenderer(void);
void drawImage(SDL_Texture *image, int x, int y);
int startGameSDL();
void loadGameSDL();


#endif