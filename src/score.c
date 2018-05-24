#include "score.h"
#include "plateau.h"

int Add_Case_And_Check_Around(Game* game,char lettre,int x, int y,Position* positions,int* nbPos, int** ville,int solv, int c);


int getScore(Game* game, int** ville, int solv, int* villageMax){
	/* Déclaration des variables */
	int variante = game->variante;
	Position* posCheckedVillage = malloc((MAXTUILES * 6)*sizeof(Position));
	Position* posCheckedPlains = malloc((MAXTUILES * 6)*sizeof(Position));
	int nbPosVillage=0;
	int nbPosPlaine=0;
	int nbForet=0,nbLac=0,nbRessource=0,nbUsine=0,score=0, nbQuadrioPlaine=0;
	int** plateau = game->plateau;
	*villageMax = 0;

	/*Lecture du plateau et ajout des points aux variables */
	for(int i=0;i<game->taille;i++){
		for(int j=0;j<game->taille;j++){
			/*village*/
			if(plateau[i][j]=='V' && !inPos(i,j,posCheckedVillage,nbPosVillage)){
				int nbCaseContigueVillage=0;
				ville[0][0]=i;
				ville[0][1]=j;
				nbCaseContigueVillage=Add_Case_And_Check_Around(game,'V',i,j,posCheckedVillage,&nbPosVillage,ville,solv,1);
				if (nbCaseContigueVillage > *villageMax ){
					ville[0][0]=i;
					ville[0][1]=j;
					*villageMax=nbCaseContigueVillage;
				}
			}
			/*plaine*/
			else if(plateau[i][j]=='P'){
				int nbCaseContiguePlaine=0;
				nbCaseContiguePlaine=Add_Case_And_Check_Around(game,'P',i,j,posCheckedPlains,&nbPosPlaine,ville,solv,1);
				if (nbCaseContiguePlaine >= 4){
					nbQuadrioPlaine++;
				}
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

	/*
	printf("#########\n");
	printf("nbLac : %d\n", nbLac);
	printf("nbQuadrioPlaine : %d\n", nbQuadrioPlaine);
	printf("nbUsine : %d\n", nbUsine);
	printf("nbRessource : %d\n", nbRessource);
	printf("nbForet : %d\n", nbForet);
	printf("villageMax : %d\n", *villageMax);
	printf("nbVillageCarre : %d\n", nombreCarre(game, *villageMax, ville, solv));
	printf("#########\n");
	*/

	switch(variante){
		case 0:
			score+=2*nbLac;
			while(nbUsine != 0 && nbRessource != 0){ //USINE & RESSOURCE
				nbRessource--;
				nbUsine--;
				score+=4;
			}
			score += *villageMax + (nbForet*2); //VILLAGE & FORET
			break;


		case 1:
			if(nbLac>1){ //LAC
				score+=((nbLac-1)*3);
			}
			while(nbUsine != 0 && nbRessource != 0){ //USINE & RESSOURCE
				nbRessource--;
				nbUsine--;
				score+=4;
			}
			score += 4*nbQuadrioPlaine; //PLAINE
			score += *villageMax + (nbForet*2); //VILLAGE & FORET
			break;

		case 2:
			if(nbLac>1){ //LAC
				score+=((nbLac-1)*3);
			}
			nbUsine*=2; //C'est comme dire qu'il y a deux fois plus d'usine
			while(nbUsine != 0 && nbRessource != 0){ //USINE & RESSOURCE
				nbRessource--;
				nbUsine--;
				score+=4;
			}
			score += *villageMax + (nbForet*2); //VILLAGE & FORET
			break;

		case 3:
			if(nbLac>1){ //LAC
				score+=((nbLac-1)*3);
			}
			while(nbUsine != 0 && nbRessource != 0){ //USINE & RESSOURCE
				nbRessource--;
				nbUsine--;
				score+=4;
			}
			score += *villageMax + (nbForet*2); //VILLAGE & FORET
			score += 4*nombreCarre(game, *villageMax, ville, solv); //CARRE DE VILLAGE
			break;

		case 4:
			if(nbLac>1){ //LAC
				score+=((nbLac-1)*3);
			}
			while(nbUsine != 0 && nbRessource != 0){ //USINE & RESSOURCE
				nbRessource--;
				nbUsine--;
				score+=4;
			}
			score += *villageMax; //VILLAGE
			if(nbForet<5){ //FORET
				score+=nbForet;
			}
			else{
				score+=5;
			}
			break;

		case 5:
			if(nbLac>1){ //LAC
				score+=((nbLac-1)*3);
			}
			while(nbUsine != 0 && nbRessource != 0){ //USINE & RESSOURCE
				nbRessource--;
				nbUsine--;
				score+=4;
			}
			score += *villageMax + (nbForet*2); //VILLAGE & FORET
			break;

		default:
			printf("Variante invalide : %d\n", variante);
			score = -1;
		}

	free(posCheckedVillage);
	free(posCheckedPlains);	

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

int inTown(int x, int y, int** ville, int tailleVille){
	for(int i=0; i<tailleVille; i++){
		if(ville[i][0] == x && ville[i][1] == y){
			return 1;
		}
	}
	return 0;
}

int Add_Case_And_Check_Around(Game* game,char lettre,int x, int y,Position* positions,int* nbPos, int** ville,int solv, int c){
	int nbCaseContigue = 0;
	// On ajoute la position
	positions[*nbPos].x=x;
	positions[*nbPos].y=y;
	*nbPos=*nbPos+1;
	nbCaseContigue++;

	// On teste les cases alentours en recursive
	if(lettre != 'P'){
		if(inPlateau(x+1,y,game->taille,solv) && !inPos(x+1,y,positions,*nbPos) && game->plateau[x+1][y]==lettre) {
			ville [c][0]= x+1;
			ville [c][1]= y;
			c++;
			nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x+1,y,positions,nbPos,ville,solv,c);
		}
		if(inPlateau(x-1,y,game->taille,solv) && !	inPos(x-1,y,positions,*nbPos) && game->plateau[x-1][y]==lettre) {
			ville [c][0]= x-1;
			ville [c][1]= y;
			c++;
			nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x-1,y,positions,nbPos,ville,solv,c);
		}
		if(inPlateau(x,y+1,game->taille,solv) && !inPos(x,y+1,positions,*nbPos) && game->plateau[x][y+1]==lettre) {
			ville [c][0]= x;
			ville [c][1]= y+1;
			c++;
			nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x,y+1,positions,nbPos,ville,solv,c);
		}
		if(inPlateau(x,y-1,game->taille,solv) && !inPos(x,y-1,positions,*nbPos) && game->plateau[x][y-1]==lettre) {
			ville [c][0]= x;
			ville [c][1]= y-1;
			c++;
			nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x,y-1,positions,nbPos,ville,solv,c);
		}
	}
	else{
		if(inPlateau(x+1,y,game->taille,solv) && !inPos(x+1,y,positions,*nbPos) && game->plateau[x+1][y]==lettre) {
			nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x+1,y,positions,nbPos,ville,solv,c);
		}
		if(inPlateau(x-1,y,game->taille,solv) && !inPos(x-1,y,positions,*nbPos) && game->plateau[x-1][y]==lettre) {
			nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x-1,y,positions,nbPos,ville,solv,c);
		}
		if(inPlateau(x,y+1,game->taille,solv) && !inPos(x,y+1,positions,*nbPos) && game->plateau[x][y+1]==lettre) {
			nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x,y+1,positions,nbPos,ville,solv,c);
		}
		if(inPlateau(x,y-1,game->taille,solv) && !inPos(x,y-1,positions,*nbPos) && game->plateau[x][y-1]==lettre) {
			nbCaseContigue+=Add_Case_And_Check_Around(game,lettre,x,y-1,positions,nbPos,ville,solv,c);
		}
	}
	
	return nbCaseContigue;
}


