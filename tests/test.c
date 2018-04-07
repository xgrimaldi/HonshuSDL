#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include <CUnit/CUnit.h>
#include "../src/game.h"
#include "../src/plateau.h"
#include "../src/tuile.h"


/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite(void)
{
	return 0;
}


/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void)
{
	return 0;	
}

/*
* Teste que l'initialisation à partir d'un fichier est réussi.
*/
void test_LoadGame(void){
	Game* partie = malloc(sizeof(Game));
	partie->tuiles= malloc(MAXTUILES * sizeof(Tuile));
	CU_ASSERT_NOT_EQUAL(LoadGame("../bin/Partie1","../bin/Tuiles",partie), EXIT_FAILURE);
	free(partie->plateau);
	free(partie->tuiles);
	free(partie);
}


/*
* Teste si lorsque l'on crée télécharger des tuiles d'un fichier , la fonction renvoie bien la bon nombre de valeurs.
*/
void test_Load_Tuiles(void)
{
  Tuile gameTuiles[MAXTUILES];
  CU_ASSERT_EQUAL(LoadTuiles("../bin/Tuiles",gameTuiles), 21);
}


/* Teste si une fonction génère bien un nombre n de tuile connaissant l'environnement*/

void test_randomTuile(void){
	Tuile* tuile = randomTuile(1);
		CU_ASSERT_EQUAL(tuile[0].id , 0);
		CU_ASSERT_TRUE(tuile[0].X_1=='L' || tuile[0].X_1=='P' || tuile[0].X_1=='F' || tuile[0].X_1=='V' || tuile[0].X_1=='U' || tuile[0].X_1=='R');
		CU_ASSERT_TRUE(tuile[0].X_2=='L' || tuile[0].X_2=='P' || tuile[0].X_2=='F' || tuile[0].X_2=='V' || tuile[0].X_2=='U' || tuile[0].X_2=='R');
		CU_ASSERT_TRUE(tuile[0].X_3=='L' || tuile[0].X_3=='P' || tuile[0].X_3=='F' || tuile[0].X_3=='V' || tuile[0].X_3=='U' || tuile[0].X_3=='R');
		CU_ASSERT_TRUE(tuile[0].X_4=='L' || tuile[0].X_4=='P' || tuile[0].X_4=='F' || tuile[0].X_4=='V' || tuile[0].X_4=='U' || tuile[0].X_4=='R');
		CU_ASSERT_TRUE(tuile[0].X_5=='L' || tuile[0].X_5=='P' || tuile[0].X_5=='F' || tuile[0].X_5=='V' || tuile[0].X_5=='U' || tuile[0].X_5=='R');
		CU_ASSERT_TRUE(tuile[0].X_6=='L' || tuile[0].X_6=='P' || tuile[0].X_6=='F' || tuile[0].X_6=='V' || tuile[0].X_6=='U' || tuile[0].X_6=='R');
}


/*
* Teste si une tuille est bien copiée.
*/
void test_copyTuile(void){
	Tuile* tuile = randomTuile(1);
	Tuile new = copyTuile(tuile[0]);
	CU_ASSERT_TRUE(new.X_1==tuile[0].X_1 &&	new.X_2==tuile[0].X_2 && new.X_3==tuile[0].X_3 && new.X_4==tuile[0].X_4 && new.X_5==tuile[0].X_5 && new.X_6==tuile[0].X_6)

}

/*
* Test si la rotation d'une tuile est effectuée correctement
*/
void test_rotateTuile(void){
	Tuile tuile =  newTuile(0, 'L', 'F', 'V', 'U', 'R', 'P');
	tuile = rotateTuile(tuile ,'W');
	CU_ASSERT_TRUE(tuile.orientation=='W');
	tuile = rotateTuile(tuile ,'S');
	CU_ASSERT_TRUE(tuile.orientation=='S');

}


