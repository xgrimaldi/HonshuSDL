#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "game.h"

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

void printTuiles(Tuile gameTuiles[MAXTUILES],int nbTuiles){
	printf("\n\t\t Tuiles paramètrées\n");
	for(int i=0;i<nbTuiles;i++){
		printf("\n %s ID:%d%s \n",Color_Bold_White,gameTuiles[i].id,Color_end);
		printf("| ");
		printIntToCharColor(gameTuiles[i].X_1);
		printf(" | ");
		printIntToCharColor(gameTuiles[i].X_2);
		printf(" |\n");
		printf("| ");
		printIntToCharColor(gameTuiles[i].X_3);
		printf(" | ");
		printIntToCharColor(gameTuiles[i].X_4);
		printf(" |\n");
		printf("| ");
		printIntToCharColor(gameTuiles[i].X_5);
		printf(" | ");
		printIntToCharColor(gameTuiles[i].X_6);
		printf(" |\n");
	}
}

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

void printIntToCharColor(int car){
	if (car=='L')
		printf("%s%c%s",Color_Bold_Blue,car,Color_end);
	else if (car=='P')
		printf("%s%c%s",Color_Bold_Green,car,Color_end);
	else if (car=='F')
		printf("%s%c%s",Color_Bold_Green,car,Color_end);
	else if (car=='V')
		printf("%s%c%s",Color_Bold_Magenta,car,Color_end);
	else if (car=='U')
		printf("%s%c%s",Color_Bold_Yellow,car,Color_end);
	else if (car=='R')
		printf("%s%c%s",Color_Bold_Red,car,Color_end);
	else
		printf("%s%c%s",Color_Bold_White,car,Color_end);
}
// ######################################
//	PARTIE INITIALISATION
// ######################################

void initPlateau(int** gamePlateau,int taille){
	for (int i=0;i<taille;i++){
		for(int j=0;j<taille;j++){
			gamePlateau[i][j]=0;
		}
	}
}

void initPlacementTuileRandom(Game* partie){
	int choix = randomMinMax(0,partie->nbTuiles-1);
	int pos_ligne = (partie->taille/2);
	int pos_col = (partie->taille/2);
	char placement[6]= {partie->tuiles[choix].X_1,partie->tuiles[choix].X_2,partie->tuiles[choix].X_3,partie->tuiles[choix].X_4,partie->tuiles[choix].X_5,partie->tuiles[choix].X_6};
	
	partie->tuiles[choix].orientation='N';

	int ind=0;
	for (int i=pos_ligne; i<pos_ligne+3 ;i++){
		for (int j=pos_col; j<pos_col+2 ;j++){
			partie->plateau[i][j] = placement[ind];
			ind++;
		}
	}
}

