#include "struct.h"
#include "tuile.h"
#include "game.h"
#include "plateau.h"


// ######################################
//	PARTIE AFFICHAGE
// ######################################

void printTuiles(Tuile gameTuiles[MAXTUILES],int nbTuiles){
	printf("\n\t\t Tuiles disponibles\n");
	int step=5;
	for(int i=0;i<nbTuiles;i=i+step){
		for(int j=0;j<step;j++){
			if(i+j<nbTuiles && gameTuiles[i+j].pos.x == -1 && gameTuiles[i+j].pos.y == -1){
				if(gameTuiles[i+j].orientation == 'E' || gameTuiles[i+j].orientation == 'W'){
					printf(" %s   ID:%d%s    \t",Color_Bold_White,gameTuiles[i+j].id,Color_end);
				}
				else{
					printf(" %s ID:%d%s    \t",Color_Bold_White,gameTuiles[i+j].id,Color_end);
				}
			}
		}
		printf("\n");
		for(int j=0;j<step;j++){
			if(i+j<nbTuiles && gameTuiles[i+j].pos.x == -1 && gameTuiles[i+j].pos.y == -1){
				switch(gameTuiles[i+j].orientation){
					case 'N':{
						printf("| ");
						printIntToCharColor(gameTuiles[i+j].X_1);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_2);
						printf(" |\t");
						break;
					}
					case 'E':{
						printf("| ");
						printIntToCharColor(gameTuiles[i+j].X_5);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_3);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_1);
						printf(" |\t");
						break;
					}
					case 'W':{
						printf("| ");
						printIntToCharColor(gameTuiles[i+j].X_2);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_4);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_6);
						printf(" |\t");
						break;
					}
					case 'S':{
						printf("| ");
						printIntToCharColor(gameTuiles[i+j].X_6);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_5);
						printf(" |\t");
						break;
					}
				}
			}
		}
		printf("\n");
		for(int j=0;j<step;j++){
			if(i+j<nbTuiles && gameTuiles[i+j].pos.x == -1 && gameTuiles[i+j].pos.y == -1){
				switch (gameTuiles[i+j].orientation){
					case 'N':{
						printf("| ");
						printIntToCharColor(gameTuiles[i+j].X_3);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_4);
						printf(" |\t");
						break;
					}
					case 'S':{
						printf("| ");
						printIntToCharColor(gameTuiles[i+j].X_4);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_3);
						printf(" |\t");
						break;
					}
					case 'E':{
						printf("| ");
						printIntToCharColor(gameTuiles[i+j].X_6);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_4);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_2);
						printf(" |\t");
						break;
					}
					case 'W':{
						printf("| ");
						printIntToCharColor(gameTuiles[i+j].X_1);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_3);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_5);
						printf(" |\t");
						break;
					}

				}
			}
		}
		printf("\n");
		for(int j=0;j<step;j++){
			if(i+j<nbTuiles && gameTuiles[i+j].pos.x == -1 && gameTuiles[i+j].pos.y == -1){
				switch(gameTuiles[i+j].orientation){
					case 'N':{
						printf("| ");
						printIntToCharColor(gameTuiles[i+j].X_5);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_6);
						printf(" |\t");
						break;
					}
					case 'S':{
						printf("| ");
						printIntToCharColor(gameTuiles[i+j].X_2);
						printf(" | ");
						printIntToCharColor(gameTuiles[i+j].X_1);
						printf(" |\t");	
						break;				
					}
					case 'W':{
						printf("             \t");
						break;
					}
					case 'E':{
						printf("             \t");
						break;
					}
				}
			}
		}
		printf("\n\n");
	}
}

void printIntToCharColor(int car){
	if (car=='L')
		printf("%s%c%s",Color_Bold_Blue,car,Color_end);
	else if (car=='P')
		printf("%s%c%s",Color_Bold_Yellow,car,Color_end);
	else if (car=='F')
		printf("%s%c%s",Color_Bold_Green,car,Color_end);
	else if (car=='V')
		printf("%s%c%s",Color_Bold_Magenta,car,Color_end);
	else if (car=='U')
		printf("%s%c%s",Color_Bold_Gray,car,Color_end);
	else if (car=='R')
		printf("%s%c%s",Color_Bold_Red,car,Color_end);
	else
		printf("%s%c%s",Color_Bold_White,car,Color_end);
}


