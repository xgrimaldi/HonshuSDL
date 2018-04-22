#include "struct.h"
#include "game.h"
#include "tuile.h"

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

char printCase(Game game, int x, int y){
	return (char)game.plateau[x][y];
}

// ######################################
//	PARTIE INITIALISATION
// ######################################

void initPlateau(int** gamePlateau,int taille,int val){
	for (int i=0;i<taille;i++){
		for(int j=0;j<taille;j++){
			gamePlateau[i][j]=val;
		}
	}
}

void initPlacementTuileRandom(Game* partie){
  	int choix = randomMinMax(0,partie->nbTuiles-1);
	int pos_ligne=0,pos_col=0;
	int ind=0;
	if (partie->taille%2==0){
		pos_ligne = (partie->taille/2)-1;
		pos_col = (partie->taille/2)-1;
	}
	else{
		pos_ligne = ((partie->taille-1)/2)-1;
		pos_col = ((partie->taille-1)/2)-1;
	}
	char placement[6]= {partie->tuiles[choix].X_5,partie->tuiles[choix].X_3,partie->tuiles[choix].X_1,partie->tuiles[choix].X_6,partie->tuiles[choix].X_4,partie->tuiles[choix].X_2};

	partie->tuiles[choix].orientation='E';
	partie->tuiles[choix].nbCasesRecouvertes=0;
	partie->tuiles[choix].pos.x=pos_col;
	partie->tuiles[choix].pos.y=pos_ligne;	

	for (int i=pos_ligne; i<pos_ligne+2 ;i++){
		for (int j=pos_col; j<pos_col+3 ;j++){
			partie->plateau[i][j] = placement[ind];
			partie->plateauIDmax[i][j] = choix;
			ind++;
		}
	}     
}

void initPlacementTuile(Game* partie,int numTuile){
	int pos_ligne=0,pos_col=0;
	int ind=0;
	if (partie->taille%2==0){
		pos_ligne = (partie->taille/2)-1;
		pos_col = (partie->taille/2)-1;
	}
	else{
		pos_ligne = ((partie->taille-1)/2)-1;
		pos_col = ((partie->taille-1)/2)-1;
	}
	char placement[6]= {partie->tuiles[numTuile].X_5,partie->tuiles[numTuile].X_3,partie->tuiles[numTuile].X_1,partie->tuiles[numTuile].X_6,partie->tuiles[numTuile].X_4,partie->tuiles[numTuile].X_2};

	partie->tuiles[numTuile].orientation='E';
	partie->tuiles[numTuile].nbCasesRecouvertes=0;
	partie->tuiles[numTuile].pos.x=pos_col;
	partie->tuiles[numTuile].pos.y=pos_ligne;	

	for (int i=pos_ligne; i<pos_ligne+2 ;i++){
		for (int j=pos_col; j<pos_col+3 ;j++){
			partie->plateau[i][j] = placement[ind];
			partie->plateauIDmax[i][j] = numTuile;
			ind++;
		}
	}
}

// ######################################
//	GESTION DU PLATEAU
// ######################################

int inPlateau(int x, int y,int taille){
	if( !((0 <= x) && (x < taille)) || !((0 <= y) && (y < taille)) ){
		printf("La case (%d, %d) ne fait pas partie du plateau de jeu !\n", x, y);
		return 0;
	}
	else return 1;
}

void savePlateau(Game* game){
	int i,j;
	for (i=0; i<(game->taille); i++){
	  for (j=0; j<(game->taille); j++){
	    game->previous[i][j]=game->plateau[i][j];
	    game->previousIDmax[i][j]=game->plateauIDmax[i][j];
	  }
	}
}