void initPlacementTuile(Game* partie,int numTuile){
	int pos_ligne = (partie->taille/2);
	int pos_col = (partie->taille/2);
	char placement[6]= {partie->tuiles[numTuile].X_1,partie->tuiles[numTuile].X_2,partie->tuiles[numTuile].X_3,partie->tuiles[numTuile].X_4,partie->tuiles[numTuile].X_5,partie->tuiles[numTuile].X_6};

	partie->tuiles[numTuile].orientation='N';

	int ind=0;
	for (int i=pos_ligne; i<pos_ligne+3 ;i++){
		for (int j=pos_col; j<pos_col+2 ;j++){
			partie->plateau[i][j] = placement[ind];
			ind++;
		}
	}
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
			gameTuiles[id_tuile].orientation='V';
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

int LoadGame(char* filepath,Game* game){
	//******************************
	// Récupération du fichier
	//******************************

    Tuile* allTuiles = malloc(MAXTUILES * sizeof(Tuile));
    // Récupération des tuiles de bases
    LoadTuiles("Tuiles",allTuiles);

  	FILE* fichier = NULL;
	fichier = fopen(filepath, "r+");

	//******************************
	// Traitement
	//******************************
	if (fichier != NULL){
		//******************************
		// Initialisation des variables
		//******************************
	    char word[50];
	    int nbTuiles=0;
     	
     	// Récupération de la taille du plateau
     	fscanf(fichier, "%s", word);
		game->taille=atoi(word);
		game->plateau=alloc_int_array(atoi(word),atoi(word));

		// Récupération du nombre de tuiles
     	fscanf(fichier, "%s", word);
		nbTuiles=atoi(word);
		game->nbTuiles=nbTuiles;

		// Copie des tuiles
 		for(int nbImport=0;nbImport<nbTuiles;nbImport++){
 			fscanf(fichier,"%s",word);
	 		game->tuiles[nbImport]=copyTuile(allTuiles[atoi(word)]);
	 		game->tuiles[nbImport].id=nbImport;
   		}

   		//Récupération de la tuile à placer
   		fscanf(fichier,"%s",word);
   		initPlacementTuile(game,atoi(word));

		fclose(fichier);
		free(allTuiles);
		return nbTuiles;
	}
	else{
		free(allTuiles);
       	// On affiche un message d'erreur si on veut
       	printf("Fichier vide ou inconnu\n");
       	return EXIT_FAILURE;
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
	        tabTuile[i].orientation='V';
		tabTuile[i].id = i;
		tabTuile[i].X_1 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_2 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_3 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_4 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_5 = cases[randomMinMax(0, 5)];
		tabTuile[i].X_6 = cases[randomMinMax(0, 5)];
	}
	return tabTuile;
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

	return new;
}

// ######################################
//	GESTION DU PLATEAU
// ######################################

int placeTuile(Game* game, int id, int x, int y, int** previous){ //Les coordonées de la position sont celles de la case la plus en haut à gauche en tenant compte de l'orientation
	Tuile tuile = game -> tuiles[id];

	if(!canPlaceTuile(*game, id, x, y)){
		printf("Impossible de placer cette tuile ici (vous recouvrez un lac ou aucune tuile !)\n");
		return EXIT_FAILURE;
	}
	previous=saveGame(game,previous);

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

	return EXIT_SUCCESS;
}

int inPlateau(int x, int y,int taille){
	if( !((0 <= x) && (x < taille)) || !((0 <= y) && (y < taille)) ){
		printf("La case (%d, %d) ne fait pas partie du plateau de jeu !\n", x, y);
		return 0;
	}
	else return 1;
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

char printCase(Game game, int x, int y){
	return (char)game.plateau[x][y];
}

// ######################################
//	GESTION DE LA PARTIE
// ######################################

int startGame(int typeGame){
	// Nettoyage de l'écran
	clearScreen();

	//*********************************
	// Déclaration des variables
	//************************ws*********
	Game* game=malloc(sizeof(Game));	
	Tuile* gameTuiles = malloc(MAXTUILES * sizeof(Tuile));
	int** gamePlateau;	
	int** previous;

	int nb_tuiles=0, choix=0 ,id_Tuile = -1,id_Tuile_prec = -1;
	int x = -1;
	char y = '^', orientation = 'V';
	int accepte = 0 ,dep = 0;

	//**********************************
	// Chargement des paramètres de partie
	//**********************************
	switch(typeGame){
		case 1:{	
			while (nb_tuiles==0){
				LOG_BOLDRED("\t\t\t\tParamètrage des tuiles \n");
				printf("Combien de tuiles voulez vous générer ? ");
				scanf("%d", &nb_tuiles);
				if(nb_tuiles <= 0){
					printf("Veuillez saisir un nombre entre 1 et %d\n", MAXTUILES);
					printf("\n");
					nb_tuiles = 0;
				}
				else{
					clearScreen();
					gameTuiles = randomTuile(nb_tuiles);
				}
			}

			int size=0;
			while (size <= 0 || size>=30){
				LOG_BOLDRED("\t\t\t\tParamètrage du plateau \n");
				printf("Quel doit-être la taille du plateau ? ");
				scanf("%d", &size);
				if(size <= 0 || size>=30){
					printf("Veuillez saisir un nombre entre 1 et 30 \n");
				}
				else{
					// Création du plateau de jeu de taille n*n
					gamePlateau = alloc_int_array(size, size);
					initPlateau(gamePlateau,size);

					// Attribution du jeu 
					game->plateau = gamePlateau;
					game->tuiles = gameTuiles;
					game->nbTuiles = nb_tuiles;
					game->nbTuilesPose=1;
					game->taille=size;

					//Placement de la premiere tuile
					initPlacementTuileRandom(game);
				}
			}
			break;
		}
		case 2:{
			game->tuiles=gameTuiles;
			char filepath[1024]={};
			printf("Quel est le chemin du fichier 'Partie' ? ...\n");
			scanf("%s",filepath);
			if( EXIT_FAILURE==LoadGame(filepath,game)){
				return EXIT_FAILURE;
			}
			break;
		}
	}
	previous = alloc_int_array(game->taille,game->taille);
	initPlateau(previous,game->taille);

	//**********************************
	// Lancement du jeu 
	//**********************************
	int stop = 0;
	choix=0;
	while(stop == 0){

		printf("\nQue voulez-vous faire ?\n");
	 	printf("1 - Voir les tuiles paramètrés\n");
	 	printf("2 - Voir le plateau de jeu\n");
	 	printf("3 - Poser une tuile\n");
	 	printf("4 - Voulez-vous annuler votre choix\n");
		if (game->nbTuilesPose==game->nbTuiles){
		  printf("5 - Terminer la partie\n");
		}
		printf("0 - Quitter la partie\n");
		
		scanf("%d",&choix);
		switch(choix){
			case 1:{
				// Affichage des tuiles disponibles 
				if(game->nbTuiles > 0)
					printTuiles(game->tuiles,game->nbTuiles);
				else
					printf("Aucune tuile: Vérifier le paramètrage ! \n");
				break;
			}
			case 2:{
				clearScreen();
				// Affichage du plateau
				printPlateau(game->plateau,game->taille);
				break;
			}
			case 3:{ 
			  	printf("Quelle tuile voulez vous placer ? : ");
				scanf("%d", &id_Tuile);
		       	if(id_Tuile < 0 || id_Tuile >= game->nbTuiles) 
		       		printf("ID incorrect ! Saisir un ID entre 0 et %d\n", game->nbTuiles-1);//Si Id incorrect alors retour aux choix
				else if (game->tuiles[id_Tuile].orientation != 'V') 
					printf("ID indisponible ! La tuile %d est déjà placée.\n",id_Tuile);//si la tuile est déjà placé, on retourne aux choix					
				//sinon, on peut continuer
				else {				
        			while(accepte == 0 ){ //ordonée
						printf("À quelle ordonée voulez vous placer la tuile %d : ", id_Tuile);
						scanf("%d", &x);
						if(x < 0 || x >= game->taille) 
							printf("Ordonée incorrect ! Saisir un nombre entre 0 et %d\n", game->taille);
						else 
							accepte = 1;
				  	}

				  	accepte = 0;
				  	while(accepte == 0){ //abcisse
				    	printf("À quelle abcisse voulez vous placer la tuile %d : ", id_Tuile);
				    	scanf(" %c", &y);
				    	if(!(y >= 97 && y < 97+game->taille) && !(y >= 65 && y < 65+game->taille)) printf("Abcisse incorrect ! Saisir une lettre entre A et %c\n", (char)(65+game->taille-1)); // On est contraint de supposer n <= 26
				    	else {
				      		accepte = 1;
				      		if(y >= 97 && y < 97+game->taille){ 
				      			//ici y est une minuscule
								y -= 97;
				      		}
				      		else
				      			y -= 65;
				    	}
				  	}

				  	accepte = 0;
				  	while(accepte == 0){ //orientation
				    	printf("Quelle orientation pour la tuile %d : ", id_Tuile);
				    	scanf(" %c", &orientation);
				    	if( orientation != 'N' && orientation != 'n' && orientation != 'E' && orientation != 'e' && orientation != 'S' && orientation != 's' && orientation != 'W' && orientation != 'w'){
				      		printf("Orientation inconnue (saisir 'N', 'E', 'S' ou 'W')\n"); // On est contraint de supposer n <= 26
				    	}
				    	else {
				      		if(orientation > 90){ //Si orientation est écrit en minuscule{
								orientation -= 32; //On la convertit en minuscule
				      		}
				      		accepte = 1;
				      		game->tuiles[id_Tuile].orientation = orientation;
				    	}
				  	}
				  
				  	if(!placeTuile(game, id_Tuile, x, (int) y, previous)){
				    	id_Tuile_prec=id_Tuile;
				    	printf("Placement réalisé\n");
				    	game->nbTuilesPose++;
				    	dep=1;
				  	}
				  
				  	else{
				    	printf("Placement refusé\n"	);
				    	game->tuiles[id_Tuile].orientation='V';
				  }
				  
				}
				accepte = 0;
				break;
			}

			case 4:{
				if (matchEmpty(previous, game->taille)){
					if (dep==1) {
					  getPrevious(game, previous,id_Tuile_prec);
						printf("Vous avez récupérer le tableau précedent\n");
						game->nbTuilesPose--;
						dep=0;
					}
					else printf("Le dernier placement a déja été annulé, veuillez effectuer une nouvelle pose de tuiles avant d'annuler\n");
				}
				else
					printf("le tableau représente la siuation initiale du jeu , vous ne pouvez pas annuler");
				
				break;
			}


			 case 5:{
			  
			  if (game->nbTuilesPose==game->nbTuiles){
			    
			    clearScreen();
			    printf("Vous avez marqué 42 points !");
			  
			    //Comptage des points à faire
			    stop=1;
			  }
			  break;
		        }
			   
			case 0:{
				for(int i=0;i<game->taille;i++){
					free(game->plateau[i]);
					free(previous[i]);
				}
				free(previous);
				free(game->plateau);
				free(game->tuiles);
				free(game);
				stop = 1;
				return EXIT_SUCCESS;
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}

int** saveGame(Game* game, int** previous){
	int i,j;
	for (i=0; i<(game->taille); i++)
		for (j=0; j<(game->taille); j++)
			previous[i][j]=game->plateau[i][j];
	return previous;
}

int getPrevious (Game* game ,int** previous,int id_tuile_removed){
	int i,j;
	game->tuiles[id_tuile_removed].orientation='V';
	for (i=0; i<(game->taille); i++){
		for (j=0; j<(game->taille); j++){
			game->plateau[i][j]=previous[i][j];
		}
	}
	return 1;
}

int matchEmpty (int** previous, int taille){
	int i,j;
	for (i=0; i<taille; i++){
		for (j=0; j<taille; j++){
			if (previous [i][j]!=0)
				return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

// ######################################
//	DIVERS FONCTIONS
// ######################################

int randomMinMax(int a,int b){
	int r = (rand() % (b - a + 1)) + a;
	return r;
}

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
