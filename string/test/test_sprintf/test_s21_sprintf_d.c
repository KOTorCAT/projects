#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%d";
  char str1[100] = "";
  char str2[100] = "";

  int num = 21;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%d";
  char str1[100] = "";
  char str2[100] = "";

  int num = -21;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%d";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = -0;
  int num_2 = -0;

  int s21 = s21_sprintf(str1, format, num_1, num_2);
  int orig = sprintf(str2, format, num_1, num_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%d";
  char str1[100] = "";
  char str2[100] = "";

  int num = +0;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%d%d%d%d%d";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = +0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = +21;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "|% d|  |% d|  |% d|% d|    |% d|";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = '\\';
  int num_2 = '\t';
  int num_3 = '\n';
  int num_4 = '\0';
  int num_5 = '%%%%';

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%010d%%%-5.5d%d%d% d";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = +0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = 21;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%+ 10.1d|%-10.3d|%%\n\t|%+3.2d|%-*d%05d";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = +21;

  int weight = 15;

  int s21 =
      s21_sprintf(str1, format, num_1, num_2, num_3, weight, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, weight, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "% .*d|% -10.3d|%%\n\t|% 3.2d|%-*d%05d";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = +21;

  int weight = 15;
  int tochnost = 5;

  int s21 = s21_sprintf(str1, format, tochnost, num_1, num_2, num_3, weight,
                        num_4, num_5);
  int orig = sprintf(str2, format, tochnost, num_1, num_2, num_3, weight, num_4,
                     num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "\n|% ld|\n| %hd|\n| %hd|\n|% hd|\n";
  char str1[100] = "";
  char str2[100] = "";

  long int num_1 = LONG_MIN;
  short int num_2 = SHRT_MAX;
  short int num_3 = SHRT_MIN;
  long int num_4 = LONG_MAX;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_11) {
  char format[100] = "\n%.*ld|%-10.3hd|%%\n\t|% 3.2hd|%-*d%05ld";
  char str1[100] = "";
  char str2[100] = "";

  long int num_1 = LONG_MIN;
  short int num_2 = SHRT_MAX;
  short int num_3 = SHRT_MIN;
  short int num_4 = -0;
  long int num_5 = LONG_MAX;

  int weight = 10;
  int tochnost = 5;

  int s21 = s21_sprintf(str1, format, tochnost, num_1, num_2, num_3, weight,
                        num_4, num_5);
  int orig = sprintf(str2, format, tochnost, num_1, num_2, num_3, weight, num_4,
                     num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_12) {
  char format[100] = "%+-10.1d|%+-10.3d|%%\n\t|%+-3.2d|%+-*d %05d";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = +21;

  int weight = 10;

  int s21 =
      s21_sprintf(str1, format, num_1, num_2, num_3, weight, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, weight, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_13) {
  char format[100] = "%+-10.*d|%+-10.*d|%%\n\t|%+-3.2d|%+-*d%05d";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = +21;

  int weight = 10;
  int tochnost = 5;

  int s21 = s21_sprintf(str1, format, tochnost, num_1, tochnost, num_2, num_3,
                        weight, num_4, num_5);
  int orig = sprintf(str2, format, tochnost, num_1, tochnost, num_2, num_3,
                     weight, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* test_s21_sprintf_d() {
  Suite* s = suite_create("\033[1;34m S21_SPRINTF_D \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sprintf_d \033[0m");

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
  tcase_add_test(tc, test_13);

  suite_add_tcase(s, tc);
  return s;
}