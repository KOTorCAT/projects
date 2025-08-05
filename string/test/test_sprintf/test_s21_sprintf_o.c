#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%o";
  char str1[100] = "";
  char str2[100] = "";

  int num = 25;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%o";
  char str1[100] = "";
  char str2[100] = "";

  int num = -25;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%o";
  char str1[100] = "";
  char str2[100] = "";

  int num = -0;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%o";
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
  char format[100] = "%o%o%o%o%o";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = +0;
  int num_2 = -0;
  int num_3 = 21213;
  int num_4 = 21321;
  int num_5 = 2521;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "|% o|  |% o|  |% o|% o|    |% o|";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = '364';
  int num_2 = '213';
  int num_3 = '574';
  int num_4 = '11111';
  int num_5 = '%%%%';

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%+010o%%%-5.5o%+o%o% o";
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
  char format[100] = "%+ 10.1o|% -10.3o|%%\n\t|%+   3.2o|%-o% *o";

  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 2111;
  int num_4 = -27451;
  int num_5 = +23121;

  int weight = 15;

  int s21 =
      s21_sprintf(str1, format, num_1, num_2, num_3, num_4, weight, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, weight, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "% *o|% -10.3o|%%\n\t|% 3.2o|%-12o%05o";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 123;
  int num_4 = -534;
  int num_5 = +3634;

  int weight = 15;

  int s21 = s21_sprintf(str1, format, weight, num_1, num_2, num_3, num_4,
                        weight, num_5);
  int orig =
      sprintf(str2, format, weight, num_1, num_2, num_3, num_4, weight, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "\n|% lo|\n| %ho|\n| %ho|\n|% ho|\n";
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
  char format[100] = "\n%*lo|%-10.3ho|%%\n\t|% 3.2ho|%-*d%05lo";
  char str1[100] = "";
  char str2[100] = "";

  long int num_1 = LONG_MIN;
  short int num_2 = SHRT_MAX;
  short int num_3 = SHRT_MIN;
  short int num_4 = -0;
  long int num_5 = LONG_MAX;

  int weight = 10;

  int s21 = s21_sprintf(str1, format, weight, num_1, num_2, num_3, num_4,
                        weight, num_5);
  int orig =
      sprintf(str2, format, weight, num_1, num_2, num_3, num_4, weight, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_12) {
  char format[100] = "%+-10.1o|%+-10.3o|%%\n\t|%+-3.2o|%+-*o % 05o";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 27681;
  int num_4 = -242341;
  int num_5 = +21231;

  int weight = 10;

  int s21 =
      s21_sprintf(str1, format, num_1, num_2, num_3, weight, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, weight, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_13) {
  char format[100] = "%+-*o|%+-10.*o|%%\n\t|%+-3.2o|%+-*d% 05o";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = +21;

  int weight = 10;

  int s21 = s21_sprintf(str1, format, weight, num_1, weight, num_2, num_3,
                        weight, num_4, num_5);
  int orig = sprintf(str2, format, weight, num_1, weight, num_2, num_3, weight,
                     num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* test_s21_sprintf_o() {
  Suite* s = suite_create("\033[1;34m S21_SPRINTF_O \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sprintf_o \033[0m");

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