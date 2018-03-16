#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "game.h"

// ######################################
//	PARTIE ALLOCATION/LIBERATION MEMOIRE
// ######################################
int **alloc_int_array(int x, int y) {
	int **a = (int **)malloc(x* sizeof(int *));
	for (int i=0; i<x; i++)
	     a[i] = (int *)malloc(y * sizeof(int));
	 return a;
}

// ######################################
//	PARTIE AFFICHAGE
// ######################################

void printTuiles(Tuile gameTuiles[MAXTUILES],int nbTuiles){
	printf("\n\t\t Tuiles paramètrées\n");
	for(int i=0;i<nbTuiles;i++){
		printf("\n %s ID:%d%s \n",Color_Bold_White,gameTuiles[i].id,Color_end);
		printf("| ");
		printIntToCharColor(gameTuiles[i].X_1);
		printf(" | ");
		printIntToCharColor(gameTuiles[i].X_2);
		printf(" |\n");
		printf("| ");
		printIntToCharColor(gameTuiles[i].X_3);
		printf(" | ");
		printIntToCharColor(gameTuiles[i].X_4);
		printf(" |\n");
		printf("| ");
		printIntToCharColor(gameTuiles[i].X_5);
		printf(" | ");
		printIntToCharColor(gameTuiles[i].X_6);
		printf(" |\n");
	}
}

void printPlateau(int** plateau,int taille){
	int nlig=0;
	int i=0;
	printf("\n\t\t Plateau de jeu \n \t ");
	
	for (int ncol=65;ncol<65+taille;ncol++){
		printf("   \033[1m%c\033[0m   ",ncol);
	}

	/* Affichage de la grille */
    printf ("\n\t+");
    for (i=0; i<taille;i++)
        printf ("------+");
    printf ("\n"); 

	for (int i=0;i<taille;i++){
		printf(" \033[1m%d\033[0m\t|",nlig);
		for(int j=0;j<taille;j++){
			if(plateau[i][j]==0)
				printf("   -   ");
			else{
				printf("   ");
				printIntToCharColor(plateau[i][j]);
				printf("   ");
			}
		}	
		printf("\n");
		nlig++;
	}
}

void printIntToCharColor(int car){
	if (car=='L')
		printf("%s%c%s",Color_Bold_Blue,car,Color_end);
	else if (car=='P')
		printf("%s%c%s",Color_Bold_Green,car,Color_end);
	else if (car=='F')
		printf("%s%c%s",Color_Bold_Green,car,Color_end);
	else if (car=='V')
		printf("%s%c%s",Color_Bold_Magenta,car,Color_end);
	else if (car=='U')
		printf("%s%c%s",Color_Bold_Yellow,car,Color_end);
	else if (car=='R')
		printf("%s%c%s",Color_Bold_Red,car,Color_end);
	else
		printf("%s%c%s",Color_Bold_White,car,Color_end);
}
// ######################################
//	PARTIE INITIALISATION
// ######################################

void initPlateau(int** gamePlateau){
	for (int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			gamePlateau[i][j]=0;
		}
	}
}


void initPlacementTuileRandom(Game* partie){
	int choix = randomMinMax(0,partie->nbTuiles);
	int pos_ligne = (partie->taille/2);
	int pos_col = (partie->taille/2);
	char placement[6]= {partie->tuiles[choix].X_1,partie->tuiles[choix].X_2,partie->tuiles[choix].X_3,partie->tuiles[choix].X_4,partie->tuiles[choix].X_5,partie->tuiles[choix].X_6};

	int ind=0;
	for (int i=pos_ligne; i<pos_ligne+3 ;i++){
		for (int j=pos_col; j<pos_col+2 ;j++){
			partie->plateau[i][j] = placement[ind];
			ind++;
		}
	}
}

Tuile* randomTuile(int nb){
	int i;
	char cases[6] = "LPFVUR";
	Tuile* tabTuile = malloc(nb*sizeof(Tuile));
	for(i = 0; i < nb; i++){
		tabTuile[i].id = i;
		tabTuile[i].X_1 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_2 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_3 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_4 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_5 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_6 = cases[randomMinMax(0, 5)];
	}
	return tabTuile;
}