/*
* Test si la tuile crée est conforme au valeurs données
*/
void test_newTuile(){
	Tuile tuile =  newTuile(0, 'L', 'F', 'V', 'U', 'R', 'P');
	CU_ASSERT_TRUE(tuile.id == 0);
	CU_ASSERT_TRUE(tuile.X_1=='L');
	CU_ASSERT_TRUE(tuile.X_2=='F');
	CU_ASSERT_TRUE(tuile.X_3=='V');
	CU_ASSERT_TRUE(tuile.X_4=='U');
	CU_ASSERT_TRUE(tuile.X_5=='R');
	CU_ASSERT_TRUE(tuile.X_6=='P');
}

/* 
* Teste si la fonction renvoi un succes si la tuile est placée et un échec sinon
*/
void test_placeTuile(void){
	Game* partie = malloc(sizeof(Game));
	partie->tuiles = randomTuile(3);
	partie->nbTuiles = 3;
	partie->taille=20;
	partie -> tuiles[2].orientation='S';
	partie->plateau = alloc_int_array(20,20);					
	partie->plateauIDmax = alloc_int_array(20,20);
	partie->previous = alloc_int_array(20,20);
	partie->previousIDmax = alloc_int_array(20,20);
	partie->previousNBCasesRec = (int*)malloc(6*sizeof(int)); 
	initPlateau(partie->plateau,20,0);
	initPlateau(partie->plateauIDmax,20,-1);
	initPlateau(partie->previous,20,0);
	initPlateau(partie->previousIDmax,20,-1);
	initPlacementTuileRandom(partie);
	CU_ASSERT_TRUE(placeTuile(partie,2,0,1)==EXIT_FAILURE);
	freeGame(partie);
}


/*
* Teste leseventuelles contraintes rélatives au placement d'une tuile
*/
void test_canPlaceTuile(){
	Game* partie = malloc(sizeof(Game));
	partie->tuiles = randomTuile(3);
	partie->nbTuiles = 3;
	partie->taille=20;
	partie -> tuiles[2].orientation='S';
	partie->plateau = alloc_int_array(20,20);					
	partie->plateauIDmax = alloc_int_array(20,20);
	partie->previous = alloc_int_array(20,20);
	partie->previousIDmax = alloc_int_array(20,20);
	partie->previousNBCasesRec = (int*)malloc(6*sizeof(int));
	initPlateau(partie->plateau,20,0);
	initPlateau(partie->plateauIDmax,20,-1);
	initPlateau(partie->previous,20,0);
	initPlateau(partie->previousIDmax,20,-1);
	initPlacementTuileRandom(partie);
	int pos_ligne = (partie->taille/2)-1;
	int pos_col = (partie->taille/2)-1;
	CU_ASSERT_TRUE(canPlaceTuile(*partie,1,0,1)== 0); // Toute nouvelle tuile posée doit recouvrir au moins une case de l’une des tuile précédemment posée
	for (int i=pos_ligne; i<pos_ligne+2 ;i++){
	for (int j=pos_col; j<pos_col+3 ;j++){
				partie->plateau[i][j] = 'L';
		}
	}
	CU_ASSERT_TRUE(canPlaceTuile(*partie,1,0,1)== 0); // Aucune case Lac ne peut être recouverte.
	freeGame(partie);
}


/* teste si la fonction renvoie bien un entier compris entre /a a et /a b */
void test_randomMinMax(void){
	int a = randomMinMax(2,10);
	CU_ASSERT_TRUE((a>=2) && (a<=10));
}


/*teste si la fonction réalise bien l'allocation dynamique de chaque table du tableau*/

void test_alloc_int_array(void){
	int** a = alloc_int_array(10,10);
	initPlateau(a,10,0);

	CU_ASSERT_PTR_NOT_NULL(a);
	
	for(int i; i<10; i++){
		free(a[i]);
	}
	free(a);
}



