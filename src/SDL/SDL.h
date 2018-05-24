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
#define STATE_PERSO_GAME 2
#define STATE_LOADED_GAME 3

/* ###########################*/
/*         STRUCTURE     	  */
/*############################*/

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

typedef struct PopUp{
	SDL_Rect background;
	SDL_Texture *txt;
	TTF_Font *font; 
} PopUp;

typedef struct GameSDL{
	SDL_Texture **img;
	SDL_Texture *txt_title;
	SDL_Texture *backgroundImage;
	SDL_Texture *leftBorder;
	SDL_Rect leftPanel;
	SDL_Rect background;
	Button* btn;
	TTF_Font *font;
	Case **casePlateau;
	Game* data;
	PopUp pop;
	PopUp cmd;
	char* filePartie;
	char* fileTuiles;
	int** ville;
	int started;
	bool showRules;
	bool showCmd;
} GameSDL;

typedef struct GameRessource{
	Mix_Music *musicGame;
	SDL_Texture *tilesetBtn;
} GameRessource;

// Structure pour gérer l'input (clavier puis joystick)
typedef struct Input {
	SDL_Event m_evenements;
} Input;

/*#####################*/
/* Variables globables */
/*#####################*/

SDL_Window *screen;
SDL_Renderer *renderer;
Menu menu;
Menu menuCfg;
GameSDL jeu;
GameRessource gameRes;
Input input;

/* #################*/
/*     FONCTIONS	*/
/*##################*/

/* DIVERS */
SDL_Texture *loadImage(char *name);
void delay(unsigned int frameLimit);
SDL_Renderer *getrenderer(void);

/* INITIALISATION */
void initHonshu(char *title);
void initRessources();
void initGameSDL();
void initMenu(void);

/* CHARGEMENT */
void loadMenuCfg();
void loadRandomGameSDL();
void loadGameSDL();
void loadMenu(void);

/* AFFICHAGE */
void drawMenu(void);
void drawGame();
void drawImage(SDL_Texture *image, int x, int y);
void drawMenuCfg(void);
void drawLeftPanelGame(void);
void drawPlateau();
void drawTextGame(char * message,SDL_Color color,int x,int y);

/* EFFACEMENT */
void cleanup();
void cleanGame();
void cleanMenu();
void cleanRessources(void);
void cleanMenuCfg(void);
void cleanScreen(void);
void cleanScreenSDL();

/* GESTION DES INPUTS */
void getInputsGame(Input *input,int* state);
void getInputsMenu(Input *input,int* state);
void getInputsMenuCfg(Input *input,int* state);

/* GESTION DES TILE */
void drawTile(SDL_Texture *image, int destx, int desty, int destw, int desth ,int srcx, int srcy,int tileWSize, int tileHSize);

/* CONFIGURATION PARTIE */
void createBtnMenuCfg(char* optionTxtContain);
int selectCfgGame(int *state);

/* BUTTON & SELECT*/
Button updateTextButton(Button btn,char* text,SDL_Color color,TTF_Font *font);
void btnEventSelect(int direction,Menu* me);
int buttonHover(Menu* menu,int x, int y);
void btnHoveredSelect(Menu* me,int btnNum);
Position caseHover(int x,int y);

PopUp createPopUp(SDL_Color color,TTF_Font* font,char* message,SDL_Rect rect);
Button createBtnImage(char* path,int x, int y, int w, int h,int value);
bool btnHovered(Button btn,int mousx,int mousy);
#endif
