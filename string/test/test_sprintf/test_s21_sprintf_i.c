#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%i";
  char str1[100] = "";
  char str2[100] = "";

  int num = 0XbF;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%i";
  char str1[100] = "";
  char str2[100] = "";

  int num = -0;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%i";
  char str1[100] = "";
  char str2[100] = "";

  int num = +0;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%i%i%i%i%i";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 10;
  int num_2 = 010;
  int num_3 = 0x1BB44948D8D;
  int num_4 = -0x2123;
  int num_5 = 05421;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "|% i|  |% i|  |% i|% i|    |% i|";
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

START_TEST(test_6) {
  char format[100] = "%+-10.1X|%+-10.3x|%%\n\t|%+-3.2x|%+-*X% 05X";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0x213;
  int num_2 = 0x849;
  int num_3 = 0xC33;
  int num_4 = 218018;
  int num_5 = 0311;

  int weight = 10;

  int s21 =
      s21_sprintf(str1, format, num_1, num_2, num_3, weight, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, weight, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%+-*x|%+-10.*x|%%\n\t|%+-3.2x|%+-*x% 05X";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0x213;
  int num_2 = 0x849;
  int num_3 = 0xC33;
  int num_4 = 218018;
  int num_5 = 0311;

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

START_TEST(test_8) {
  char format[100] = "\n|% li|\n| %hi|\n| %hi|\n|% hi|\n";
  char str1[100] = "";
  char str2[100] = "";

  long int num_1 = 0x213;
  short int num_2 = 0x849;
  short int num_3 = 0xC33;
  long int num_4 = 218018;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* test_s21_sprintf_i() {
  Suite* s = suite_create("\033[1;34m S21_SPRINTF_I \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sprintf_i \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);

  suite_add_tcase(s, tc);
  return s;
}