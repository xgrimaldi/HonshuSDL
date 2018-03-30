#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include <CUnit/CUnit.h>
#include "../src/game.h"

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
* Teste si lorsque l'on crée télécharger des tuiles d'un fichier , la fonction renvoie bien la bon nombre de valeurs.
*/
void test_Load_Tuiles(void)
{
  Tuile gameTuiles[MAXTUILES];
  CU_ASSERT_EQUAL(LoadTuiles("../bin/Tuiles",gameTuiles), 21);
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

/* teste si une fonction génère bien un nombre n de tuile connaissant l'environnement*/

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


/*teste si la fonction réalise bien l'allocation dynamique de chaque table du tableau*/

void test_alloc_int_array(void){
	int** a = alloc_int_array(10,10);
	initPlateau(a,10);

	CU_ASSERT_PTR_NOT_NULL(a);
	
	for(int i; i<10; i++){
		free(a[i]);
	}
	free(a);
}


/* teste si toutes les cases d'un tableau sont bien initialisées ssssà 0.*/
void test_initPlateau(void){
	int ** a = alloc_int_array(10,10);
	initPlateau(a,10);

	for (int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			CU_ASSERT_EQUAL(a[i][j],0);
		}
	}
	for(int i; i<10; i++)
		free(a[i]);
	free(a);
}

/* teste que une tuile choisie aléatoirement a bien été placée au centre du plateau de jeu*/
void test_initPlacementTuileRandom (void){
	Game* partie = malloc(sizeof(Game));
	partie->plateau = alloc_int_array(20, 20);
	initPlateau(partie->plateau,20);
	partie->tuiles = randomTuile(3);
	partie->nbTuiles = 3;
	partie->nbTuilesPose=1;
	partie->taille=20;
	initPlacementTuileRandom(partie);
	for (int i=9; i<9+3 ;i++){
		for (int j=9; j<9+2 ;j++){
			CU_ASSERT_NOT_EQUAL(partie->plateau[i][j],0);
		}
	}
	for(int i=0;i<partie->taille;i++){
		free(partie->plateau[i]);
	}
	free(partie->plateau);
	free(partie->tuiles);
	free(partie);
}


/* teste si la fonction renvoie bien un entier compris entre /a a et /a b */
void test_randomMinMax(void){
	int a = randomMinMax(2,10);
	CU_ASSERT_TRUE((a>=2) && (a<=10));
}

/* teste si la fonction renvoi un succes si la tuile est placée et un échec sinon*/
void test_placeTuile(void){
	Game* partie = malloc(sizeof(Game));
	partie->plateau = alloc_int_array(20, 20);
	initPlateau(partie->plateau,20);
	int** previous;
	previous = alloc_int_array(20, 20);
	initPlateau(previous,20);
	partie->tuiles = randomTuile(3);
	partie->nbTuiles = 3;
	partie->taille=20;
	partie -> tuiles[2].orientation='S';
	CU_ASSERT_TRUE(placeTuile(partie,2,0,1,previous)==EXIT_FAILURE);
	for(int i=0;i<partie->taille;i++){
		free(partie->plateau[i]);
		free(previous[i]);
	}
	free(previous);
	free(partie->plateau);
	free(partie->tuiles);
	free(partie);
}

void test_copyTuile(void){
	Tuile* tuile = randomTuile(1);
	Tuile new = copyTuile(tuile[0]);
	CU_ASSERT_TRUE(new.X_1==tuile[0].X_1 &&	new.X_2==tuile[0].X_2 && new.X_3==tuile[0].X_3 && new.X_4==tuile[0].X_4 && new.X_5==tuile[0].X_5 && new.X_6==tuile[0].X_6)

}

/*fonction qui teste que le tableau sauvgardé est bien identique à celui passé en arguments*/
void test_saveGame(void){
	Game* partie = malloc(sizeof(Game));
	partie->plateau = alloc_int_array(20, 20);
	initPlateau(partie->plateau,20);
	partie->plateau[0][0]=5;
	int** previous;
	previous = alloc_int_array(20, 20);
	initPlateau(previous,20);
	saveGame(partie,previous);
	for (int i=0;i<20;i++){
		for(int j=0;j<20;j++){
			CU_ASSERT_TRUE(partie->plateau[i][j]==previous[i][j]);
		}
	}
	for(int i=0;i<partie->taille;i++){
		free(partie->plateau[i]);
		free(previous[i]);
	}
	free(partie->plateau);
	free(previous);
	free(partie);

}

/*teste si la fonction récupère bien un tableau corrpondant a clui passé en arguments*/
void test_getPrevious (void){
	Game* partie = malloc(sizeof(Game));
	partie->plateau = alloc_int_array(20, 20);
	initPlateau(partie->plateau,20);
	int** previous;
	previous = alloc_int_array(20, 20);
	initPlateau(previous,20);
	previous[0][0]=5;
	partie->tuiles = randomTuile(3);
	getPrevious(partie, previous,0);
	for (int i=0;i<20;i++){
	for(int j=0;j<20;j++){
			CU_ASSERT_TRUE(partie->plateau[i][j]==previous[i][j]);
		}
	}
	for(int i=0;i<partie->taille;i++){
		free(partie->plateau[i]);
		free(previous[i]);
	}
	free(partie->plateau);
	free(partie->tuiles);
	free(previous);
	free(partie);
}


/*Teste si la fonction renvoie bien un échec si le tableau contient au moins une case non nulle et un succés sinon*/
void test_matchEmpty (void){
	int** a= alloc_int_array(20, 20);
	initPlateau(a,20);
	CU_ASSERT_TRUE(matchEmpty(a,20)==EXIT_SUCCESS);
	a[1][5]=3;
	CU_ASSERT_TRUE(matchEmpty(a,20)==EXIT_FAILURE);
	
	for(int i=0;i<20;i++){
		free(a[i]);
	}
	free(a);
}

/* main() fonction
 * Retourne CUE_SUCCESS sur un traitement réussi
 * CUnit Error sur échecs 
 */ 
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
   	(NULL == CU_add_test(pSuite, "Test Chargement Tuiles", test_Load_Tuiles))  ||
   	(NULL == CU_add_test(pSuite, "Test Entier aléatoire", test_randomMinMax)) ||
   	(NULL == CU_add_test(pSuite, "Test d'initialisation des cases d'un tableeau à 0", test_initPlateau)) ||
   	(NULL == CU_add_test(pSuite, "Test du placement d'une tuile aléatoirement  choisie au centre du plateau", test_initPlacementTuileRandom)) ||
   	(NULL == CU_add_test(pSuite, "Test de création d'un tableau de tuile aléatoire", test_randomTuile)) ||
   	(NULL == CU_add_test(pSuite, "Test d'initialisation a partir d'un fichier", test_LoadGame)) ||
   	(NULL == CU_add_test(pSuite, "Test de possibilité de placement de tuile", test_placeTuile)) ||
   	(NULL == CU_add_test(pSuite, "Test de copie d'une tuile", test_copyTuile)) ||
   	(NULL == CU_add_test(pSuite, "Test de sauvegarde d'un plateau de jeu", test_saveGame)) ||
   	(NULL == CU_add_test(pSuite, "Test récupération d'un tableau dans un autre ", test_getPrevious))||
   	(NULL == CU_add_test(pSuite, "Test de vérification des tableaux vides", test_matchEmpty)) ||
	(NULL == CU_add_test(pSuite, "Test d'allocation", test_alloc_int_array))
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
