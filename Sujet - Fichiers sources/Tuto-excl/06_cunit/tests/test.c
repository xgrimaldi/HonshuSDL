#include <stdio.h>
#include <string.h>
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "../src/graph.h"

/* Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite(void)
{
   if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
      return -1;
   }
   else {
      return 0;
   }
}


/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void)
{
   if (0 != fclose(temp_file)) {
      return -1;
   }
   else {
      temp_file = NULL;
      return 0;
   }
}


/*
* Teste si lorsque l'on crée un graphe d'une certaine taille (ici 4), la fonction size renvoie bien la bonne valeur.
*/
void test_taille_graphe(void)
{
  graph g = create_graph(4);
  CU_ASSERT_EQUAL(size(g), 4);
  free_graph(g);
}

/*
* Teste si lorsque l'ont crée un graphe, ce graphe a initialement 0 arêtes.
*/
void test_graphe_initialement_vide(void)
{
  graph g = create_graph(4);
  int i, j;
  for(i = 0; i < 4; i++){
    for(j = 0; j < 4; j++){
      CU_ASSERT_EQUAL(is_edge(g, i, j), 0);
    }
  }
  free_graph(g);
}

void test_ajouter_arete(void)
{
  graph g = create_graph(4);
  add_edge(g, 0, 1);
  CU_ASSERT_EQUAL(is_edge(g, 0, 1), 1);
  CU_ASSERT_EQUAL(is_edge(g, 1, 0), 1);
  free_graph(g);
}

void test_retirer_arete(void)
{
  graph g = create_graph(4);
  add_edge(g, 0, 1);
  remove_edge(g, 0, 1);
  CU_ASSERT_NOT_EQUAL(is_edge(g, 0, 1), 1);
  free_graph(g);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
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
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "Test taille du graphe", test_taille_graphe)) ||
       (NULL == CU_add_test(pSuite, "Test vacuité du graphe", test_graphe_initialement_vide)) ||
       (NULL == CU_add_test(pSuite, "Test ajouter arete", test_ajouter_arete)) ||
       (NULL == CU_add_test(pSuite, "Test retirer arete", test_retirer_arete))
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
