#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#include "../game.h"
#include "../struct.h"
#include "../plateau.h"
#include "../tuile.h"
#include "../score.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

#define STATE_EXIT 0
#define STATE_MENU 1
#define STATE_LOADED_GAME 2
#define STATE_PERSO_GAME 3

typedef struct Button{
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Color color;
	char txt[100];
	int value;
} Button;

typedef struct Files{
	char **files;
	int nb_files;
}Files;


typedef struct Case{
	SDL_Rect Outline;
	char type;	
} Case;


typedef struct Menu{
	SDL_Texture *background;
	Mix_Music *gMusic;
	TTF_Font *font; 
	Button* btnMenu;
	int btn_selected;
	int nb_btn;
} Menu;

typedef struct GameSDL{
	SDL_Texture **img;
	SDL_Texture *txt_title;
	SDL_Texture *txt_idSelected;
	SDL_Texture *backgroundImage;
	SDL_Rect leftPanel;
	SDL_Rect background;
	TTF_Font *font;
	Case **casePlateau;
	Game* data;
	char* filePartie;
	char* fileTuiles;
	int** ville;
	int started;
} GameSDL;

// Structure pour gérer l'input (clavier puis joystick)
typedef struct Input
{
    SDL_Event m_evenements;
} Input;

/* Variables globables */
SDL_Window *screen;
SDL_Renderer *renderer;
Menu menu;
Menu menuCfg;
GameSDL jeu;
Input input;

/* ##########
* FONCTIONS
############# */

void drawPlateau();
void cleanScreen(void);
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
void initGameSDL();
void loadRandomGameSDL();
void loadGameSDL();
void loadMenu();
void cleanScreenSDL();

void loadMenuCfg();
void createBtnMenuCfg(char* optionTxtContain);
void drawMenuCfg(void);
void cleanMenuCfg(void);
int selectCfgGame(int *state);

Button updateTextButton(Button btn,char* text,SDL_Color color,TTF_Font *font);
void btnEventSelect(int direction,Menu* me);


/* GESTION DES INPUTS */
void getInputsGame(Input *input,int* state);
void getInputsMenu(Input *input,int* state);
void getInputsMenuCfg(Input *input,int* state);

#endif