int LoadTuiles(char* filepath,Tuile gameTuiles[MAXTUILES]){
	//******************************
	// Initialisation des variables
	//******************************
	FILE* fichier = NULL;
	int nbTuiles=0;

	//******************************
	// Vérification des arguments
	//******************************
	fichier = fopen(filepath, "r+");

	//******************************
	// Récupération des tuiles du jeu
	//******************************

	if (fichier != NULL){
      	char line[100]; 
     	int id_tuile;

     	fgets ( line, sizeof line, fichier );
		// Première ligne, récupération du nombre de tuiles
		nbTuiles=atoi(line);
		
     	while ( fgets ( line, sizeof line, fichier ) != NULL ){
        	//Récupération de l'id de la tuile
        	id_tuile=atoi(line);
        	gameTuiles[id_tuile].id=id_tuile;
        	//Récupération de la ligne suivante (Partie tuile 1/3)
    		fgets ( line, sizeof line, fichier );
			gameTuiles[id_tuile].X_1=line[0];
        	gameTuiles[id_tuile].X_2=line[2];
        	//Récupération de la ligne suivante (Partie tuile 2/3)	        	
    		fgets ( line, sizeof line, fichier );        	
        	gameTuiles[id_tuile].X_3 = line[0];
        	gameTuiles[id_tuile].X_4 = line[2];
        	//Récupération de la ligne suivante (Partie tuile 3/3)	        	
    		fgets ( line, sizeof line, fichier );
        	gameTuiles[id_tuile].X_5 = line[0];
        	gameTuiles[id_tuile].X_6 = line[2];
			// Changement de l'orientation
			gameTuiles[id_tuile].orientation='V';
		}
			printf("Un nombre de %d tuiles a été généré.\n",nbTuiles);
			return nbTuiles;
	}
	else{
	       	// On affiche un message d'erreur si on veut
	       	printf("Fichier vide ou inconnu\n");
	       	return 0;
	}
}

// ######################################
//	PARTIE JEU
// ######################################

int placeTuile(Game* game, int id, int x, int y){ //Les coordonées de la position sont celles de la case la plus en haut à gauche en tenant compte de l'orientation
	Tuile tuile = game -> tuiles[id];

	if(!canPlaceTuile(*game, id, x, y)){
		printf("Impossible de placer cette tuile ici (vous recouvrez un lac ou aucune tuile !)\n");
		return EXIT_FAILURE;
	}

	switch(game -> tuiles[id].orientation){

		case 'N':{ 
			game -> plateau[x][y] = tuile.X_1;
			game -> plateau[x][y+1] = tuile.X_2;
			game -> plateau[x+1][y] = tuile.X_3;
			game -> plateau[x+1][y+1] = tuile.X_4;
			game -> plateau[x+2][y] = tuile.X_5;
			game -> plateau[x+2][y+1] = tuile.X_6;
			break;
		}

		case 'E':{
			game -> plateau[x][y] = tuile.X_5;
			game -> plateau[x][y+1] = tuile.X_3;
			game -> plateau[x][y+2] = tuile.X_1;
			game -> plateau[x+1][y] = tuile.X_6;
			game -> plateau[x+1][y+1] = tuile.X_4;
			game -> plateau[x+1][y+2] = tuile.X_2;
			break;
		}

		case 'S':{
			game -> plateau[x][y] = tuile.X_6;
			game -> plateau[x][y+1] = tuile.X_5;
			game -> plateau[x+1][y] = tuile.X_4;
			game -> plateau[x+1][y+1] = tuile.X_3;
			game -> plateau[x+2][y] = tuile.X_2;
			game -> plateau[x+2][y+1] = tuile.X_1;
			break;
		}

		case 'W':{
			game -> plateau[x][y] = tuile.X_2;
			game -> plateau[x][y+1] = tuile.X_4;
			game -> plateau[x][y+2] = tuile.X_6;
			game -> plateau[x+1][y] = tuile.X_1;
			game -> plateau[x+1][y+1] = tuile.X_3;
			game -> plateau[x+1][y+2] = tuile.X_5;
			break;
		}

		default:{
			printf("Erreur d'orientation de la tuile (Utiliser 'N', 'E', 'S' ou 'W' uniquement)\n");
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

int inPlateau(int x, int y){
	if( !((0 <= x) && (x < n)) || !((0 <= y) && (y < n)) ){
		printf("La case (%d, %d) ne fait pas partie du plateau de jeu !\n", x, y);
		return 0;
	}
	else return 1;
}

int canPlaceTuile(Game game, int id, int x, int y){ //Reste a traiter le cas de recouvrement complet d'une autre tuile (interdit)
	int recouvreUneTuile = 0;
	char orientation = game.tuiles[id].orientation;
	if(orientation =='N' || orientation == 'S'){ //L'ordre des cases n'a pas d'importance pour des orientations de même axe
		
		if (game.plateau[x][y] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x][y+1] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+1][y] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+1][y+1] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+2][y] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+2][y+1] != 0) recouvreUneTuile = 1;

		if (!(inPlateau(x, y)) || game.plateau[x][y] == 'L') return 0;
		if (!(inPlateau(x, y+1)) || game.plateau[x][y+1] == 'L') return 0;
		if (!(inPlateau(x+1, y)) || game.plateau[x+1][y] == 'L') return 0;
		if (!(inPlateau(x+1, y+1)) || game.plateau[x+1][y+1] == 'L') return 0;
		if (!(inPlateau(x+2, y)) || game.plateau[x+2][y] == 'L') return 0;
		if (!(inPlateau(x+2, y+1)) || game.plateau[x+2][y+1] == 'L') return 0;
	}

	else{
		if (game.plateau[x][y] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x][y+1] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x][y+2] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+1][y] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+1][y+1] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+1][y+2] != 0) recouvreUneTuile = 1;

		if (!(inPlateau(x, y)) || game.plateau[x][y] == 'L') return 0;
		if (!(inPlateau(x, y+1)) || game.plateau[x][y+1] == 'L') return 0;
		if (!(inPlateau(x, y+2)) || game.plateau[x][y+2] == 'L') return 0;
		if (!(inPlateau(x+1, y)) || game.plateau[x+1][y] == 'L') return 0;
		if (!(inPlateau(x+1, y+1)) || game.plateau[x+1][y+1] == 'L') return 0;
		if (!(inPlateau(x+1, y+2)) || game.plateau[x+1][y+2] == 'L') return 0;
	}

	if(!recouvreUneTuile) printf("Aucune tuile n'est recouverte !\n");

	return recouvreUneTuile;
}

