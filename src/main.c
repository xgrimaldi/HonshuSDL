/*
* PROJET INFO - LES TUILEURS
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "game.h"

int main(int argc, char *argv[]) {

	//*********************************
	// Déclaration des variables
	//*********************************

	char ***gamePlateau;
	int choix=0;
	int nb_tuiles=0;
	Tuile gameTuiles[MAXTUILES];

	//**********************************
	// Chargement des paramètres par défauts
	//**********************************
	
	// Si argument donné chargement des tuiles
	if(argc >1){
		nb_tuiles=LoadTuiles(argv[1],gameTuiles);
	}

	// Création du plateau de jeu de taille n*n
	gamePlateau = alloc_array(n, n);
	for (int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			gamePlateau[i][j]="0";
		}
	}

	//**********************************
	// Lancement du jeu 
	//**********************************
	int stop = 0;
	while(stop == 0){
		printf("\nQue voulez-vous faire ?\n");
		printf("0 - Quitter le programme\n");
	 	printf("1 - Voir les tuiles paramètrés\n");
		printf("2 - Voir le tableau de jeu\n");
		printf("3 - Charger un fichier de tuiles\n");
		scanf("%d",&choix);
		switch(choix){
			case 1:{
				// Affichage des tuiles disponibles 
				if(nb_tuiles > 0)
					printTuiles(gameTuiles,nb_tuiles);
				else
					printf("Aucune tuile: Vérifier le paramètrage ! \n");
				break;
			}
			case 2:{
				// Affichage du plateau
				printPlateau(gamePlateau,n);
				break;
			}
			case 3:{ 
				char filepath[200]={};
				printf("Quel est le chemin du fichier de Tuiles ? ...\n");
				scanf("%s",filepath);
				// Chargement d'un fichier de tuiles
				//resetTuiles(gameTuiles);
				if(filepath!=NULL)
					nb_tuiles=LoadTuiles(filepath,gameTuiles);
				break;
			}
			case 0:{
				stop = 1;
				break;
			}
		}
	}

	return 0;
}