int getPrevious (Game* game ,int id_tuile_removed,int x,char y){
	int i,j;
	game->tuiles[id_tuile_removed].pos.x=-1;
	game->tuiles[id_tuile_removed].pos.y=-1;
	for (i=0; i<(game->taille); i++){
		for (j=0; j<(game->taille); j++){
			game->plateau[i][j]=game->previous[i][j];
			game->plateauIDmax[i][j]=game->previousIDmax[i][j];
		}
	}

	retablishNBCasesRec(game,id_tuile_removed,x,y,game->previousNBCasesRec);
        
	return 1;
}

int matchEmpty (Game* game){
	int i,j;
	for (i=0; i<game->taille; i++){
		for (j=0; j<game->taille; j++){
			if (game->previous [i][j]!=0)
				return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

void copieNBCasesRec(Game* game, int id, int x, int y,int* copie){
  int ID;
  if (game->tuiles[id].orientation=='N' || game->tuiles[id].orientation == 'S'){
    ID=game->plateauIDmax[x][y];
    if (ID!=-1) copie[0]=game->tuiles[ID].nbCasesRecouvertes;
    ID=game->plateauIDmax[x][y+1];
    if (ID!=-1) copie[1]=game->tuiles[ID].nbCasesRecouvertes;
    ID=game->plateauIDmax[x+1][y];
    if (ID!=-1) copie[2]=game->tuiles[ID].nbCasesRecouvertes;
    ID=game->plateauIDmax[x+1][y+1];
    if (ID!=-1) copie[3]=game->tuiles[ID].nbCasesRecouvertes;
    ID=game->plateauIDmax[x+2][y];
    if (ID!=-1) copie[4]=game->tuiles[ID].nbCasesRecouvertes;
    ID=game->plateauIDmax[x+2][y+1];
    if (ID!=-1) copie[5]=game->tuiles[ID].nbCasesRecouvertes;
  }
  else{
    ID=game->plateauIDmax[x][y];
    if (ID!=-1) copie[0]=game->tuiles[ID].nbCasesRecouvertes;
    ID=game->plateauIDmax[x][y+1];
    if (ID!=-1) copie[1]=game->tuiles[ID].nbCasesRecouvertes;
    ID=game->plateauIDmax[x][y+2];
    if (ID!=-1) copie[2]=game->tuiles[ID].nbCasesRecouvertes;
    ID=game->plateauIDmax[x+1][y];
    if (ID!=-1) copie[3]=game->tuiles[ID].nbCasesRecouvertes;
    ID=game->plateauIDmax[x+1][y+1];
    if (ID!=-1) copie[4]=game->tuiles[ID].nbCasesRecouvertes;
    ID=game->plateauIDmax[x+1][y+2];
    if (ID!=-1) copie[5]=game->tuiles[ID].nbCasesRecouvertes;
  }
}


void retablishNBCasesRec(Game* game, int id, int x, int y,int* copie){
  int ID;
  if (game->tuiles[id].orientation=='N' || game->tuiles[id].orientation == 'S'){

    ID=game->plateauIDmax[x][y];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[0];
    ID=game->plateauIDmax[x][y+1];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[1];
    ID=game->plateauIDmax[x+1][y];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[2];
    ID=game->plateauIDmax[x+1][y+1];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[3];
    ID=game->plateauIDmax[x+2][y];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[4];
    ID=game->plateauIDmax[x+2][y+1];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[5];

  }
  
  else{
    ID=game->plateauIDmax[x][y];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[0];
    ID=game->plateauIDmax[x][y+1];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[1];
    ID=game->plateauIDmax[x][y+2];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[2];
    ID=game->plateauIDmax[x+1][y];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[3];
    ID=game->plateauIDmax[x+1][y+1];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[4];
    ID=game->plateauIDmax[x+1][y+2];
    if (ID!=-1) game->tuiles[ID].nbCasesRecouvertes=copie[5];
  }
}



int testRecouvrementTotal(Game* game, int id, int x, int y){
  int* copieNBCasesRecouverte=(int*)malloc(6*sizeof(int));
  copieNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
  int idmax;
  Tuile tuile = game -> tuiles[id];

  if (tuile.orientation=='N' || tuile.orientation == 'S'){
    idmax=game->plateauIDmax[x][y];
    if (idmax!=-1){
    	if (game->tuiles[idmax].nbCasesRecouvertes == 5){
        free(copieNBCasesRecouverte);
		    return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
    
    idmax=game->plateauIDmax[x][y+1];
    if (idmax!=-1){
    	if (game->tuiles[idmax].nbCasesRecouvertes==5){
			retablishNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
			  free(copieNBCasesRecouverte);
      return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
    
    
    idmax=game->plateauIDmax[x+1][y];
    if (idmax!=-1){
      if (game->tuiles[idmax].nbCasesRecouvertes==5){
        retablishNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
			  free(copieNBCasesRecouverte);
        return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
    
    idmax=game->plateauIDmax[x+1][y+1];
    if (idmax!=-1){
    	if (game->tuiles[idmax].nbCasesRecouvertes==5){
        retablishNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
        free(copieNBCasesRecouverte);
        return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
    
    idmax=game->plateauIDmax[x+2][y];
    if (idmax!=-1){
      if (game->tuiles[idmax].nbCasesRecouvertes==5){
        retablishNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
        free(copieNBCasesRecouverte);
        return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
    
    idmax=game->plateauIDmax[x+2][y+1];
    if (idmax!=-1){
      if (game->tuiles[idmax].nbCasesRecouvertes==5){
        retablishNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
        free(copieNBCasesRecouverte);
        return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
  }
	  

  else{
    idmax=game->plateauIDmax[x][y];
    if (idmax!=-1){
      if (game->tuiles[idmax].nbCasesRecouvertes == 5){
        free(copieNBCasesRecouverte);
        return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
    
    idmax=game->plateauIDmax[x][y+1];
    if (idmax!=-1){
    	if (game->tuiles[idmax].nbCasesRecouvertes==5){
        retablishNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
        free(copieNBCasesRecouverte);			
      return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
    
    idmax=game->plateauIDmax[x][y+2];
    if (idmax!=-1){
    	if (game->tuiles[idmax].nbCasesRecouvertes==5){
			retablishNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
		  free(copieNBCasesRecouverte);
      return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
    
    idmax=game->plateauIDmax[x+1][y];
    if (idmax!=-1){
    	if (game->tuiles[idmax].nbCasesRecouvertes==5){
			retablishNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
      free(copieNBCasesRecouverte);
			return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
    
    idmax=game->plateauIDmax[x+1][y+1];
    if (idmax!=-1){
    	if (game->tuiles[idmax].nbCasesRecouvertes==5){
			retablishNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
      free(copieNBCasesRecouverte);
			return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }
    
    idmax=game->plateauIDmax[x+1][y+2];
    if (idmax!=-1){
    	if (game->tuiles[idmax].nbCasesRecouvertes==5){
			retablishNBCasesRec(game,id,x,y,copieNBCasesRecouverte);
      free(copieNBCasesRecouverte);
			return idmax;
      }
      game->tuiles[idmax].nbCasesRecouvertes++;
    }    
  }

  game->previousNBCasesRec[0]=copieNBCasesRecouverte[0];
  game->previousNBCasesRec[1]=copieNBCasesRecouverte[1];
  game->previousNBCasesRec[2]=copieNBCasesRecouverte[2];
  game->previousNBCasesRec[3]=copieNBCasesRecouverte[3];
  game->previousNBCasesRec[4]=copieNBCasesRecouverte[4];
  game->previousNBCasesRec[5]=copieNBCasesRecouverte[5];
  free(copieNBCasesRecouverte);
  return -1;
}

int copyPlateauToPlateauBis(Game* game){
  for (int i=0;i<game->taille;i++){
    for(int j=0;j<game->taille;j++){
      game->plateauBis[i][j]=game->plateau[i][j];
    }
  }
  return EXIT_SUCCESS;
}