// ######################################
//	Gestion des fichiers
// ######################################

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
			gameTuiles[id_tuile].orientation='N';
			gameTuiles[id_tuile].pos.x=-1;
			gameTuiles[id_tuile].pos.y=-1;

		}
		fclose(fichier);
		return nbTuiles;
	}
	else{
	   	// On affiche un message d'erreur si on veut
	   	printf("Fichier vide ou inconnu\n");
	   	return 0;
	}
}

// ######################################
//	GESTION DES TUILES
// ######################################

Tuile* randomTuile(int nb){
	int i;
	char cases[6] = "LPFVUR";
	Tuile* tabTuile = malloc(nb*sizeof(Tuile));
	for(i = 0; i < nb; i++){
		tabTuile[i].id = i;
        tabTuile[i].orientation='N';
        tabTuile[i].pos.x=-1;
        tabTuile[i].pos.y=-1;
		tabTuile[i].nbCasesRecouvertes=0;
		tabTuile[i].X_1 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_2 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_3 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_4 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_5 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_6 = cases[randomMinMax(0, 5)];
	}
	return tabTuile;
}

Tuile rotateTuile(Tuile t,char direction){
	if (direction == 'N' || direction == 'S' || direction == 'W' || direction == 'E'){
		t.orientation=direction;
	}
	return t;
}

Tuile copyTuile(Tuile tuileACopier){
	Tuile new;
	new.id=tuileACopier.id;
	new.X_1=tuileACopier.X_1;
	new.X_2=tuileACopier.X_2;
	new.X_3=tuileACopier.X_3;
	new.X_4=tuileACopier.X_4;
	new.X_5=tuileACopier.X_5;
	new.X_6=tuileACopier.X_6;
	new.orientation=tuileACopier.orientation;
	new.pos.x=tuileACopier.pos.x;
	new.pos.y=tuileACopier.pos.y;

	return new;
}

// ######################################
//	GESTION DU PLATEAU
// ######################################

int placeTuile(Game* game, int id, int x, int y){ //Les coordonées de la position sont celles de la case la plus en haut à gauche en tenant compte de l'orientation
	if(!canPlaceTuile(*game, id, x, y)){
		printf("Impossible de placer cette tuile ici (vous recouvrez un lac ou aucune tuile !)\n");
		return EXIT_FAILURE;
	}
	/*Déclaration de variables*/
	Tuile tuile = game -> tuiles[id]; 
	int TRT=testRecouvrementTotal(game,id,x,y);
	
	if (TRT!=-1){
	  printf("Vous recouvrez totalement la tuile d'id %d.\n",TRT);
	  return EXIT_FAILURE;
	};

	savePlateau(game);
	game->tuiles[id].nbCasesRecouvertes=0;

	/*Gestion du plateau de recouvrement */
	if (game->tuiles[id].orientation=='N' || game->tuiles[id].orientation=='S'){
	  game->plateauIDmax[x][y]=id;
	  game->plateauIDmax[x][y+1]=id;
	  game->plateauIDmax[x+1][y]=id;
	  game->plateauIDmax[x+1][y+1]=id;
	  game->plateauIDmax[x+2][y]=id;
	  game->plateauIDmax[x+2][y+1]=id;
	}
	else{
	  game->plateauIDmax[x][y]=id;
	  game->plateauIDmax[x][y+1]=id;
	  game->plateauIDmax[x][y+2]=id;
	  game->plateauIDmax[x+1][y]=id;
	  game->plateauIDmax[x+1][y+1]=id;
	  game->plateauIDmax[x+1][y+2]=id;
	}
	
	/*Gestion du plateau*/
	switch(game -> tuiles[id].orientation){

		case 'N':{ 
			game -> plateau[x][y] = tuile.X_1;
			game -> plateau[x][y+1] = tuile.X_2;
			game -> plateau[x+1][y] = tuile.X_3;
			game -> plateau[x+1][y+1] = tuile.X_4;
			game -> plateau[x+2][y] = tuile.X_5;
			game -> plateau[x+2][y+1] = tuile.X_6;
			break;
		}

		case 'E':{
			game -> plateau[x][y] = tuile.X_5;
			game -> plateau[x][y+1] = tuile.X_3;
			game -> plateau[x][y+2] = tuile.X_1;
			game -> plateau[x+1][y] = tuile.X_6;
			game -> plateau[x+1][y+1] = tuile.X_4;
			game -> plateau[x+1][y+2] = tuile.X_2;
			break;
		}

		case 'S':{
			game -> plateau[x][y] = tuile.X_6;
			game -> plateau[x][y+1] = tuile.X_5;
			game -> plateau[x+1][y] = tuile.X_4;
			game -> plateau[x+1][y+1] = tuile.X_3;
			game -> plateau[x+2][y] = tuile.X_2;
			game -> plateau[x+2][y+1] = tuile.X_1;
			break;
		}

		case 'W':{
			game -> plateau[x][y] = tuile.X_2;
			game -> plateau[x][y+1] = tuile.X_4;
			game -> plateau[x][y+2] = tuile.X_6;
			game -> plateau[x+1][y] = tuile.X_1;
			game -> plateau[x+1][y+1] = tuile.X_3;
			game -> plateau[x+1][y+2] = tuile.X_5;
			break;
		}

		default:{
			printf("Erreur d'orientation de la tuile (Utiliser 'N', 'E', 'S' ou 'W' uniquement)\n");
			return EXIT_FAILURE;
		}
	}

	// Inversion
	game->tuiles[id].pos.x=y;
	game->tuiles[id].pos.y=x;

	return EXIT_SUCCESS;
}

