#include "../test_s21_string.h"

START_TEST(test_1) {
  char str1[] = "Hello world!";
  char str2[] = "Hello world!";
  int n = s21_strlen(str2);

  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

START_TEST(test_2) {
  char str1[] = "Hello world!";
  char str2[] = "Helsfdlo world!";
  int n = s21_strlen(str2);

  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

START_TEST(test_3) {
  char str1[] = "hdfsf";
  char str2[] = "hdsfrld";
  int n = 2;

  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

START_TEST(test_4) {
  char str1[] = "hdfsf";
  char str2[] = "hdsfrld";
  int n = 3;

  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

START_TEST(test_5) {
  char str1[] = "";
  char str2[] = "";
  int n = 1;

  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

START_TEST(test_6) {
  char str1[] = "\0";
  char str2[] = "";
  int n = 1;

  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

START_TEST(test_7) {
  char str1[] = "aa\0b";
  char str2[] = "aa\0c";
  int n = s21_strlen(str2);

  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

START_TEST(test_8) {
  char str1[] = "aa\n   \tb";
  char str2[] = "aa\n   \tb";
  int n = s21_strlen(str2);

  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

START_TEST(test_9) {
  char str1[] = "aa\n   \tba";
  char str2[] = "aa\n   \tbc";
  int n = s21_strlen(str2);

  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

START_TEST(test_10) {
  char str1[] = "\0";
  char str2[] = "";
  int n = s21_strlen(str2);

  int res1 = s21_strncmp(str1, str2, n);
  int res2 = strncmp(str1, str2, n);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

Suite* test_s21_strncmp() {
  Suite* s = suite_create("\033[33m S21_STRNCMP \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_strncmp \033[0m");

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