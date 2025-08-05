#include "../test_s21_string.h"

START_TEST(test_1) {
  char str[] = "Hello world!";
  char ch = 'w';
  int n = s21_strlen(str);
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(test_2) {
  char str[] = "Hello world!";
  char ch = 'l';
  int n = s21_strlen(str);
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(test_3) {
  char str[] = "Hello world!";
  char ch = ' ';
  int n = s21_strlen(str);
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(test_4) {
  char str[] = "Hello world!";
  char ch = '\0';
  int n = s21_strlen(str);
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(test_5) {
  char str[] = "Hell\no world!";
  char ch = '\n';
  int n = s21_strlen(str);
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(test_6) {
  char str[] = "";
  char ch = '\n';
  int n = s21_strlen(str);
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(test_7) {
  char str[] = "a1aab";
  char ch = '1';
  int n = 3;
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(test_8) {
  char str[] = "";
  char ch = '\0';
  int n = 1;
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(test_9) {
  char str[] = "\n\t";
  char ch = '\\';
  int n = s21_strlen(str);
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

START_TEST(test_10) {
  char str[] = "\\n\t";
  char ch = '\\';
  int n = s21_strlen(str);
  ck_assert_pstr_eq(s21_memchr(str, ch, n), memchr(str, ch, n));
}
END_TEST

Suite* test_s21_memchr() {
  Suite* s = suite_create("\033[33m S21_MEMCHR \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_memchr \033[0m");

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