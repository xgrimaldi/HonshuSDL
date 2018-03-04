/*
* PROJET INFO - LES TUILEURS
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define n 20
#define MAXTUILES 100

#define L "LAC"
#define P "PLAINE"
#define F "FORET"
#define V "VILLE"
#define U "USINE"
#define R "RESSOURCE"

/*
 * Exemple de structure
 */

typedef struct {	
	int id;
	char orientation;
	char X_1;
	char X_2;
	char X_3;
	char X_4;
	char X_5;
	char X_6;
} Tuile;

char ***alloc_array(int x, int y) {
    char ***a = calloc(x, sizeof(char **));
    for(int i = 0; i != x; i++) {
        a[i] = calloc(y, sizeof(char *));
    }
    return a;
}

void printTuiles(Tuile gameTuiles[MAXTUILES],int nbTuiles){
	for(int i=0;i<nbTuiles;i++){
		printf("\n ID:%d \n",gameTuiles[i].id);
		printf("|%c | %c | \n",gameTuiles[i].X_1,gameTuiles[i].X_2);
		printf("|%c | %c | \n",gameTuiles[i].X_2,gameTuiles[i].X_4);
		printf("|%c | %c | \n",gameTuiles[i].X_3,gameTuiles[i].X_6);		
	}
}

void printPlateau(char*** plateau,int taille){
	for (int i=0;i<taille;i++){
		for(int j=0;j<taille;j++){
			printf(" %s ",plateau[i][j]);
			}	
		printf("\n");
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
			printf("Un nombre de %d a été généré\n",nbTuiles);
			return nbTuiles;
	}
	else{
	       	// On affiche un message d'erreur si on veut
	       	printf("Fichier vide");
	       	return 0;
	}
}

int main(int argc, char *argv[]) {

	// Déclaration des variables
	Tuile gameTuiles[MAXTUILES];
	char ***gamePlateau;
	int choix;
	int nb_tuiles;
	// Génération des tuiles par fichier
	if(argc >=1){
		nb_tuiles=LoadTuiles(argv[1],gameTuiles);
	}

	// Création du plateau de jeu de taille n*n
	gamePlateau = alloc_array(n, n);

	for (int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			gamePlateau[i][j]="0";
		}
	}

	printf("Que voulez-vous faire ?\n");
 	printf("1 - Voir les tuiles disponibles\n");
	printf("2 - Voir le tableau de jeu\n");
	scanf("%d",&choix);
	switch(choix){
		case 1:
			printTuiles(gameTuiles,nb_tuiles);
			break;
		case 2:
			// Affichage du plateau
			printf("\n\t\t Affichage du plateau de jeu\n");
			printPlateau(gamePlateau,n);
			break;
	}


	return 0;
}
