#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%e";
  char str1[100] = "";
  char str2[100] = "";

  double num = 21.00012;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%E";
  char str1[100] = "";
  char str2[100] = "";

  double num = 0.00012;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%e";
  char str1[100] = "";
  char str2[100] = "";

  double num = 0000.00012;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%E";
  char str1[100] = "";
  char str2[100] = "";

  double num = 0000.000145242;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%e";
  char str1[100] = "";
  char str2[100] = "";

  double num = 23123.0003145242;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%e";
  char str1[100] = "";
  char str2[100] = "";

  double num = '\0';

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%E";
  char str1[100] = "";
  char str2[100] = "";

  double num = -2312.002103;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%E%E%e%E";
  char str1[100] = "";
  char str2[100] = "";

  double num_1 = -2312.00103;
  double num_2 = 2312.002103;
  double num_3 = -00000.00103;
  double num_4 = -0.0023103;
  double num_5 = 2.1002103;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "%E %E%E        %e%e";
  char str1[100] = "";
  char str2[100] = "";

  double num_1 = -2312.002103;
  double num_2 = 2312.00103;
  double num_3 = -00000.00203;
  double num_4 = -0.00232103;
  double num_5 = 2.1002103;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "%+-10e%020E%+-.3e%-+3.2e%.6E";
  char str1[100] = "";
  char str2[100] = "";

  double num_1 = -2312.002103;
  double num_2 = 2312.00203;
  double num_3 = -00000.00203;
  double num_4 = -0.00232103;
  double num_5 = 2.1002103;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_11) {
  char format[100] = "%10e%020E%10e%3.2e%.6E";
  char str1[100] = "";
  char str2[100] = "";

  double num_1 = -212.002103;
  double num_2 = 232.00203;
  double num_3 = -00000.00203;
  double num_4 = -0.00232103;
  double num_5 = 2.1002103;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_12) {
  char format[100] = "%+-*.*le%020lE%-+e% -+*.*le%.6le";
  char str1[100] = "";
  char str2[100] = "";

  double num_1 = -2312.00213;
  double num_2 = 2312.00213;
  double num_3 = -00000.0022;
  double num_4 = -0.0023241;
  double num_5 = 2.100213;

  int weight = 5;
  int tochnost = 3;

  int s21 = s21_sprintf(str1, format, weight, tochnost, num_1, num_2, num_3,
                        weight, tochnost, num_4, num_5);
  int orig = sprintf(str2, format, weight, tochnost, num_1, num_2, num_3,
                     weight, tochnost, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* test_s21_sprintf_e() {
  Suite* s = suite_create("\033[1;34m S21_SPRINTF_E \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sprintf_e \033[0m");

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
  tcase_add_test(tc, test_11);
  tcase_add_test(tc, test_12);
  suite_add_tcase(s, tc);
  return s;
}