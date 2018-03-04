#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

char ***alloc_array(int x, int y) {
    char ***a = calloc(x, sizeof(char **));
    for(int i = 0; i != x; i++) {
        a[i] = calloc(y, sizeof(char *));
    }
    return a;
}

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

/*
void resetTuiles(Tuile gameTuiles[MAXTUILES]){

}
*/

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