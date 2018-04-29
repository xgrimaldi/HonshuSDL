#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "SDL.h"

/* =======================================
* 			INITIALISATION
* ========================================*/
 
void initHonshu(char *title){

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        exit(0);
    }

	/*Création de fênetre*/
    screen = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
 
    /*On crée un renderer pour la SDL et on active la synchro verticale : VSYNC*/
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);
 
    // Si on n'y arrive pas, on quitte en enregistrant l'erreur
    if (screen == NULL || renderer == NULL){
        printf("Impossible d'initialiser le mode écran à %d x %d: %s\n", SCREEN_WIDTH,SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }
 
    //Initialisation du chargement des images png avec SDL_Image 2
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        printf( "SDL_image n'a pu être initialisée! SDL_image Error: %s\n", IMG_GetError() );
        exit(1);
    }
 
    //On cache le curseur de la souris
    SDL_ShowCursor(SDL_DISABLE);
 
    //On initialise SDL_TTF 2 qui gérera l'écriture de texte
    if (TTF_Init() < 0)
    {
        printf("Impossible d'initialiser SDL TTF: %s\n", TTF_GetError());
        exit(1);
    }
 
    //On initialise SDL_Mixer 2, qui gérera la musique et les effets sonores
    int flags = MIX_INIT_MP3;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags)
    {
        printf("Mix_Init: Failed to init SDL_Mixer\n");
        printf("Mix_Init: %s\n", Mix_GetError());
        exit(1);
    }
 
    /* Open 44.1KHz, signed 16bit, system byte order,
    stereo audio, using 1024 byte chunks (voir la doc pour plus d'infos) */
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }
 
    // Définit le nombre de pistes audio (channels) à mixer
    Mix_AllocateChannels(32);
 
}

 /* =======================================
* 				Chargement
* ========================================*/

SDL_Texture *loadImage(char *name){
	/* Charge les images avec SDL Image dans une SDL_Surface */
	SDL_Surface *loadedImage = NULL;
	SDL_Texture *texture = NULL;
	loadedImage = IMG_Load(name);
	 
	if (loadedImage != NULL){
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(getrenderer(), loadedImage);
		// On se débarrasse du pointeur vers une surface
		SDL_FreeSurface(loadedImage);
		loadedImage = NULL;
	}
	else
	printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());
	return texture;
}

 /* =======================================
* 				Affichage
* ========================================*/
void drawImage(SDL_Texture *image, int x, int y){
	SDL_Rect dest;
	 
	/* Règle le rectangle à dessiner selon la taille de l'image source */
	dest.x = x;
	dest.y = y;
	 
	/* Dessine l'image entière sur l'écran aux coordonnées x et y */
	SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(getrenderer(), image, NULL, &dest);
}

/* =======================================
* 			Libération / Fin
* ========================================*/
 
void cleanup(){
	// Effacement de la partie
	cleanMenu();
	cleanGame();

    //On fait le ménage et on remet les pointeurs à NULL
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(screen);
    screen = NULL;

    //On quitte SDL_Mixer 2 et on décharge la mémoire
    Mix_CloseAudio();
    Mix_Quit();

    //On quitte SDL_TTF 2
    TTF_Quit();
	IMG_Quit();
    //On quitte la SDL
    SDL_Quit();
}

void cleanScreenSDL(void)
{	
	/* Création du rectangle de coté */
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = SCREEN_WIDTH;
    r.h = SCREEN_HEIGHT;

    // Set render color to blue ( rect will be rendered in this color )
    SDL_SetRenderDrawColor( getrenderer(), 0, 0, 0, 0);

    // Render rect
    SDL_RenderFillRect( getrenderer(), &r );

    SDL_RenderPresent(getrenderer());

	// Délai pour laisser respirer le proc
	SDL_Delay(1);  
}

/* =======================================
* 			Autres fonctions
* ========================================*/

/* Récupère le renderer */
SDL_Renderer *getrenderer(void)
{
    return renderer;
}

