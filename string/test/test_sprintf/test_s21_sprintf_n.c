#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "Hello world!%n";
  char str1[100] = "";
  char str2[100] = "";

  int s21_num = 0;
  int orig_num = 0;

  int s21 = s21_sprintf(str1, format, &s21_num);
  int orig = sprintf(str2, format, &orig_num);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(s21_num, orig_num);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "Hello%n world!%n";
  char str1[100] = "";
  char str2[100] = "";

  int s21_num_1 = 0;
  int s21_num_2 = 0;

  int orig_num_1 = 0;
  int orig_num_2 = 0;

  int s21 = s21_sprintf(str1, format, &s21_num_1, &s21_num_2);
  int orig = sprintf(str2, format, &orig_num_1, &orig_num_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(s21_num_1, orig_num_1);
  ck_assert_int_eq(s21_num_2, orig_num_2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%n";
  char str1[100] = "";
  char str2[100] = "";

  int s21_num = -1;
  int orig_num = -1;

  int s21 = s21_sprintf(str1, format, &s21_num);
  int orig = sprintf(str2, format, &orig_num);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(s21_num, orig_num);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "Hel\t\tlo%n \0world!%n";
  char str1[100] = "";
  char str2[100] = "";

  int s21_num_1 = 0;
  int s21_num_2 = 0;

  int orig_num_1 = 0;
  int orig_num_2 = 0;

  int s21 = s21_sprintf(str1, format, &s21_num_1, &s21_num_2);
  int orig = sprintf(str2, format, &orig_num_1, &orig_num_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(s21_num_1, orig_num_1);
  ck_assert_int_eq(s21_num_2, orig_num_2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "Hel%%dbfkdshbfhskdlo%ln worlsaddad!%hnsadasd";
  char str1[100] = "";
  char str2[100] = "";

  long int s21_num_1 = 0;
  short int s21_num_2 = 0;

  long int orig_num_1 = 0;
  short int orig_num_2 = 0;

  int s21 = s21_sprintf(str1, format, &s21_num_1, &s21_num_2);
  int orig = sprintf(str2, format, &orig_num_1, &orig_num_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(s21_num_1, orig_num_1);
  ck_assert_int_eq(s21_num_2, orig_num_2);
}
END_TEST

Suite* test_s21_sprintf_n() {
  Suite* s = suite_create("\033[1;34m S21_SPRINTF_N \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sprintf_n \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);

  suite_add_tcase(s, tc);
  return s;
}