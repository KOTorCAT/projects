#include "../test_s21_string.h"

START_TEST(test_1) {
  char str1[100] = "Hello world!";
  char str2[100] = "Hello world!";
  char dop[] = " And hello school 21!";
  int n = s21_strlen(dop);

  ck_assert_str_eq(s21_strncat(str1, dop, n), strncat(str2, dop, n));
}
END_TEST

START_TEST(test_2) {
  char str1[100] = "";
  char str2[100] = "";
  char dop[] = "Hello school 21!";
  int n = s21_strlen(dop);

  ck_assert_str_eq(s21_strncat(str1, dop, n), strncat(str2, dop, n));
}
END_TEST

START_TEST(test_3) {
  char str1[100] = "";
  char str2[100] = "";
  char dop[] = "Hello school 21!";
  int n = 5;

  ck_assert_str_eq(s21_strncat(str1, dop, n), strncat(str2, dop, n));
}
END_TEST

START_TEST(test_4) {
  char str1[100] = "\n\0\n";
  char str2[100] = "\n\0\n";
  char dop[] = "Hello school 21!";
  int n = 5;

  ck_assert_str_eq(s21_strncat(str1, dop, n), strncat(str2, dop, n));
}
END_TEST

START_TEST(test_5) {
  char str1[100] = "\0";
  char str2[100] = "\0";
  char dop[] = "Hello school 21!";
  int n = 5;

  ck_assert_str_eq(s21_strncat(str1, dop, n), strncat(str2, dop, n));
}
END_TEST

START_TEST(test_6) {
  char str1[100] = "\0";
  char str2[100] = "\0";
  char dop[] = "Hello school 21!";
  int n = s21_strlen(dop);

  ck_assert_str_eq(s21_strncat(str1, dop, n), strncat(str2, dop, n));
}
END_TEST

START_TEST(test_7) {
  char str1[100] = "\0";
  char str2[100] = "\0";
  char dop[] = "\0";
  int n = 1;

  ck_assert_str_eq(s21_strncat(str1, dop, n), strncat(str2, dop, n));
}
END_TEST

START_TEST(test_8) {
  char str1[100] = "";
  char str2[100] = "";
  char dop[] = "\0";
  int n = 1;

  ck_assert_str_eq(s21_strncat(str1, dop, n), strncat(str2, dop, n));
}
END_TEST

START_TEST(test_9) {
  char str1[100] = "\n \t asas \0 dfsd";
  char str2[100] = "\n \t asas \0 dfsd";
  char dop[] = "\0";
  int n = 1;

  ck_assert_str_eq(s21_strncat(str1, dop, n), strncat(str2, dop, n));
}
END_TEST

START_TEST(test_10) {
  char str1[100] = "\n \t asas \0 dfsd";
  char str2[100] = "\n \t asas \0 dfsd";
  char dop[] = "\t\0";
  int n = 2;

  ck_assert_str_eq(s21_strncat(str1, dop, n), strncat(str2, dop, n));
}
END_TEST

Suite* test_s21_strncat() {
  Suite* s = suite_create("\033[33m S21_STRNCAT \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_strncat \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);
  tcase_add_test(tc, test_10);

  suite_add_tcase(s, tc);
  return s;
}