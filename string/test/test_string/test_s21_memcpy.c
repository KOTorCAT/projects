#include "../test_s21_string.h"

START_TEST(test_1) {
  char str1[] = "Hello world!";
  char str2[] = "Hello world!";
  char res[] = "BYE BYE";
  int n = 4;
  ck_assert_str_eq(s21_memcpy(str1, res, n), memcpy(str2, res, n));
}
END_TEST

START_TEST(test_2) {
  char str1[] = "Hello world!";
  char str2[] = "Hello world!";
  char res[] = "BYE BYE";
  int n = s21_strlen(res);
  ck_assert_str_eq(s21_memcpy(str1, res, n), memcpy(str2, res, n));
}
END_TEST

START_TEST(test_3) {
  char str1[100] = "gsgs\t\t\nef even\\nn\n";
  char str2[100] = "gsgs\t\t\nef even\\nn\n";
  char res[] = "ver2q3\n\t\4n    \n \0 dfsdf";
  int n = s21_strlen(res);
  ck_assert_str_eq(s21_memcpy(str1, res, n), memcpy(str2, res, n));
}
END_TEST

START_TEST(test_4) {
  char str1[100] = "gsgs\t\t\nef even\\nn\n";
  char str2[100] = "gsgs\t\t\nef even\\nn\n";
  char res[] = "ver2q3\n\t\4n    \n \0 dfsdf";
  int n = 0;
  ck_assert_str_eq(s21_memcpy(str1, res, n), memcpy(str2, res, n));
}
END_TEST

START_TEST(test_5) {
  char str1[100] = "";
  char str2[100] = "";
  char res[] = "ver2q3\n\t\4n    \n \0 dfsdf";
  int n = 10;
  ck_assert_str_eq(s21_memcpy(str1, res, n), memcpy(str2, res, n));
}
END_TEST

START_TEST(test_6) {
  char str1[100] = "";
  char str2[100] = "";
  char res[] = "ve\0r2q3\n\t\4n    \n \0 dfsdf";
  int n = 10;
  ck_assert_str_eq(s21_memcpy(str1, res, n), memcpy(str2, res, n));
}
END_TEST

START_TEST(test_7) {
  char str1[100] = "";
  char str2[100] = "";
  char res[] = "\0";
  int n = 1;
  ck_assert_str_eq(s21_memcpy(str1, res, n), memcpy(str2, res, n));
}
END_TEST

START_TEST(test_8) {
  char str1[100] = "";
  char str2[100] = "";
  char res[] = "\n\t dg r\n\0rrt";
  int n = 10;
  ck_assert_str_eq(s21_memcpy(str1, res, n), memcpy(str2, res, n));
}
END_TEST

START_TEST(test_9) {
  char str1[100] = "";
  char str2[100] = "";
  char res[] = "";
  int n = s21_strlen(res);
  ck_assert_str_eq(s21_memcpy(str1, res, n), memcpy(str2, res, n));
}
END_TEST

START_TEST(test_10) {
  char str1[100] = "fbdf\n\0hfh";
  char str2[100] = "fbdf\n\0hfh";
  char res[] = "\t\t\t\\0\n\fg\f";
  int n = s21_strlen(res);
  ck_assert_str_eq(s21_memcpy(str1, res, n), memcpy(str2, res, n));
}
END_TEST

Suite* test_s21_memcpy() {
  Suite* s = suite_create("\033[33m S21_MEMCPY \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_memcpy \033[0m");

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