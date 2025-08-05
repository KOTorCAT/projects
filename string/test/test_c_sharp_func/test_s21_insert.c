#include "../test_s21_string.h"

START_TEST(test_1) {
  char src[] = "Hello world!";
  char str[] = "School 21 and ";

  char *s21_res = s21_insert(src, str, 6);

  ck_assert_pstr_eq(s21_res, "Hello School 21 and world!");
  free(s21_res);
}
END_TEST

START_TEST(test_2) {
  char src[] = "Hello world!";
  char str[] = "School 21 and ";

  char *s21_res = s21_insert(src, str, 12);

  ck_assert_pstr_eq(s21_res, NULL);
  free(s21_res);
}
END_TEST

START_TEST(test_3) {
  char src[] = "Hello world!";
  char str[] = "School 21 and ";

  char *s21_res = s21_insert(src, str, -1);

  ck_assert_pstr_eq(s21_res, NULL);
  free(s21_res);
}
END_TEST

START_TEST(test_4) {
  char src[] = "Hello world!";
  char str[] = "1234";

  char *s21_res = s21_insert(src, str, 6);

  ck_assert_pstr_eq(s21_res, "Hello 1234world!");
  free(s21_res);
}
END_TEST

START_TEST(test_5) {
  char src[] = "Hello world!";
  char str[] = "    \t\t\t";

  char *s21_res = s21_insert(src, str, 6);

  ck_assert_pstr_eq(s21_res, "Hello     \t\t\tworld!");
  free(s21_res);
}
END_TEST

START_TEST(test_6) {
  char *src = NULL;
  char *str = NULL;

  char *s21_res = s21_insert(src, str, 6);

  ck_assert_pstr_eq(s21_res, NULL);
  free(s21_res);
}
END_TEST

Suite *test_s21_insert() {
  Suite *s = suite_create("\033[1;35m S21_INSERT \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_insert \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);

  suite_add_tcase(s, tc);

  return s;
}