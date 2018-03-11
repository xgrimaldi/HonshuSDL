#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
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
		printf("\n ID:%d \n",gameTuiles[i].id);
		printf("|%c | %c | \n",gameTuiles[i].X_1,gameTuiles[i].X_2);
		printf("|%c | %c | \n",gameTuiles[i].X_3,gameTuiles[i].X_4);
		printf("|%c | %c | \n",gameTuiles[i].X_5,gameTuiles[i].X_6);		
	}
}

void printPlateau(int** plateau,int taille){
	int nlig=0;
	int i=0;
	printf("\n\t\t Plateau de jeu \n \t");
	
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
			else
				printf("   %c   ",plateau[i][j]);
		}	
		printf("\n");
		nlig++;
	}
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

void initPlacementTuileRandom(Game partie){
	int choix = randomMinMax(0,partie.nbTuiles);
	int pos_ligne = (partie.taille/2);
	int pos_col = (partie.taille/2);
	char placement[6]= {partie.tuiles[choix].X_1,partie.tuiles[choix].X_2,partie.tuiles[choix].X_3,partie.tuiles[choix].X_4,partie.tuiles[choix].X_5,partie.tuiles[choix].X_6};

	int ind=0;
	for (int i=pos_ligne; i<pos_ligne+3 ;i++){
		for (int j=pos_col; j<pos_col+2 ;j++){
			partie.plateau[i][j] = placement[ind];
			ind++;
		}
	}
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

int placeTuile(Game* game, Tuile tuile, int x, int y){
	switch(tuile.orientation){

		case 'N':{ 
			if(canPlaceTuile(*game, tuile, x, y)){
				game -> plateau[x][y] = tuile.X_1;
				game -> plateau[x][y+1] = tuile.X_2;
				game -> plateau[x+1][y] = tuile.X_3;
				game -> plateau[x+1][y+1] = tuile.X_4;
				game -> plateau[x+2][y] = tuile.X_5;
				game -> plateau[x+2][y+2] = tuile.X_6;
			}
			else{
				printf("Impossible de placer cette tuile ici\n");
				return EXIT_FAILURE;
			}
			break;
		}

		case 'E':{
			if(canPlaceTuile(*game, tuile, x, y)){
				game -> plateau[x][y] = tuile.X_5;
				game -> plateau[x][y+1] = tuile.X_3;
				game -> plateau[x][y+2] = tuile.X_1;
				game -> plateau[x+1][y] = tuile.X_6;
				game -> plateau[x+1][y+1] = tuile.X_4;
				game -> plateau[x+1][y+2] = tuile.X_2;
			}
			else{
				printf("Impossible de placer cette tuile ici\n");
				return EXIT_FAILURE;
			}
			break;
		}

		case 'S':{
			if(canPlaceTuile(*game, tuile, x, y)){
				game -> plateau[x][y] = tuile.X_6;
				game -> plateau[x][y+1] = tuile.X_5;
				game -> plateau[x+1][y] = tuile.X_4;
				game -> plateau[x+1][y+1] = tuile.X_3;
				game -> plateau[x+2][y] = tuile.X_2;
				game -> plateau[x+2][y+2] = tuile.X_1;
			}
			else{
				printf("Impossible de placer cette tuile ici\n");
				return EXIT_FAILURE;
			}
			break;
		}

		case 'W':{
			if(canPlaceTuile(*game, tuile, x, y)){
				game -> plateau[x][y] = tuile.X_2;
				game -> plateau[x][y+1] = tuile.X_4;
				game -> plateau[x][y+2] = tuile.X_6;
				game -> plateau[x+1][y] = tuile.X_1;
				game -> plateau[x+1][y+1] = tuile.X_3;
				game -> plateau[x+1][y+2] = tuile.X_5;
			}
			else{
				printf("Impossible de placer cette tuile ici\n");
				return EXIT_FAILURE;
			}
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
	if(!(0 <= x <n) || !(0 <= y <n)){
		return 0;
	}
	else return 1;
}

int canPlaceTuile(Game game, Tuile tuile, int x, int y){ //Reste a traiter le cas de recouvrement complet d'une autre tuile (interdit)
	int recouvreUneTuile = 0;
	if(tuile.orientation =='N' || tuile.orientation == 'S'){
		
		if (game.plateau[x][y] != "0") recouvreUneTuile = 1;
		else if(game.plateau[x][y+1] != "0") recouvreUneTuile = 1;
		else if(game.plateau[x+1][y] != "0") recouvreUneTuile = 1;
		else if(game.plateau[x+1][y+1] != "0") recouvreUneTuile = 1;
		else if(game.plateau[x+2][y] != "0") recouvreUneTuile = 1;
		else if(game.plateau[x+2][y+1] != "0") recouvreUneTuile = 1;

		if (!(inPlateau(x, y)) || game.plateau[x][y] == 'L') return 0;
		if (!(inPlateau(x, y+1)) || game.plateau[x][y+1] == 'L') return 0;
		if (!(inPlateau(x+1, y)) || game.plateau[x+1][y] == 'L') return 0;
		if (!(inPlateau(x+1, y+1)) || game.plateau[x+1][y+1] == 'L') return 0;
		if (!(inPlateau(x+2, y)) || game.plateau[x+2][y] == 'L') return 0;
		if (!(inPlateau(x+2, y+1)) || game.plateau[x+2][y+1] == 'L') return 0;
	}

	else{
		if (game.plateau[x][y] !="0") recouvreUneTuile = 1;
		else if(game.plateau[x][y+1] !="0") recouvreUneTuile = 1;
		else if(game.plateau[x][y+2] !="0") recouvreUneTuile = 1;
		else if(game.plateau[x+1][y] !="0") recouvreUneTuile = 1;
		else if(game.plateau[x+1][y+1] !="0") recouvreUneTuile = 1;
		else if(game.plateau[x+1][y+2] !="0") recouvreUneTuile = 1;

		if (!(inPlateau(x, y)) || game.plateau[x][y] == 'L') return 0;
		if (!(inPlateau(x, y+1)) || game.plateau[x][y+1] == 'L') return 0;
		if (!(inPlateau(x, y+2)) || game.plateau[x][y+2] == 'L') return 0;
		if (!(inPlateau(x+1, y)) || game.plateau[x+1][y] == 'L') return 0;
		if (!(inPlateau(x+1, y+1)) || game.plateau[x+1][y+1] == 'L') return 0;
		if (!(inPlateau(x+1, y+2)) || game.plateau[x+1][y+2] == 'L') return 0;
	}

	return recouvreUneTuile;
}

// ######################################
//	PARTIE JEU
// ######################################

Game initGame(){
	// Nettoyage de l'écran
	clearScreen();

	//*********************************
	// Déclaration des variables
	//*********************************
	Game test;	
	int **gamePlateau;	
	Tuile *gameTuiles = malloc(MAXTUILES * sizeof(Tuile));
	int nb_tuiles=0;
	int choix=0;
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
				printf("A développer");
				break;
			}
			case 2:{ 
				char filepath[1024]={};
				printf("Quel est le chemin du fichier de Tuiles ? ...\n");
				scanf("%s",filepath);
				// Chargement d'un fichier de tuiles
				//resetTuiles(gameTuiles);
				if(filepath!=NULL){
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
	test.plateau = gamePlateau;
	test.tuiles = gameTuiles;
	test.nbTuiles=nb_tuiles;
	test.taille=n;

	//Placement de la premiere tuile
	initPlacementTuileRandom(test);

	return test;
}


void startGame(Game game){
	//**********************************
	// Lancement du jeu 
	//**********************************
	int stop = 0;
	int choix=0;
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
				if(game.nbTuiles > 0)
					printTuiles(game.tuiles,game.nbTuiles);
				else
					printf("Aucune tuile: Vérifier le paramètrage ! \n");
				break;
			}
			case 2:{
				clearScreen();
				// Affichage du plateau
				printPlateau(game.plateau,n);
				break;
			}
			case 3:{
				// Poser une tuile

			}
			case 0:{
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
	srand(time(NULL));
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
