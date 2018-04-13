#include "score.h"
#include "plateau.h"

int getScore(Game* game){
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
				nbCaseContigue=Add_Case_And_Check_Around(game,'V',i,j,posChecked,&nbPos);
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

int Add_Case_And_Check_Around(Game* game,char lettre,int x, int y,Position* positions,int* nbPos){
	int nbCaseContigue = 0;
	// On ajoute la position
	positions[*nbPos].x=x;
	positions[*nbPos].y=y;
	*nbPos=*nbPos+1;
	nbCaseContigue++;

	// On teste les cases alentours en recursive
	if(inPlateau(x+1,y,game->taille) && !inPos(x+1,y,positions,*nbPos) && game->plateau[x+1][y]==lettre) nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x+1,y,positions,nbPos);
	if(inPlateau(x-1,y,game->taille) && !inPos(x-1,y,positions,*nbPos) && game->plateau[x-1][y]==lettre) nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x-1,y,positions,nbPos);
	if(inPlateau(x,y+1,game->taille) && !inPos(x,y+1,positions,*nbPos) && game->plateau[x][y+1]==lettre) nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x,y+1,positions,nbPos);
	if(inPlateau(x,y-1,game->taille) && !inPos(x,y-1,positions,*nbPos) && game->plateau[x][y-1]==lettre) nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x,y-1,positions,nbPos);
	
	return nbCaseContigue;
}