/* teste que une tuile choisie aléatoirement a bien été placée au centre du plateau de jeu*/
void test_initPlacementTuileRandom (void){
	Game* partie = malloc(sizeof(Game));
	partie->tuiles = randomTuile(3);
	partie->nbTuiles = 3;
	partie->taille=20;
	partie->plateau = alloc_int_array(20,20);					
	partie->plateauIDmax = alloc_int_array(20,20);
	partie->previous = alloc_int_array(20,20);
	partie->previousIDmax = alloc_int_array(20,20);
	initPlateau(partie->plateau,20,0);
	initPlateau(partie->plateauIDmax,20,-1);
	initPlateau(partie->previous,20,0);
	initPlateau(partie->previousIDmax,20,-1);
	partie->previousNBCasesRec = (int*)malloc(6*sizeof(int));
	initPlacementTuileRandom(partie);
	for (int i=9; i<9+2 ;i++){
		for (int j=9; j<9+2 ;j++){
			CU_ASSERT_NOT_EQUAL(partie->plateau[i][j],0);
		}
	}
	freeGame(partie);
}


/*
*Teste si toute les cases du tableau ont été initialisées à la valeur souhaité
*/ 
void test_initPlateau(){
	int **plateau = alloc_int_array(20,20);
	initPlateau(plateau,20,5);
	for (int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			CU_ASSERT_EQUAL(plateau[i][j],5);
		}
	}
	for(int i; i<10; i++)
		free(plateau[i]);
	free(plateau);
}


/*
*Teste si un couple de coordonnées appartient au plateau de jeu
*ce test permet aussi de faire un test pour s'assurer que les tuiles sont placées dans le plateau
*/
void test_inPlateau(){
 	CU_ASSERT_EQUAL(inPlateau(50,7,20),0);
 	CU_ASSERT_EQUAL(inPlateau(14,7,20),1);
 	CU_ASSERT_EQUAL(inPlateau(10,700,20),0);
 	CU_ASSERT_EQUAL(inPlateau(3,7,20),1);
 	
}


void test_saveGame(void){
	Game* partie = malloc(sizeof(Game));
	partie->tuiles = randomTuile(3);
	partie->nbTuiles = 3;
	partie->taille=20;
	partie->plateau = alloc_int_array(20,20);					
	partie->plateauIDmax = alloc_int_array(20,20);
	partie->previous = alloc_int_array(20,20);
	partie->previousIDmax = alloc_int_array(20,20);
	partie->previousNBCasesRec = (int*)malloc(6*sizeof(int));
	initPlateau(partie->plateau,20,0);
	initPlateau(partie->plateauIDmax,20,-1);
	initPlateau(partie->previous,20,0);
	initPlateau(partie->previousIDmax,20,-1);
	partie->plateau[1][3]='C';
	partie->plateauIDmax[0][0]=5;
	savePlateau(partie);
	for (int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			CU_ASSERT_TRUE(partie->previous[i][j]==partie->plateau[i][j]);
			CU_ASSERT_TRUE(partie->previousIDmax[i][j]==partie->plateauIDmax[i][j]);
		}
	}
	freeGame(partie);
}

/*teste si la fonction récupère bien un tableau corrpondant a clui passé en arguments*/
void test_getPrevious (void){
	Game* partie = malloc(sizeof(Game));
	partie->tuiles = randomTuile(3);
	partie->nbTuiles = 3;
	partie->taille=20;
	partie->plateau = alloc_int_array(20,20);					
	partie->plateauIDmax = alloc_int_array(20,20);
	partie->previous = alloc_int_array(20,20);
	partie->previousIDmax = alloc_int_array(20,20);
	partie->previousNBCasesRec = (int*)malloc(6*sizeof(int));
	initPlateau(partie->plateau,20,0);
	initPlateau(partie->plateauIDmax,20,-1);
	initPlateau(partie->previous,20,0);
	initPlateau(partie->previousIDmax,20,-1);
	partie->plateau[1][3]='C';
	partie->plateauIDmax[0][0]=5;
	getPrevious(partie,1,2,3);
	for (int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			CU_ASSERT_TRUE(partie->plateau[i][j]==partie->previous[i][j]);
			CU_ASSERT_TRUE(partie->plateauIDmax[i][j]==partie->previousIDmax[i][j]);
		}
	}
	freeGame(partie);
}