// ######################################
//	PARTIE JEU
// ######################################

void startGame(){
	// Nettoyage de l'écran
	clearScreen();

	//*********************************
	// Déclaration des variables
	//************************ws*********
	Game* game=malloc(sizeof(Game));	
	int **gamePlateau;	
	Tuile *gameTuiles = malloc(MAXTUILES * sizeof(Tuile));
	int nb_tuiles=0;
	int choix=0; 
	int id_Tuile = -1;
	int x = -1;
	char y = '^';
	char orientation = 'A';
	int accepte = 0;
	//**********************************
	// Chargement des paramètres par défauts
	//**********************************
	while (nb_tuiles==0){
		LOG_BOLDRED("\t\t\t\tParamètrage des tuiles \n");
		printf("Quelles tuiles voulez-vous utilisez ?\n");
		printf("1 - Des tuiles générées aléatoirement \n");
		printf("2 - Des tuiles générées à partir d'un fichier \n");
		scanf("%d",&choix);
		switch(choix){
			case 1:{
				printf("Combien de tuiles voulez vous générer ? ");
				scanf("%d", &nb_tuiles);
				if(nb_tuiles <= 0){
					printf("Veuillez saisir un nombre entre 1 et %d\n", MAXTUILES);
					printf("\n");
					nb_tuiles = 0;
				}
				else{
					clearScreen();
					gameTuiles = randomTuile(nb_tuiles);
				}
				break;
			}
			case 2:{ 
				char filepath[1024]={};
				printf("Quel est le chemin du fichier de Tuiles ? ...\n");
				scanf("%s",filepath);
				// Chargement d'un fichier de tuiles
				//resetTuiles(gameTuiles);
				if(filepath!=NULL){
					clearScreen();
					nb_tuiles=LoadTuiles(filepath,gameTuiles);
				}
				break;
			}
		}
	}

	// Création du plateau de jeu de taille n*n
	gamePlateau = alloc_int_array(n, n);
	initPlateau(gamePlateau);

	// Attribution du jeu 
	game->plateau=gamePlateau;
	game->tuiles = gameTuiles;
	game->nbTuiles=nb_tuiles;
	game->taille=n;

	//Placement de la premiere tuile
	initPlacementTuileRandom(game);


	//**********************************
	// Lancement du jeu 
	//**********************************
	int stop = 0;
	choix=0;
	while(stop == 0){

		printf("\nQue voulez-vous faire ?\n");
		printf("0 - Quitter la partie\n");
	 	printf("1 - Voir les tuiles paramètrés\n");
	 	printf("2 - Voir le plateau de jeu\n");
	 	printf("3 - Poser une tuile\n");
		scanf("%d",&choix);
		switch(choix){
			case 1:{
				// Affichage des tuiles disponibles 
				if(game->nbTuiles > 0)
					printTuiles(game->tuiles,game->nbTuiles);
				else
					printf("Aucune tuile: Vérifier le paramètrage ! \n");
				break;
			}
			case 2:{
				clearScreen();
				// Affichage du plateau
				printPlateau(game->plateau,n);
				break;
			}
			case 3:{
				while(accepte == 0){ //ID
					printf("Quelle tuile voulez vous placer ? : ");
					scanf("%d", &id_Tuile);
					if(id_Tuile < 0 || id_Tuile > game->nbTuiles) printf("ID incorrect ! Saisir un ID entre 0 et %d\n", game->nbTuiles);
					else accepte = 1;
				}
				accepte =  0;
				while(accepte == 0 ){ //ordonée
					printf("À quelle ordonée voulez vous placer la tuile %d : ", id_Tuile);
					scanf("%d", &x);
					if(x < 0 || x >= n) printf("Ordonée incorrect ! Saisir un nombre entre 0 et %d\n", n);
					else accepte = 1;
				}
				accepte = 0;
				while(accepte == 0){ //abcisse
					printf("À quelle abcisse voulez vous placer la tuile %d : ", id_Tuile);
					scanf(" %c", &y);
					if(!(y >= 97 && y < 97+n) && !(y >= 65 && y < 65+n)) printf("Abcisse incorrect ! Saisir une lettre entre A et %c\n", (char)(65+n-1)); // On est contraint de supposer n <= 26
					else {
						accepte = 1;
						if(y >= 97 && y < 97+n){ //ici y est une minuscule
							y -= 97;
						}
						else y -= 65;
					}
				}
				accepte = 0;
				while(accepte == 0){ //orientation
					printf("Quelle orientation pour la tuile %d : ", id_Tuile);
					scanf(" %c", &orientation);
					if( orientation != 'N' && orientation != 'n' && orientation != 'E' && orientation != 'e' && orientation != 'S' && orientation != 's' && orientation != 'W' && orientation != 'w'){
						printf("Orientation inconnue (saisir 'N', 'E', 'S' ou 'W')\n"); // On est contraint de supposer n <= 26
					}
					else {
						if(orientation > 90){ //Si orientation est écrit en minuscule{
							orientation -= 32; //On la convertit en minuscule
						}
						accepte = 1;
						game->tuiles[id_Tuile].orientation = orientation;
					}
				}
				if(!placeTuile(game, id_Tuile, x, (int) y)){
					printf("Placement réalisé\n");
				}
				else{
					printf("Placement refusé\n"	);
				}
				accepte = 0;
				break;
			}
			case 0:{
				for(int i=0;i<game->taille;i++){
					free(game->plateau[i]);
				}
				free(game->plateau);;
				free(game->tuiles);
				free(game);
				stop = 1;
				break;
			}
		}
	}
}
// ######################################
//	PARTIE DIVERS
// ######################################

int randomMinMax(int a,int b){
	int r = (rand() % (b - a + 1)) + a;
	return r;
}

void HonshuScreen(){
	printf(" \n");
	printf("	 __    __    ______   .__   __.      _______. __    __   __    __  \n");
	printf("	|  |  |  |  /  __  \\  |  \\ |  |     /       ||  |  |  | |  |  |  | \n");
	printf("	|  |__|  | |  |  |  | |   \\|  |    |   (----`|  |__|  | |  |  |  | \n");
	printf("	|   __   | |  |  |  | |  . `  |     \\   \\    |   __   | |  |  |  | \n");
	printf("	|  |  |  | |  `--'  | |  |\\   | .----)   |   |  |  |  | |  `--'  | \n");
	printf("	|__|  |__|  \\______/  |__| \\__| |_______/    |__|  |__|  \\______/  \n");
	printf("\n");
}

void clearScreen() {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}