int nombreCarre (Game* game, int maxTown, int** ville, int solv){
	int carre = 0;
	for(int x = 0;x<game->taille;x++){
		for(int y = 0;y<game->taille;y++){
			if(game->plateau[x][y]=='V'){
				if ((inTown(x, y, ville, maxTown))){
					if ((inPlateau(x+1,y,game->taille,solv) && game->plateau[x+1][y]=='V') && 
						(inPlateau(x,y+1,game->taille,solv) && game->plateau[x][y+1]=='V') &&
						(inPlateau(x+1,y+1,game->taille,solv) && game->plateau[x+1][y+1]=='V'))
						carre++;

					else if ((inPlateau(x+1,y-1,game->taille,solv) && game->plateau[x+1][y-1]=='V') && 
						(inPlateau(x,y-1,game->taille,solv) && game->plateau[x][y-1]=='V') &&
						(inPlateau(x+1,y,game->taille,solv) && game->plateau[x+1][y]=='V') )
						carre++;
					
					else if ((inPlateau(x,y-1,game->taille,solv) && game->plateau[x][y-1]=='V') && 
						(inPlateau(x-1,y-1,game->taille,solv) && game->plateau[x-1][y-1]=='V') &&
						(inPlateau(x-1,y,game->taille,solv) && game->plateau[x-1][y]=='V')) 
						carre++;

					else if ((inPlateau(x-1,y,game->taille,solv) && game->plateau[x-1][y]=='V') && 
						(inPlateau(x-1,y+1,game->taille,solv) && game->plateau[x-1][y+1]=='V') &&
						(inPlateau(x,y+1,game->taille,solv) && game->plateau[x][y+1]=='V'))
						carre++;
					}
				}
			}
		}
	return (carre/4);
}