// Gestion des FPS
void delay(unsigned int frameLimit)
{
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();
 
    if (frameLimit < ticks){
        return;
    }
 
    if (frameLimit > ticks + 16){
        SDL_Delay(16);
    }
    else{
        SDL_Delay(frameLimit - ticks);
    }
}

// Fonction de saisie d'un texte à l'écran 
void runTextInput(SDL_Renderer* renderer,char* rep)
{
	/* Initialisation du TextInput */
	SDL_StartTextInput();

	/* Déclaration des variables */
	size_t len = 0;
	size_t LEN_MAX=30;
	SDL_Event event;
	SDL_bool quit = SDL_FALSE;
    TTF_Font *font = TTF_OpenFont("../font/Raleway-Bold.ttf", 25);
    SDL_Color color = { 0, 5, 234 , 0 };
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect dstrect;
    int texW = 0;
    int texH = 0;

    /* Boucle d'écriture */ 
	while(!quit)
	{
		SDL_bool has_type = SDL_FALSE;
		SDL_WaitEvent(&event); /* Attente d'un nouvel événement */
		
		// Vérification des événements
		if(event.type == SDL_QUIT)
			quit = SDL_TRUE;
		else if( event.type == SDL_KEYDOWN)
		{
			if(event.key.keysym.sym == SDLK_BACKSPACE && len)
			{
				rep[len - 1] = 0;
				len--;
				has_type = SDL_TRUE;
			}
			if(event.key.keysym.sym == SDLK_RETURN){
				quit = SDL_TRUE;
			}
			if(event.key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL) && SDL_HasClipboardText())
			{
				char *tmp = SDL_GetClipboardText();
				size_t l = strlen(tmp);
				size_t l_copy = len + l < LEN_MAX ? l : LEN_MAX - len;
				strncpy(rep + len, tmp, l_copy);
				len += l_copy;
				SDL_free(tmp);
				has_type = SDL_TRUE;
			}
			if(event.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL))
				SDL_SetClipboardText(rep);
		}
		else if(event.type == SDL_TEXTINPUT)
		{
			size_t l = strlen(event.text.text);
			size_t l_copy = len + l < LEN_MAX ? l : LEN_MAX - len;
			strncpy(rep + len, event.text.text, l_copy);
			len += l_copy;
			has_type = SDL_TRUE;
		}

		//Si une saisie a été effectué.
		if(has_type){
		   	surface = TTF_RenderText_Solid(font,rep,color);
		    texture = SDL_CreateTextureFromSurface(renderer, surface);
		    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
		    dstrect.x= 0;
		    dstrect.y= 0;
		    dstrect.w=texW;
		    dstrect.h=texH;
	        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	        SDL_RenderPresent(renderer);
	        SDL_Delay(1);
	        SDL_RenderClear(renderer);
	    }
	}

	// Libération des ressources
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
	SDL_StopTextInput();
}

/* =======================================
* 			MENU
* ========================================*/
void loadMenu(void)
{
 	// Charge l'image du fond (background)
	menu.background = loadImage("../images/menu.bmp");
	 //Load music
	menu.gMusic = Mix_LoadMUS( "../sound//beat.wav" ); 
	if( menu.gMusic == NULL ) {
		 printf( "Impossible de lancer la musique ! SDL_mixer Error: %s\n", Mix_GetError() ); 
		 exit(0);
	}
}

void drawMenu(void){
	SDL_Rect dest;
	 
	/* Règle le rectangle à dessiner selon la taille de l'image source */
	dest.x = 0;
	dest.y = 0;

	/* Récupère les informations */
	SDL_QueryTexture(menu.background, NULL, NULL, &dest.w, &dest.h);

	// Affiche le fond (background) aux coordonnées (0,0)
	drawImage(menu.background, (SCREEN_WIDTH/2)-dest.w/2, (SCREEN_HEIGHT/2)-dest.h/2);
	 
	// Affiche l'écran
	SDL_RenderPresent(getrenderer());
	SDL_RenderClear(getrenderer());
	// Délai pour laisser respirer le proc
	SDL_Delay(1); 
}
 
