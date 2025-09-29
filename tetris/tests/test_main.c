#include <check.h>
#include <stdio.h>
#include <stdlib.h>

Suite *tetris_backend_suite(void);
Suite *fsm_suite(void);
Suite *fsm_matrix_suite(void);

int main(void) {
  int number_failed = 0;
  SRunner *sr;

  sr = srunner_create(fsm_suite());
  srunner_run_all(sr, CK_MINIMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(tetris_backend_suite());
  srunner_run_all(sr, CK_MINIMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  sr = srunner_create(fsm_matrix_suite());
  srunner_run_all(sr, CK_MINIMAL);
  number_failed += srunner_ntests_failed(sr);
  srunner_free(sr);

  printf("Total tests failed: %d\n", number_failed);
  return number_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}