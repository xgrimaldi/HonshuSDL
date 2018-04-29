#include "SolvNaif.h"
#include "struct.h"
#include "game.h"
#include "plateau.h"
#include "score.h"
#include "tuile.h"

void copiePlateau(int** array, int** copieArray, int size){
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			copieArray[i][j]=array[i][j];
		}
	}
}

void copieGame2(Game* partie,Game* copie){
	int size=partie->taille;

	copie->taille=size;

	copie->nbTuiles=partie->nbTuiles;
	copie->nbTuilesPose=partie->nbTuilesPose;

	copiePlateau(partie->plateau,copie->plateau,size);
	copiePlateau(partie->plateauIDmax,copie->plateauIDmax,size);

	int i;
	for(i=0;i<copie->nbTuiles;i++){
		copie->tuiles[i]=partie->tuiles[i];
	}
}
/*
Game copieGame(Game partie){

	Game copie;


	int size=partie.taille;

	copie.taille=size;

	copie.nbTuiles=partie.nbTuiles;
	copie.nbTuilesPose=partie.nbTuilesPose;

	copie.plateau = alloc_int_array(size, size);
	copie.plateauIDmax = alloc_int_array(size, size);
	copie.previous = alloc_int_array(size,size);
	copie.previousIDmax = alloc_int_array(size,size);

	copiePlateau(partie.plateau,copie.plateau,size);
	copiePlateau(partie.plateauIDmax,copie.plateauIDmax,size);
	copie.previous=partie.previous;
	copie.previousIDmax=partie.previousIDmax;

	copie.previousNBCasesRec = (int*)malloc(6*sizeof(int)); 

	copie.previousNBCasesRec = partie.previousNBCasesRec;

	copie.tuiles = (Tuile*)malloc(MAXTUILES*sizeof(Tuile));

	int i;
	for(i=0;i<copie.nbTuiles;i++){
		copie.tuiles[i]=partie.tuiles[i];
	}


	return copie;
}
*/


int* IdsTuilesDisponibles(Tuile gameTuiles[MAXTUILES],int nbTuiles){
	int* resultat = (int*)malloc(MAXTUILES*sizeof(int));
	int i;
	int j=0;
	for(i=0;i<nbTuiles;i++){
		if(gameTuiles[i].pos.x == -1 && gameTuiles[i].pos.y == -1){
			resultat[j]=gameTuiles[i].id;
			j++;
		}
	}
	resultat[j] = -1;
	return resultat;
}


int maxScore(Game* game,Game* resu,int** ville){	

	if (game->taille==-1){
		return 1;	
	} 

	if(getScore(game,ville,1)>getScore(resu,ville,1)){
		copieGame2(game,resu);
		return 1;	
	}
	return 0;
}


int solveurNaif(Game partie, Game* resultat, int i, int** ville){


/*******************************************
* Cas où le solveur ne doit rien anticiper
*******************************************/

	if (i==-1){
		copieGame2(&partie,resultat);
		return 1;
	}


/*******************************************
* Cas où il n'y a plus de tuiles à placer
*******************************************/


	int* Liste_id=IdsTuilesDisponibles(partie.tuiles,partie.nbTuiles);

	int id_Tuile=Liste_id[0];

	if (id_Tuile==-1){
		free(Liste_id);
		copieGame2(&partie,resultat);
		return 1;
	}


/*******************************************
*               Héréditer
*******************************************/

	int size = partie.taille;

	
	Game game;
	
	game.plateau = alloc_int_array(size, size);
	game.plateauIDmax = alloc_int_array(size, size);


	game.previousNBCasesRec = (int*)malloc(6*sizeof(int)); 

	game.tuiles = (Tuile*)malloc(MAXTUILES*sizeof(Tuile));

	copieGame2(&partie,&game);


	int ok=0;
	

	int x,y,orientation,p;

	p=0;
	


	Game copiePartie;

	copiePartie.plateau = alloc_int_array(size, size);
	copiePartie.plateauIDmax = alloc_int_array(size, size);

	copiePartie.previousNBCasesRec = (int*)malloc(6*sizeof(int)); 

	copiePartie.tuiles = (Tuile*)malloc(MAXTUILES*sizeof(Tuile));

	copieGame2(&partie,&copiePartie);


	while(id_Tuile != -1){

		for (x=0;x<size;x++){
			for(y=0;y<size;y++){
				for(orientation=1;orientation<5;orientation++){
					if (orientation==1) copiePartie.tuiles[id_Tuile].orientation = 'N';
					else if(orientation==2) copiePartie.tuiles[id_Tuile].orientation = 'E';
					else if(orientation==3) copiePartie.tuiles[id_Tuile].orientation = 'S';
					else copiePartie.tuiles[id_Tuile].orientation = 'W';
					
			
					if(!placeTuile(&copiePartie,id_Tuile,x,y,1)){
						ok=1;
						solveurNaif(copiePartie,&game,i-1,ville); 

						maxScore(&game,resultat,ville);

						copieGame2(&partie,&copiePartie);
					}

				}
			}
			
		}
		p++;
		id_Tuile=Liste_id[p];
	}

	free(Liste_id);

	freeGame(&copiePartie,1);

	freeGame(&game,1);


	if (ok==0) {
		resultat->taille=-1;
	}

	return 1;
}

int iterSolvNaif(Game partie, Game* resultat, int n, int** ville){
	int i = 0;
	while (i+n<partie.nbTuiles){
		solveurNaif(partie,resultat,n,ville);
		copieGame2(resultat,&partie);
		i=i+n+1;
//		printf("plop %d\n", i);
//		printPlateau(resultat->plateau,10);
	}


	if (i != partie.nbTuiles) solveurNaif(partie,resultat,partie.nbTuiles-i-1,ville);

	return 1;
}