void getInputsMenu(Input *input,int* state)
{
    SDL_Event event;
 
    /* Keymapping : gère les appuis sur les touches et les enregistre
    dans la structure input */
    while (SDL_PollEvent(&event)){
        switch (event.type){
 
            case SDL_QUIT:
                *state=0;
            break;
 
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        *state=0;
                    break;
  
                    case SDLK_UP:
                   		input->jump=1;
                    break;
  
                    case SDLK_1:
                    	*state=2;
                    break;
 
                    default:
                    break;
                }
            break;
        }
    }
}

void cleanMenu(void)
{
	// Libère la texture du background
	if (menu.background != NULL)
	{
		SDL_DestroyTexture(menu.background);
		menu.background = NULL;
	}
	Mix_FreeMusic( menu.gMusic );
 
}
/* =======================================
* 			JEU
* ========================================*/
void LoadGameSDL(void)
{
	// Malloc GAME
	jeu.data=malloc(sizeof(Game));
 	// Charge l'image du fond (background)
	jeu.img = malloc(6 * sizeof(SDL_Texture*));
	// Chargement du font
	jeu.font = TTF_OpenFont("../font/Raleway-Bold.ttf", 25);

	//Attribut data(Game)
	jeu.data->taille=10;
	jeu.data->nbTuiles = 10;
	jeu.data->nbTuilesPose=1;
	jeu.data->tuiles = malloc(MAXTUILES * sizeof(Tuile));
	jeu.data->tuiles = randomTuile(jeu.data->nbTuiles);
	jeu.data->tuileJoue.id = -1;
	jeu.data->tuileJoue.pos.x=-1;
	jeu.data->tuileJoue.pos.y=-1;

	// Création du plateau de jeu de taille n*n
	jeu.data->plateau = alloc_int_array(jeu.data->taille, jeu.data->taille);
	initPlateau(jeu.data->plateau,jeu.data->taille,0);
	// Plateau de copie
	jeu.data->plateauBis = alloc_int_array(jeu.data->taille, jeu.data->taille);
	initPlateau(jeu.data->plateauBis,jeu.data->taille,0);
	// Plateau de copie
	jeu.data->plateauIDmax = alloc_int_array(jeu.data->taille, jeu.data->taille);
	initPlateau(jeu.data->plateauIDmax,jeu.data->taille,-1);
	// Plateau de copie
	jeu.data->previous = alloc_int_array(jeu.data->taille, jeu.data->taille);
	initPlateau(jeu.data->previous,jeu.data->taille,0);
	// Plateau de copie
	jeu.data->previousIDmax = alloc_int_array(jeu.data->taille, jeu.data->taille);
	initPlateau(jeu.data->previousIDmax,jeu.data->taille,-1);

	jeu.data->previousNBCasesRec = (int*)malloc(6*sizeof(int)); 

	//Placement de la premiere tuile
	initPlacementTuileRandom(jeu.data);

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

	/* Création du rectangle de coté */
    jeu.leftPanel.x = 0;
    jeu.leftPanel.y = 0;
    jeu.leftPanel.w = SCREEN_WIDTH*0.3;
    jeu.leftPanel.h = SCREEN_HEIGHT;

    /*Création du rectangle de fond de plateau*/
	jeu.background.x=SCREEN_WIDTH*0.3;
	jeu.background.y=0;
	jeu.background.w=SCREEN_WIDTH*0.7;
	jeu.background.h=SCREEN_HEIGHT;

    // Chargement des images du jeu
	jeu.img[0] = IMG_LoadTexture(getrenderer(), "../images/lac.png");
	jeu.img[1] = IMG_LoadTexture(getrenderer(), "../images/foret.png");
	jeu.img[2] = IMG_LoadTexture(getrenderer(), "../images/ressource.png");
	jeu.img[3] = IMG_LoadTexture(getrenderer(), "../images/village.png");
	jeu.img[4] = IMG_LoadTexture(getrenderer(), "../images/plaine.png");
	jeu.img[5] = IMG_LoadTexture(getrenderer(), "../images/usine.png");

}

