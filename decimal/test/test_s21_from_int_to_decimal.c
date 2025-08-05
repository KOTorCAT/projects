#include <limits.h>

#include "test_s21_decimal.h"

START_TEST(test_1) {
  long int a = 5;
  s21_decimal dec = {0};

  s21_from_int_to_decimal(a, &dec);

  ck_assert_int_eq(a, dec.bits[0]);
}
END_TEST

START_TEST(test_2) {
  int a = 0;
  s21_decimal dec = {0};

  s21_from_int_to_decimal(a, &dec);

  ck_assert_int_eq(a, dec.bits[0]);
}
END_TEST

START_TEST(test_3) {
  int a = -8;
  s21_decimal dec = {0};

  s21_from_int_to_decimal(a, &dec);

  ck_assert_int_eq(a, -dec.bits[0]);
}
END_TEST

START_TEST(test_4) {
  int a = 2147483647;
  s21_decimal *dec = NULL;

  int result = s21_from_int_to_decimal(a, dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_5) {
  int a = -2147483647;
  s21_decimal dec = {0};

  int result = s21_from_int_to_decimal(a, &dec);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dec.bits[0], -a);
}
END_TEST

START_TEST(test_6) {
  long int a = 999;
  s21_decimal dec = {0};

  int result = s21_from_int_to_decimal(a, &dec);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(dec.bits[0], a);
}

END_TEST

Suite *test_s21_from_int_to_decimal() {
  Suite *s = suite_create("\033[33m S21_FROM_INT_TO_DECIMAL \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_from_int_to_decimal \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);

  suite_add_tcase(s, tc);
  return s;
}
