#include "test_s21_decimal.h"

int main() {
  Suite *tests[] = {test_s21_add(),
                    test_s21_div(),
                    test_s21_mul(),
                    test_s21_sub(),
                    decimal_suite(),
                    test_s21_from_int_to_decimal(),
                    test_s21_from_decimal_to_int(),
                    test_s21_from_float_to_decimal(),
                    test_s21_from_decimal_to_float(),
                    test_s21_truncate(),
                    test_s21_round(),
                    test_s21_floor(),
                    test_s21_negate(),
                    NULL};

  for (int i = 0; tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    srunner_free(sr);
  }

  return 0;
}