void drawPlateau(void)
{
    int row = 0, column = 0;
    SDL_Rect rect;

    for( ; row < jeu.data->taille; row++)
    {
        for( column=0; column < jeu.data->taille; column++)
        {
        	if ((row+column)%2 == 0 )
   		    	SDL_SetRenderDrawColor(getrenderer(), 212, 23, 43, 0);
   		    else
   		    	SDL_SetRenderDrawColor(getrenderer(), 3, 26, 36, 0);

            rect.w = SCREEN_WIDTH*0.7/jeu.data->taille;
            rect.h = SCREEN_HEIGHT/jeu.data->taille;
            rect.x = (column * rect.w)+SCREEN_WIDTH*0.3;
            rect.y = row * rect.h;
            SDL_RenderFillRect(getrenderer(), &rect);
        }
    }

    /* Affichage de la grille */
	for (int i=0;i<jeu.data->taille;i++){
		for(int j=0;j<jeu.data->taille;j++){
			if(jeu.data->plateau[i][j]!=0){
				if(jeu.data->plateau[i][j]=='L')
					SDL_RenderCopy(getrenderer(), jeu.img[0], NULL, &jeu.casePlateau[i][j].Outline);
				else if(jeu.data->plateau[i][j]=='F')
					SDL_RenderCopy(getrenderer(), jeu.img[1], NULL, &jeu.casePlateau[i][j].Outline);
				else if(jeu.data->plateau[i][j]=='R')
					SDL_RenderCopy(getrenderer(), jeu.img[2], NULL, &jeu.casePlateau[i][j].Outline);
				else if(jeu.data->plateau[i][j]=='V')
					SDL_RenderCopy(getrenderer(), jeu.img[3], NULL, &jeu.casePlateau[i][j].Outline);
				else if(jeu.data->plateau[i][j]=='P')
					SDL_RenderCopy(getrenderer(), jeu.img[4], NULL, &jeu.casePlateau[i][j].Outline);
				else if(jeu.data->plateau[i][j]=='U')
					SDL_RenderCopy(getrenderer(), jeu.img[5], NULL, &jeu.casePlateau[i][j].Outline);

			}
		}	
	}

	/* Affichage de la grille Bis*/
	for (int i=0;i<jeu.data->taille;i++){
		for(int j=0;j<jeu.data->taille;j++){
			if(jeu.data->plateauBis[i][j]!=0){
				if(jeu.data->plateauBis[i][j]=='L')
					SDL_RenderCopy(getrenderer(), jeu.img[0], NULL, &jeu.casePlateau[i][j].Outline);
				else if(jeu.data->plateauBis[i][j]=='F')
					SDL_RenderCopy(getrenderer(), jeu.img[1], NULL, &jeu.casePlateau[i][j].Outline);
				else if(jeu.data->plateauBis[i][j]=='R')
					SDL_RenderCopy(getrenderer(), jeu.img[2], NULL, &jeu.casePlateau[i][j].Outline);
				else if(jeu.data->plateauBis[i][j]=='V')
					SDL_RenderCopy(getrenderer(), jeu.img[3], NULL, &jeu.casePlateau[i][j].Outline);
				else if(jeu.data->plateauBis[i][j]=='P')
					SDL_RenderCopy(getrenderer(), jeu.img[4], NULL, &jeu.casePlateau[i][j].Outline);
				else if(jeu.data->plateauBis[i][j]=='U')
					SDL_RenderCopy(getrenderer(), jeu.img[5], NULL, &jeu.casePlateau[i][j].Outline);

			}
		}
	}

}

