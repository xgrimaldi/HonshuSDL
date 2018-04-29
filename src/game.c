#include "game.h"
#include "tuile.h"
#include "plateau.h"
#include "score.h"
#include "SolvNaif.h"

int LoadGame(char* filepath,char* filepathTuile,Game* game){
	//******************************
	// Récupération du fichier
	//******************************
    Tuile* allTuiles = malloc(MAXTUILES * sizeof(Tuile));
    // Récupération des tuiles de bases
    if(LoadTuiles(filepathTuile,allTuiles) == 0){
    	free(allTuiles);
    	return EXIT_FAILURE;
    }

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
	    int size;
	    int nbTuiles=0;

     	// Récupération de la taille du plateau
     	fscanf(fichier, "%s", word);
		
		size = atoi(word);
		game->taille=size;

		game->plateau=alloc_int_array(size,size);
		game->plateauBis=alloc_int_array(size,size);
		game->plateauIDmax=alloc_int_array(size,size);
		game->previous = alloc_int_array(size,size);
		game->previousIDmax = alloc_int_array(size,size);
		game->previousNBCasesRec = (int*)malloc(6*sizeof(int)); 

		initPlateau(game->plateau,size,0);
		initPlateau(game->plateauBis,size,0);
		initPlateau(game->plateauIDmax,size,-1);
		initPlateau(game->previous,game->taille,0);
		initPlateau(game->previousIDmax,game->taille,-1);

		// Récupération du nombre de tuiles
     	fscanf(fichier, "%s", word);
		nbTuiles=atoi(word);
		game->nbTuiles=nbTuiles;
		game->nbTuilesPose=1;

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

void freeGame(Game* game,int solv){
	for(int i=0;i<game->taille;i++){
		free(game->plateau[i]);
		if (!solv) free(game->plateauBis[i]);
		free(game->plateauIDmax[i]);
		if (!solv) free(game->previous[i]);
		if (!solv) free(game->previousIDmax[i]);
	}
	if (!solv) free(game->previous);
	if (!solv) free(game->previousIDmax);
	
	free(game->previousNBCasesRec);
	free(game->plateau);
	
	if (!solv) free(game->plateauBis);
	
	free(game->plateauIDmax);
	free(game->tuiles);
	
	if (!solv) free(game);
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

	int nb_tuiles=0, choix=0,choixniv=0 ,choixsolv=0,id_Tuile = -1,id_Tuile_prec = -1;
	int x = -1, previousx = -1;
	char y = '^',previousy='^', orientation = 'N';
	int accepte = 0 ,dep = 0;
	char orientation_selected='N';
	int tuile_selected=-1;
	

	//**********************************
	// Chargement des paramètres de partie
	//**********************************
	switch(typeGame){

		case 1:{	
			// Initialisation des tuiles
			while (nb_tuiles==0){
				LOG_BOLDRED("\t\t\t\tParamètrage des tuiles \n");
				printf("Combien de tuiles voulez vous générer ? ");
				scanf("%d", &nb_tuiles);
				purger();
				if(nb_tuiles < 5){
					printf("Veuillez saisir un nombre entre 5 et %d\n", MAXTUILES);
					printf("\n");
					nb_tuiles = 0;
				}
				else{
					clearScreen();
					game->tuiles = malloc(MAXTUILES * sizeof(Tuile));
					game->tuiles = randomTuile(nb_tuiles);
					game->nbTuiles = nb_tuiles;
					game->nbTuilesPose=1;
				}
			}

			// Initialisation du plateau
			int size=0;
			while (size < 6 || size > 30){
				LOG_BOLDRED("\t\t\t\tParamètrage du plateau \n");
				printf("Quel doit-être la taille du plateau ? ");
				scanf("%d", &size);
				purger();
				if(size < 6 || size > 30){
					LOG_BOLDRED("Veuillez saisir un nombre entre 6 et 30 \n");
				}
				else{
					// Attribution du jeu 
					game->taille=size;

					// Création du plateau de jeu de taille n*n
					game->plateau = alloc_int_array(size, size);
					// Création du plateau des ID maximals de taille n*n					
					game->plateauIDmax = alloc_int_array(size, size);
					game->plateauBis = alloc_int_array(size,size);
					game->previous = alloc_int_array(size,size);
					game->previousIDmax = alloc_int_array(size,size);
					game->previousNBCasesRec = (int*)malloc(6*sizeof(int)); 
					// Initialisation des plateaux
					initPlateau(game->plateau,size,0);
					initPlateau(game->plateauIDmax,size,-1);
					initPlateau(game->plateauBis,size,0);
					initPlateau(game->previous,size,0);
					initPlateau(game->previousIDmax,size,-1);

					//Placement de la premiere tuile
					initPlacementTuileRandom(game);
				}
			}

			break;
		}
		case 2:{
			game->tuiles = malloc(MAXTUILES * sizeof(Tuile));
			char filepath[1024]={};
			char filepathTuile[1024]={};

			printf("Quel est le chemin du fichier 'Partie' ? ...\n");
			scanf("%s",filepath);
			purger();
			if (!fileExist(filepath)){
				printf("Fichier non existant");
				return EXIT_FAILURE;
			}


			printf("Quel est le chemin du fichier 'Tuiles' ? ...\n");
			scanf("%s",filepathTuile);
			purger();
			if (!fileExist(filepathTuile)){
				printf("Fichier non existant");
				return EXIT_FAILURE;
			}
			if( EXIT_FAILURE==LoadGame(filepath,filepathTuile,game)){
				return EXIT_FAILURE;
			}
			break;
		}
	}
	
	//**********************************
	// Lancement du jeu 
	//**********************************
	int stop = 0;
	int stopsolveur;

	int** ville = alloc_int_array(game->taille, game->taille);
	initPlateau(ville,game->taille,-1);

	game->nivSolv=1;

	//**********************************
	// Copie du game initial pour le solveur
	//**********************************
	Game gameInitial;
	
	gameInitial.plateau = alloc_int_array(game->taille,game->taille);
	gameInitial.plateauIDmax = alloc_int_array(game->taille,game->taille);

	gameInitial.previousNBCasesRec = (int*)malloc(6*sizeof(int)); 

	gameInitial.tuiles = (Tuile*)malloc(MAXTUILES*sizeof(Tuile));

	copieGame2(game,&gameInitial);

	while(stop == 0){
		printRules();
		choix=0;
		printf("\nQue voulez-vous faire ?\n");
	 	printf("1 - Voir les tuiles paramétrées\n");
	 	printf("2 - Voir le plateau de jeu\n");
	 	printf("3 - Poser une tuile\n");
	 	printf("4 - Annuler l'action précédente\n");
	 	printf("5 - Changer l'orientation d'une tuile\n");
	 	printf("6 - Envoyer le village associé à une case\n");
	 	printf("7 - Utiliser le solveur\n");
		if (game->nbTuilesPose == game->nbTuiles){
		  printf("8 - Terminer la partie\n");
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
				// Affichage des tuiles disponibles et non disponibles
				if(game->nbTuiles > 0){
					printTuilesNonDisponibles(game->tuiles,game->nbTuiles);
					printTuiles(game->tuiles,game->nbTuiles);
					printf("\nLE SCORE EST DE %d points\n.",getScore(game,ville,0));
				
				}else
					LOG_BOLDRED("Aucune tuile: Vérifier le paramètrage ! \n");
				break;
			}
			case 3:{ 
			  	printf("Quelle tuile voulez vous placer ? : ");
				scanf("%d", &id_Tuile);
				purger();
		       	if(id_Tuile < 0 || id_Tuile >= game->nbTuiles) 
		       		printf("ID incorrect ! Saisir un ID entre 0 et %d\n", game->nbTuiles-1);//Si Id incorrect alors retour aux choix
				else if (game->tuiles[id_Tuile].pos.x != -1 && game->tuiles[id_Tuile].pos.y != -1) 
					printf("ID indisponible ! La tuile %d est déjà placée.\n",id_Tuile);//si la tuile est déjà placé, on retourne aux choix					
				//sinon, on peut continuer
				else {	
					accepte=0;			
        			while(accepte == 0 ){ //ordonée
						printf("À quelle ordonée voulez vous placer la tuile %d : ", id_Tuile);
						scanf("%d", &x);
						purger();
						if(x < 0 || x >= game->taille) 
							printf("Ordonée incorrect ! Saisir un nombre entre 0 et %d\n", game->taille);
						else 
							accepte = 1;
				  	}

				  	accepte = 0;
				  	while(accepte == 0){ //abcisse
				    	printf("À quelle abcisse voulez vous placer la tuile %d : ", id_Tuile);
				    	scanf("%c", &y);
    					purger();
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
						purger();
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
				  
				  	if(!placeTuile(game, id_Tuile, x, (int) y,0)){
				    	id_Tuile_prec=id_Tuile;
				    	printf("Placement réalisé\n");
				    	game->nbTuilesPose++;
				    	dep=1;
						previousx=x;
						previousy=y;
			        	}
				  
				  	else{
				    	LOG_BOLDRED("Placement refusé\n"	);
				  	}  
				}
				accepte = 0;
				break;
			}

			case 4:{
				if (matchEmpty(game)){
					if (dep==1) {
					  getPrevious(game,id_Tuile_prec,previousx,previousy);
						printf("Vous avez récupéré le tableau précedent\n");
						game->nbTuilesPose--;
						dep=0;
					}
					else printf("Le dernier placement a déja été annulé, veuillez effectuer une nouvelle pose de tuiles avant d'annuler\n");
				}
				else
					printf("le tableau représente la situation initiale du jeu , vous ne pouvez pas annuler");
				
				break;
			}

		    case 5:{
		    	tuile_selected=-1;
		    	printf("Quelle tuile voulez-vous changer d'orientation ? \n");
		    	scanf("%d",&tuile_selected);
		    	purger();

		    	printf("Quelle est l'orientation souhaité ? (N/E/W/S) \n");
		    	scanf(" %c",&orientation_selected);
		    	purger();
		    	if (tuile_selected != -1 && (orientation_selected == 'N' || orientation_selected == 'S' || orientation_selected == 'E' || orientation_selected == 'W')) {
					game->tuiles[tuile_selected]=rotateTuile(game->tuiles[tuile_selected],orientation_selected);
				}
				break;
		    }

		    case 6:{
			    int x,nbVille,nbPos=0;
			    char y;
			    Position* posChecked = malloc((MAXTUILES * 6)*sizeof(Position));

				printf("Qu'elle est abscisse du ville choisie ? \n");
			    scanf("%d",&x);
			    purger();

				printf("Qu'elle est ordonné du ville choisie ? \n");
			    scanf(" %c",&y);
			    purger();

			    if(!(y >= 97 && y < 97+game->taille) && !(y >= 65 && y < 65+game->taille))
			    printf("Abcisse incorrect ! Saisir une lettre entre A et %c\n", (char)(65+game->taille-1)); // On est contraint de supposer n <= 26
				else {
				  		if(y >= 97 && y < 97+game->taille){ 
				      		//ici y est une minuscule
							y -= 97;
				      		}
				      		else
				      			y -= 65;
				    	}

				if (game->plateau[x][(int) y]!='V') 
					LOG_BOLDRED("Ceci n'est pas une ville\n");
				else {
					nbVille = Add_Case_And_Check_Around(game,'V',x, y,posChecked,&nbPos,ville,0);
					if (nbVille== 1) 
						printf("cette ville n'est associé à aucun village");
					else 
						printVillage(ville,nbVille);
				}
				free(posChecked);
				break;
		    }


		  
		    case 7:{

		    	stopsolveur = 0;
		    	clearScreen();
		    	while (stopsolveur==0){
			    	
			    	printf("\nQue voulez-vous faire ?\n");
		 			printf("1 - Appliquer le solveur sur le plateau initial\n");
		 			printf("2 - Appliquer le solveur sur le plateau actuel\n");
		 			printf("3 - Changer le niveau du solveur (son niveau est de %d/%d)\n",game->nivSolv,game->nbTuiles-1);
		 			printf("0 - Quitter le Solveur\n");
		 						
		 			choixsolv = 0;
		 			scanf("%d",&choixsolv);
		 			purger();

		 			switch(choixsolv){
		 				case 1:{

		 					clearScreen();
					    	
					    	Game Solvgame;
			    
					    	Solvgame.plateau = alloc_int_array(game->taille,game->taille);
							Solvgame.plateauIDmax = alloc_int_array(game->taille,game->taille);
							Solvgame.previousNBCasesRec = (int*)malloc(6*sizeof(int)); 
							Solvgame.tuiles = (Tuile*)malloc(MAXTUILES*sizeof(Tuile));
					    
							copieGame2(&gameInitial,&Solvgame);

					    	Game copieGame;
			    
					    	copieGame.plateau = alloc_int_array(game->taille,game->taille);
							copieGame.plateauIDmax = alloc_int_array(game->taille,game->taille);
							copieGame.previousNBCasesRec = (int*)malloc(6*sizeof(int)); 
							copieGame.tuiles = (Tuile*)malloc(MAXTUILES*sizeof(Tuile));
					    
							copieGame2(&gameInitial,&copieGame);



					    	iterSolvNaif(copieGame,&Solvgame,game->nivSolv-1,ville);
					    	

					    	printf("Le solveur a trouvé:\n");
					    	printf("\n");
			    			printPlateau(Solvgame.plateau,game->taille);

			    			printf("Et son SCORE est: %d\n",getScore(&Solvgame,ville,1));

			    			freeGame(&Solvgame,1);
			    			freeGame(&copieGame,1);
			    			break;
		 				}
		 				case 2:{
		 					clearScreen();
					    	
					    	Game Solvgame;
			    
					    	Solvgame.plateau = alloc_int_array(game->taille,game->taille);
							Solvgame.plateauIDmax = alloc_int_array(game->taille,game->taille);
							Solvgame.previousNBCasesRec = (int*)malloc(6*sizeof(int)); 
							Solvgame.tuiles = (Tuile*)malloc(MAXTUILES*sizeof(Tuile));
					    
					    	copieGame2(game,&Solvgame);

					    	Game copieGame;
			    
					    	copieGame.plateau = alloc_int_array(game->taille,game->taille);
							copieGame.plateauIDmax = alloc_int_array(game->taille,game->taille);
							copieGame.previousNBCasesRec = (int*)malloc(6*sizeof(int)); 
							copieGame.tuiles = (Tuile*)malloc(MAXTUILES*sizeof(Tuile));


							copieGame2(game,&copieGame);


					    	iterSolvNaif(copieGame,&Solvgame,game->nivSolv-1,ville);
					    	
					    	printf("Le solveur a trouvé:\n");
					    	printf("\n");
			    			printPlateau(Solvgame.plateau,game->taille);

			    			printf("Et son SCORE est: %d\n",getScore(&Solvgame,ville,1));

			    			freeGame(&copieGame,1);
			    			freeGame(&Solvgame,1);
			    			break;
		 				}
		 				case 3:{
		 					accepte=0;
		 					while(accepte==0){
			 					printf("Quel niveau voulez-vous pour le solveur ?\n");
			 					printf("Le niveau correspond aux anticipations du solveur\n"); 
			 					printf("1: Solveur nul mais très rapide (Glouton)\n");
			 					if (game->nbTuiles>2) printf("2: Solveur moyen et rapide\n"); 
			 					if (game->nbTuiles>3) printf("3: Solveur bon mais lent\n"); 
			 					if (game->nbTuiles>4) printf("4: Solveur très bon mais très lent\n");
			 					if (game->nbTuiles>5) printf("entre 5 et %d : Solveur excellent mais horrible\n",game->nbTuiles-1);
			 					
			 					scanf("%d",&choixniv);
			 					purger();

			 					if (choixniv < game->nbTuiles){
			 						accepte=1;
			 						game->nivSolv=choixniv;
			 					}
			 					else printf("Niveau invalide\n");
		 					}
		 					clearScreen();
		 					break;
		 					
		 				}

		 				case 0:{
		 					stopsolveur=1;
		 					clearScreen();
		 					break;
		 					
		 				}
		 			}

				}

		    	break;
		    }


			case 8:{
			  if (game->nbTuilesPose==game->nbTuiles){
			    clearScreen();
			    printf("Vous avez marqué %d points !",getScore(game,ville,0));
			  
			    //Comptage des points à faire
			    stop=1;
			  }
			  break;
		    }

			/*QUITTER LE PROGRAMME*/
			case 0:{
				freeGame(game,1);
				freeGame(&gameInitial,1);
				for(int i=0;i<game->taille;i++){
					free(ville[i]);
				}
				free(ville);
				stop = 1;
				return EXIT_SUCCESS;
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}


// ######################################
//	DIVERS FONCTIONS
// ######################################

int fileExist(const char* filename){
    struct stat buffer;
    int exist = stat(filename,&buffer);
    if(exist == 0)
        return 1;
    else // -1
        return 0;
}

void purger(void){   
	int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

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
