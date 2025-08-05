#include "../test_s21_string.h"

START_TEST(test_1) {
  char str1[10] = "";
  char str2[10] = "";
  char str[] = "Hello world!";
  int n = 5;
  ck_assert_str_eq(s21_strncpy(str1, str, n), strncpy(str2, str, n));
}
END_TEST

START_TEST(test_2) {
  char str1[10] = "fgdfg";
  char str2[10] = "fgdfg";
  char str[] = "Hello world!";
  int n = 5;
  ck_assert_str_eq(s21_strncpy(str1, str, n), strncpy(str2, str, n));
}
END_TEST

START_TEST(test_3) {
  char str1[15] = "fgdfg";
  char str2[15] = "fgdfg";
  char str[] = "Hello\n\n world!";
  int n = s21_strlen(str);
  ck_assert_str_eq(s21_strncpy(str1, str, n), strncpy(str2, str, n));
}
END_TEST

START_TEST(test_4) {
  char str1[10] = "";
  char str2[10] = "";
  char str[] = "Hel\0lo\n\n world!";
  int n = s21_strlen(str);
  ck_assert_str_eq(s21_strncpy(str1, str, n), strncpy(str2, str, n));
}
END_TEST

START_TEST(test_5) {
  char str1[10] = "";
  char str2[10] = "";
  char str[] = "";
  int n = 1;
  ck_assert_str_eq(s21_strncpy(str1, str, n), strncpy(str2, str, n));
}
END_TEST

START_TEST(test_6) {
  char str1[10] = "";
  char str2[10] = "";
  char str[] = "\0";
  int n = 1;
  ck_assert_str_eq(s21_strncpy(str1, str, n), strncpy(str2, str, n));
}
END_TEST

START_TEST(test_7) {
  char str1[100] = "";
  char str2[100] = "";
  char str[] = "\n\tlasdjasl\t\tasdmkkas";
  int n = 10;
  ck_assert_str_eq(s21_strncpy(str1, str, n), strncpy(str2, str, n));
}
END_TEST

START_TEST(test_8) {
  char str1[100] = "\t\t\0fvsdvsv";
  char str2[100] = "\t\t\0fvsdvsv";
  char str[] = "\n\tlasdjasl\t\tasdmkkas";
  int n = s21_strlen(str);
  ck_assert_str_eq(s21_strncpy(str1, str, n), strncpy(str2, str, n));
}
END_TEST

START_TEST(test_9) {
  char str1[100] = "\t\t\0fvsdvsv";
  char str2[100] = "\t\t\0fvsdvsv";
  char str[] = "\n\tlasd  \0 jasl\t\tasdmkkas";
  int n = s21_strlen(str);
  ck_assert_str_eq(s21_strncpy(str1, str, n), strncpy(str2, str, n));
}
END_TEST

START_TEST(test_10) {
  char str1[] = "\n";
  char str2[] = "\n";
  char str[] = "\0";
  int n = s21_strlen(str);
  ck_assert_str_eq(s21_strncpy(str1, str, n), strncpy(str2, str, n));
}
END_TEST

Suite* test_s21_strncpy() {
  Suite* s = suite_create("\033[33m S21_STRNCPY \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_strncpy \033[0m");

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