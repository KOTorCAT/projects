#include "test_s21_decimal.h"

START_TEST(test_1) {
  // максимальное число 79,228,162,514,264,337,593,543,950,335

  s21_big_decimal dec = {{7658}};
  s21_big_decimal result = {0};
  int scale = 2;
  int pattern = 76;

  s21_round_big_decimal(dec, &scale, &result);

  ck_assert_int_eq(result.bits[0], pattern);
}
END_TEST

Suite *test_s21_round_big_decimal() {
  Suite *s = suite_create("\033[33m S21_ROUND_BIG_DECIMAL \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_round_big_decimal \033[0m");

  tcase_add_test(tc, test_1);

  suite_add_tcase(s, tc);
  return s;
}