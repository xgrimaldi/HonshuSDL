#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "game.h"

// ######################################
//	PARTIE ALLOCATION/LIBERATION MEMOIRE
// ######################################
char ***alloc_array(int x, int y) {
    char ***a = calloc(x, sizeof(char **));
    for(int i = 0; i != x; i++) {
        a[i] = calloc(y, sizeof(char *));
    }
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
		printf("|%c | %c | \n",gameTuiles[i].X_2,gameTuiles[i].X_4);
		printf("|%c | %c | \n",gameTuiles[i].X_3,gameTuiles[i].X_6);		
	}
}

void printPlateau(char*** plateau,int taille){
	printf("\n\t\t Plateau de jeu \n");
	for (int i=0;i<taille;i++){
		for(int j=0;j<taille;j++){
			printf(" %s ",plateau[i][j]);
			}	
		printf("\n");
	}
}

// ######################################
//	PARTIE INITIALISATION
// ######################################

void initPlateau(char*** gamePlateau){
	for (int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			gamePlateau[i][j]="0";
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

Game initGame(){
	// Nettoyage de l'écran
	clearScreen();

	//*********************************
	// Déclaration des variables
	//*********************************
	Game test;	
	char ***gamePlateau;	
	Tuile *gameTuiles = malloc(MAXTUILES * sizeof(Tuile));
	int nb_tuiles=0;
	int choix=0;
	//**********************************
	// Chargement des paramètres par défauts
	//**********************************
	while (nb_tuiles==0){
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
	gamePlateau = alloc_array(n, n);
	for (int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			gamePlateau[i][j]="0";
		}
	}

	// Attribution du jeu 
	test.plateau = gamePlateau;
	test.tuiles = gameTuiles;
	test.nbTuiles=nb_tuiles;
	test.taille=n;

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