void drawTextGame(char * message,int x, int y){
	int texW = 0;
	int texH = 0;

	SDL_Color color = { 0, 0, 0 , 0 };
	SDL_Surface * surface = TTF_RenderText_Solid(jeu.font, message, color);
	jeu.txt_title = SDL_CreateTextureFromSurface(renderer, surface);
	
	SDL_QueryTexture(jeu.txt_title, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { x, y, texW, texH };
	SDL_RenderCopy(renderer, jeu.txt_title, NULL, &dstrect);

	SDL_FreeSurface(surface);
}

void drawTuileSelected(){
	if(jeu.data->tuileJoue.id!=-1){
		printf("OK");
	}
}

void drawGame(void){
	/* AFFICHAGE CONTOUR */
	//Affichage en blanc
    SDL_SetRenderDrawColor( getrenderer(), 255, 255, 255, 0);
    // Ajout du panneau au renderer
    SDL_RenderFillRect( getrenderer(), &jeu.leftPanel);

    //Affichage en noir
    SDL_SetRenderDrawColor( getrenderer(), 0, 0, 0, 0);
    // Ajout du fond noir
    SDL_RenderFillRect( getrenderer(), &jeu.background);

	drawTextGame("Tuile en main", 5,5);
    /* Affichage JEU */
    // Affichage du plateau
	drawPlateau();
	
	// Update de l'écran
	SDL_RenderPresent(getrenderer());
	SDL_RenderClear(getrenderer());

	// Délai pour laisser respirer le proc
	SDL_Delay(1); 
}

void cleanGame(void)
{
	for(int i=0;i<6;i++){
		SDL_DestroyTexture(jeu.img[i]);
	}
	for (int i=0; i<10; i++)
	     free(jeu.casePlateau[i]);
	free(jeu.casePlateau);

	freeGame(jeu.data,0);

	TTF_CloseFont(jeu.font);
 
}

void getInputsGame(Input *input,int* state)
{
    SDL_Event event;
 
    /* Keymapping : gère les appuis sur les touches et les enregistre
    dans la structure input */
    while (SDL_PollEvent(&event)){
        switch (event.type){
 
            case SDL_QUIT:
                *state= 0;
            break;
 
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: {
						*state = 1;
						break;
					}
					case SDLK_1: {
						if (jeu.data->tuileJoue.id == -1) {
							initTuileJoue(jeu.data);
						}
						placeTuileJoue(jeu.data);
						break;
					}
					case SDLK_a:{
						if (jeu.data->tuileJoue.id != -1) {
							nextTuileAvailable(jeu.data);
							placeTuileJoue(jeu.data);
						}
						break;
					}
					case SDLK_o:{
						changeOrientationTuileJoue(jeu.data);
						placeTuileJoue(jeu.data);
						break;
					}
					case SDLK_RETURN:{
						if (jeu.data->tuileJoue.id != -1) {
							jeu.data->tuiles[jeu.data->tuileJoue.id].orientation=jeu.data->tuileJoue.orientation;
						  	if(!placeTuile(jeu.data, jeu.data->tuileJoue.id, jeu.data->tuileJoue.pos.y, jeu.data->tuileJoue.pos.x,0)){
						    	printf("Placement réalisé\n");
						    	jeu.data->nbTuilesPose++;
				        	}
				        	nextTuileAvailable(jeu.data);
				        	placeTuileJoue(jeu.data);
						}
			        	break;
					}

					case SDLK_RIGHT: {
                        moveTuileJoue(jeu.data,1,0);
						break;
					}
					case SDLK_LEFT: {
						moveTuileJoue(jeu.data,-1,0);
						break;
					}
					case SDLK_UP: {
                        moveTuileJoue(jeu.data,0,-1);
						break;
					}
					case SDLK_DOWN: {
                        moveTuileJoue(jeu.data,0,1);
						break;
					}
                    default:{
                    	input->jump=-1;
                    	break;
                    }
                }
            break;
        }
    }
}
/* =======================================
* 			Main fonction
* ========================================*/
int startGameSDL() {
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
}
