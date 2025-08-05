#include "../test_s21_string.h"

START_TEST(test_1) {
  char str[] = "Hello, world!";
  int ch = 'o';

  ck_assert_pstr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(test_2) {
  char str[] = "Hello, world!";
  int ch = 'l';

  ck_assert_pstr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(test_3) {
  char str[] = "Hello, world!";
  int ch = '\0';

  ck_assert_pstr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(test_4) {
  char str[] = "Hello, world!";
  int ch = ' ';

  ck_assert_pstr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(test_5) {
  char str[] = "Hello,21312 world!";
  int ch = '2';

  ck_assert_pstr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(test_6) {
  char str[] = "Hello,21312 \nworld\n!";
  int ch = '\n';

  ck_assert_pstr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(test_7) {
  char str[] = "";
  int ch = '\n';

  ck_assert_pstr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(test_8) {
  char str[] = "";
  int ch = '\0';

  ck_assert_pstr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(test_9) {
  char str[] = "\0 ff \0 ff";
  int ch = '\0';

  ck_assert_pstr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

START_TEST(test_10) {
  char str[] = "dsfds\n\\0\n\0 \n\\";
  int ch = '\\';

  ck_assert_pstr_eq(s21_strchr(str, ch), strchr(str, ch));
}
END_TEST

Suite* test_s21_strchr() {
  Suite* s = suite_create("\033[33m S21_STRCHR \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_strchr \033[0m");

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