void printVillage (int** ville, int n){
	printf("les villages associé à la ville sont :\n");
	for (int i=0; i<n;i++)
		printf("(%d,%c) ",ville[i][0],(char) (97+ville[i][1]));
	printf("\n");
} 

void printRules (int variante){
	printf("\nVariante des règles (version %d): \n", variante);
	printf("Afin de maximiser vos points vous pouvez :\n");
	if(variante==3){
		printf("1/ Augmenter la taille de votre plus grand village et réaliser à l'interieur de celui-ci \n");
		printf("   des carrés. Le nombre de ville dans celui-ci représente le nombre de points obtenue, \n");
		printf("   et chaque carré de 4 villages augmente le score de 4.\n");
	}
	else{
		printf("1/ Augmenter la taille de votre plus grand village,\n");
		printf("   le nombre de ville dans celui-ci représente le nombre de points obtenue.\n");
	}
	if(variante==4){
		printf("2/ Augmenter le nombre de Forets.\n");
		printf("   Pour chaque forêt, la première case vaut 1, la seconde 2, la troisième 3, etc... ");
		printf("   jusqu'à 5.\n");
	}
	else{
		printf("2/ Augmenter le nombre de Forets. Le nombre d’abres compte double dans le score.\n");
	}
	if(variante==0){
		printf("3/ Augmenter le nombre de lacs. Le nombre de lacs compte double dans le score.\n");
	}
	else{
		printf("3/ Augmenter le nombre de lacs.Le nombre de lacs compte triple dans le score.\n");
	}
	if(variante==2){
		printf("4/ Compter les Ressources. On alloue deux Ressource par Usine tant qu’il reste \n");
		printf("   des cases Ressource et des cases Usine. Chaque Ressource allouée à une Usine rapporte 4 points. \n");
		printf("   Une Usine ne peut traiter que deux Ressources et une Ressource ne peut être allouée qu’à une Usine.\n");
		printf("   Une Usine peut traiter une ressource d’une case qui ne lui est pas contigue\n");
	}
	else{
		printf("4/ Compter les Ressources. On alloue une Ressource par Usine tant qu’il reste \n");
		printf("   des cases Ressource et des cases Usine. Chaque Ressource alloué à une Usine rapporte 4 points. \n");
		printf("   Une Usine ne peut traiter qu’une Ressource et une Ressource ne peut être allouée qu’à une Usine.\n");
		printf("   Une Usine peut traiter une ressource d’une case qui ne lui est pas contigue.\n");
	}
	if(variante==1){
		printf("5/ Augmenter le nombre de quadio de plaines. Une plaine de 4 cases vaut 4 points.\n");
	}
}
