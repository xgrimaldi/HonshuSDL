#include "score.h"
#include "plateau.h"

int getScore(Game* game,int** ville){
	/* Déclaration des variables */
	Position* posChecked = malloc((MAXTUILES * 6)*sizeof(Position));
	int nbPos=0;
	int villageMax=0,nbForet=0,nbLac=0,nbRessource=0,nbUsine=0,score=0;
	int** plateau = game->plateau;

	/*Lecture du plateau et ajout des points aux variables */
	for(int i=0;i<game->taille;i++){
		for(int j=0;j<game->taille;j++){
			if(plateau[i][j]=='V' && !inPos(i,j,posChecked,nbPos)){
				int nbCaseContigue=0;
				nbCaseContigue=Add_Case_And_Check_Around(game,'V',i,j,posChecked,&nbPos,ville);
				if (nbCaseContigue > villageMax )
					villageMax=nbCaseContigue;
			}
			else if(plateau[i][j]=='F'){
				nbForet++;
			}
			else if(plateau[i][j]=='L'){
				nbLac++;
			}
			else if(plateau[i][j]=='R'){
				nbRessource++;
			}
			else if(plateau[i][j]=='U'){
				nbUsine++;
			}
		}
	}

	/* Gestion du score final*/
	
	/*Lac*/
	if(nbLac>1){
		score+=((nbLac-1)*3);
	}
	
	/* USINE RESSOURCE */
	while(nbUsine != 0 && nbRessource != 0){
		nbRessource--;
		nbUsine--;
		score+=1;
	}

	/* Villages FORET */
	score += villageMax + (nbForet*2);

	/*Libération des ressources */
	free(posChecked);
	
	return score;
}


int inPos(int x , int y, Position* positions,int nbPos){
	for(int i=0;i<nbPos;i++){
		if (positions[i].x == x && positions[i].y == y){
			return 1;
		}
	}
	return 0;
}

int Add_Case_And_Check_Around(Game* game,char lettre,int x, int y,Position* positions,int* nbPos, int** ville){
	int nbCaseContigue = 0;
	// On ajoute la position
	positions[*nbPos].x=x;
	positions[*nbPos].y=y;
	*nbPos=*nbPos+1;
	nbCaseContigue++;

	// On teste les cases alentours en recursive
	if(inPlateau(x+1,y,game->taille) && !inPos(x+1,y,positions,*nbPos) && game->plateau[x+1][y]==lettre) {
		ville [nbCaseContigue][0]= x+1;
		ville [nbCaseContigue][1]= y;
		nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x+1,y,positions,nbPos,ville);
	}
	if(inPlateau(x-1,y,game->taille) && !inPos(x-1,y,positions,*nbPos) && game->plateau[x-1][y]==lettre) {
		ville [nbCaseContigue][0]= x-1;
		ville [nbCaseContigue][1]= y;
		nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x-1,y,positions,nbPos,ville);
	}
	if(inPlateau(x,y+1,game->taille) && !inPos(x,y+1,positions,*nbPos) && game->plateau[x][y+1]==lettre) {
		ville [nbCaseContigue][0]= x;
		ville [nbCaseContigue][1]= y+1;
		nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x,y+1,positions,nbPos,ville);
	}
	if(inPlateau(x,y-1,game->taille) && !inPos(x,y-1,positions,*nbPos) && game->plateau[x][y-1]==lettre) {
		ville [nbCaseContigue][0]= x;
		ville [nbCaseContigue][1]= y-1;
		nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x,y-1,positions,nbPos,ville);
	}
	
	return nbCaseContigue;
}

void printVillage (int** ville, int n){
	printf("les ville associé au village est :\n");
	for (int i=0; i<n;i++)
		printf("(%d,%d) ",ville[i][0],ville[i][1]);
} 

void printRules (void){
	printf("\n Afin de maximiser vos points vous pouvez :\n");
	printf("1 augmenter la taille de votre plus grand village,\n");
	printf("	Le nombre de ville dans celui-ci représente le nombre de points obtenue.\n");
	printf("2 Augmenter le nombre de Forets.Le nombre d’abres compte double dans le score.\n");
	printf("3 Augmenter le nombre de lacs.Le nombre de lacs compte triple dans le score.\n");
	printf("4 Compter les Ressources. On alloue une Ressource par Usine tant qu’il reste \n");
	printf("	des cases Ressource et des cases Usine. Chaque Ressource alloué à une Usine \n");
	printf("	rapporte 4points. Une Usine ne peut traiter qu’une Ressource et une Ressource\n");
	printf("	ne  peut être allouée qu’à une Usine.\n");
	printf("	Une Usine peut traiter une ressource d’une case qui ne lui est pas contigue\n");
}