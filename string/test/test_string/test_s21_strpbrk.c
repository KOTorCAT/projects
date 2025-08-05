#include "../test_s21_string.h"

START_TEST(test_1) {
  char str[] = "Hello world!";
  char alf[] = "wr";

  ck_assert_pstr_eq(s21_strpbrk(str, alf), strpbrk(str, alf));
}
END_TEST

START_TEST(test_2) {
  char str[] = "Hello world!";
  char alf[] = "lo";

  ck_assert_pstr_eq(s21_strpbrk(str, alf), strpbrk(str, alf));
}
END_TEST

START_TEST(test_3) {
  char str[] = "Hello world!";
  char alf[] = "abc";

  ck_assert_pstr_eq(s21_strpbrk(str, alf), strpbrk(str, alf));
}
END_TEST

START_TEST(test_4) {
  char str[] = "He\n    zfzdf \tllo world!";
  char alf[] = "\n\t";

  ck_assert_pstr_eq(s21_strpbrk(str, alf), strpbrk(str, alf));
}
END_TEST

START_TEST(test_5) {
  char str[] = "He\n    zfzdf \tllo world!";
  char alf[] = "\0";

  ck_assert_pstr_eq(s21_strpbrk(str, alf), strpbrk(str, alf));
}
END_TEST

START_TEST(test_6) {
  char str[] = "He\n    zfz\0df \tllo world!";
  char alf[] = "\0w!";

  ck_assert_pstr_eq(s21_strpbrk(str, alf), strpbrk(str, alf));
}
END_TEST

START_TEST(test_7) {
  char str[] = "";
  char alf[] = "\0w!";

  ck_assert_pstr_eq(s21_strpbrk(str, alf), strpbrk(str, alf));
}
END_TEST

START_TEST(test_8) {
  char str[] = "\0";
  char alf[] = "\0w!";

  ck_assert_pstr_eq(s21_strpbrk(str, alf), strpbrk(str, alf));
}
END_TEST

START_TEST(test_9) {
  char str[] = "\0\0\n\0";
  char alf[] = "\nw!";

  ck_assert_pstr_eq(s21_strpbrk(str, alf), strpbrk(str, alf));
}
END_TEST

START_TEST(test_10) {
  char str[] = "fsdf\0\0\n\0";
  char alf[] = "";

  ck_assert_pstr_eq(s21_strpbrk(str, alf), strpbrk(str, alf));
}
END_TEST

Suite* test_s21_strpbrk() {
  Suite* s = suite_create("\033[33m S21_STRPBRK \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_strpbrk \033[0m");

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