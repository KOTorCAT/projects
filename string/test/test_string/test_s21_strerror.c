#include "../test_s21_string.h"

START_TEST(test_1) {
  for (size_t i = MIN_ERR; i < MAX_ERR; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(test_2) {
  int errnum = -10;
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}
END_TEST

START_TEST(test_3) {
  int errnum = 150;
  ck_assert_str_eq(s21_strerror(errnum), strerror(errnum));
}
END_TEST

Suite* test_s21_strerror() {
  Suite* s = suite_create("\033[33m S21_STRERROR \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_strerror \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);

  suite_add_tcase(s, tc);
  return s;
}