#include "../test_s21_string.h"

START_TEST(test_1) {
  int n = 5;
  char res1[] = "Hello world!";
  char res2[] = "Hello world!";
  char str = 'w';
  ck_assert_str_eq(s21_memset(res1, str, n), memset(res2, str, n));
}
END_TEST

START_TEST(test_2) {
  char res1[] = "Hello world!";
  char res2[] = "Hello world!";
  int n = s21_strlen(res1);
  char str = 'l';
  ck_assert_str_eq(s21_memset(res1, str, n), memset(res2, str, n));
}
END_TEST

START_TEST(test_3) {
  char res1[] = "sadas 231 aaaa \t\t\tsfdsf";
  char res2[] = "sadas 231 aaaa \t\t\tsfdsf";
  int n = 10;
  char str = 'a';
  ck_assert_str_eq(s21_memset(res1, str, n), memset(res2, str, n));
}
END_TEST

START_TEST(test_4) {
  char res1[] = "sadas 231 aaaa \t\t\tsfdsf";
  char res2[] = "sadas 231 aaaa \t\t\tsfdsf";
  int n = s21_strlen(res1);
  char str = 'a';
  ck_assert_str_eq(s21_memset(res1, str, n), memset(res2, str, n));
}
END_TEST

START_TEST(test_5) {
  char res1[] = "sadas 231 aaaa \t\t\tsfdsf";
  char res2[] = "sadas 231 aaaa \t\t\tsfdsf";
  int n = 5;
  char str = '\0';
  ck_assert_str_eq(s21_memset(res1, str, n), memset(res2, str, n));
}
END_TEST

START_TEST(test_6) {
  char res1[] = "";
  char res2[] = "";
  int n = 0;
  char str = '\n';
  ck_assert_str_eq(s21_memset(res1, str, n), memset(res2, str, n));
}
END_TEST

START_TEST(test_7) {
  char res1[] = "";
  char res2[] = "";
  int n = 0;
  char str = '\0';
  ck_assert_str_eq(s21_memset(res1, str, n), memset(res2, str, n));
}
END_TEST

START_TEST(test_8) {
  char res1[] = "\t\twqeqwe wad a\0 asdaksdk";
  char res2[] = "\t\twqeqwe wad a\0 asdaksdk";
  int n = 20;
  char str = '\n';
  ck_assert_str_eq(s21_memset(res1, str, n), memset(res2, str, n));
}
END_TEST

START_TEST(test_9) {
  char res1[] = "\t\twqeqwe wad a\0 asdaksdk";
  char res2[] = "\t\twqeqwe wad a\0 asdaksdk";
  int n = 20;
  char str = '\0';
  ck_assert_str_eq(s21_memset(res1, str, n), memset(res2, str, n));
}
END_TEST

START_TEST(test_10) {
  char res1[] = "\t\twqeqwe wad a\0 asdaksdk";
  char res2[] = "\t\twqeqwe wad a\0 asdaksdk";
  int n = 20;
  char str = '@';
  ck_assert_str_eq(s21_memset(res1, str, n), memset(res2, str, n));
}
END_TEST

Suite* test_s21_memset() {
  Suite* s = suite_create("\033[33m S21_MEMSET \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_memset \033[0m");

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