/*Teste si la fonction renvoie bien un échec si le tableau contient au moins une case non nulle et un succés sinon*/
void test_matchEmpty (void){
	Game* partie = malloc(sizeof(Game));
	partie->tuiles = randomTuile(3);
	partie->nbTuiles = 3;
	partie->taille=20;
	partie->plateau = alloc_int_array(20,20);					
	partie->plateauIDmax = alloc_int_array(20,20);
	partie->previous = alloc_int_array(20,20);
	partie->previousIDmax = alloc_int_array(20,20);
	partie->previousNBCasesRec = (int*)malloc(6*sizeof(int));
	initPlateau(partie->plateau,20,0);
	initPlateau(partie->plateauIDmax,20,-1);
	initPlateau(partie->previous,20,0);
	initPlateau(partie->previousIDmax,20,-1);
	CU_ASSERT_TRUE(matchEmpty(partie)==EXIT_SUCCESS);
	partie->previous[1][1]=3;
	CU_ASSERT_TRUE(matchEmpty(partie)==EXIT_FAILURE);
	freeGame(partie);
}

void test_testRecouvrementTotal(){
	Game* partie = malloc(sizeof(Game));
	partie->tuiles = randomTuile(3);
	partie->nbTuiles = 3;
	partie->taille=20;
	partie->plateau = alloc_int_array(20,20);					
	partie->plateauIDmax = alloc_int_array(20,20);
	partie->previous = alloc_int_array(20,20);
	partie->previousIDmax = alloc_int_array(20,20);
	partie->previousNBCasesRec = (int*)malloc(6*sizeof(int));
	initPlateau(partie->plateau,20,0);
	initPlateau(partie->plateauIDmax,20,-1);
	initPlateau(partie->previous,20,0);
	initPlateau(partie->previousIDmax,20,-1);
	initPlacementTuileRandom(partie);
	partie -> tuiles[1].orientation='W';
	CU_ASSERT_EQUAL(testRecouvrementTotal(partie,1,9,'j'),-1); //une tuile de doit pas être totalement recouverte

}

int main()
{
   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite, clean_suite);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   if (
   	(NULL == CU_add_test(pSuite, "Test d'initialisation a partir d'un fichier", test_LoadGame))  ||
   	(NULL == CU_add_test(pSuite, "Test d'allocation mémoire d'un tableau", test_alloc_int_array)) ||
   	(NULL == CU_add_test(pSuite, "Test du placement d'une tuile aléatoirement  choisie au centre du plateau", test_initPlacementTuileRandom)) ||
   	(NULL == CU_add_test(pSuite, "Test le choix aléatoire d'un entier compris entre deux valeurs précises", test_randomMinMax)) ||
   	(NULL == CU_add_test(pSuite, "Test de possibilité de placer une tuile en respectant l'ensemble des règles", test_canPlaceTuile)) ||
   	(NULL == CU_add_test(pSuite, "Test de placement d'une tuile", test_placeTuile)) ||
   	(NULL == CU_add_test(pSuite, "Test de création d'une tuile", test_newTuile)) ||
   	(NULL == CU_add_test(pSuite, "Test de la modification de l'orientation lors de l'exécution de la fonction rotate", test_rotateTuile)) ||
   	(NULL == CU_add_test(pSuite, "Test de copie de tuiles ", test_copyTuile))||
   	(NULL == CU_add_test(pSuite, "Test de création de tuiles aléatoires", test_randomTuile)) ||
	(NULL == CU_add_test(pSuite, "Test de chargement de tuiles à partir d'un fichier ", test_Load_Tuiles)) ||
	(NULL == CU_add_test(pSuite, "Test d'allocation mémoire d'un tableau", test_initPlateau)) ||
	(NULL == CU_add_test(pSuite, "Test de vérification de coordonnées, s'assure que le point fait bien partie du tableau de jeu", test_inPlateau)) ||
	(NULL == CU_add_test(pSuite, "Test de sauvegarde du tableau de jeu", test_saveGame)) ||
	(NULL == CU_add_test(pSuite, "Test de récupération du plateau de jeu précedent", test_getPrevious)) ||
	(NULL == CU_add_test(pSuite, "Test de vérification de tableau vide ", test_matchEmpty)) ||
	(NULL == CU_add_test(pSuite, "Test de recouvrement, s'assure que aucune tuile n'est completement couverte", test_testRecouvrementTotal))
   	) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}