int canPlaceTuile(Game game, int id, int x, int y){ //Reste a traiter le cas de recouvrement complet d'une autre tuile (interdit)
	int recouvreUneTuile = 0;
	char orientation = game.tuiles[id].orientation;
	if(orientation =='N' || orientation == 'S'){ //L'ordre des cases n'a pas d'importance pour des orientations de même axe
		
		if (game.plateau[x][y] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x][y+1] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+1][y] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+1][y+1] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+2][y] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+2][y+1] != 0) recouvreUneTuile = 1;

		if (!(inPlateau(x, y,game.taille)) || game.plateau[x][y] == 'L') return 0;
		if (!(inPlateau(x, y+1,game.taille)) || game.plateau[x][y+1] == 'L') return 0;
		if (!(inPlateau(x+1, y,game.taille)) || game.plateau[x+1][y] == 'L') return 0;
		if (!(inPlateau(x+1, y+1,game.taille)) || game.plateau[x+1][y+1] == 'L') return 0;
		if (!(inPlateau(x+2, y,game.taille)) || game.plateau[x+2][y] == 'L') return 0;
		if (!(inPlateau(x+2, y+1,game.taille)) || game.plateau[x+2][y+1] == 'L') return 0;
	}

	else{
		if (game.plateau[x][y] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x][y+1] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x][y+2] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+1][y] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+1][y+1] != 0) recouvreUneTuile = 1;
		else if(game.plateau[x+1][y+2] != 0) recouvreUneTuile = 1;

		if (!(inPlateau(x, y,game.taille)) || game.plateau[x][y] == 'L') return 0;
		if (!(inPlateau(x, y+1,game.taille)) || game.plateau[x][y+1] == 'L') return 0;
		if (!(inPlateau(x, y+2,game.taille)) || game.plateau[x][y+2] == 'L') return 0;
		if (!(inPlateau(x+1, y,game.taille)) || game.plateau[x+1][y] == 'L') return 0;
		if (!(inPlateau(x+1, y+1,game.taille)) || game.plateau[x+1][y+1] == 'L') return 0;
		if (!(inPlateau(x+1, y+2,game.taille)) || game.plateau[x+1][y+2] == 'L') return 0;
	}

	if(!recouvreUneTuile) printf("Aucune tuile n'est recouverte !\n");

	return recouvreUneTuile;
}

Tuile newTuile(int id, char x1, char x2, char x3, char x4, char x5, char x6){
	Tuile tuile;
	tuile.id = id;
	tuile.X_1=x1;
	tuile.X_2=x2;
	tuile.X_3=x3;
	tuile.X_4=x4;
	tuile.X_5=x5;
	tuile.X_6=x6;
	tuile.orientation='N';
	tuile.pos.x=-1;
	tuile.pos.y=-1;
	return tuile;
}