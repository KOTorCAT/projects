#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%u";
  char str1[100] = "";
  char str2[100] = "";

  size_t num = 21;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%u";
  char str1[100] = "";
  char str2[100] = "";

  size_t num = -21;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%u";
  char str1[100] = "";
  char str2[100] = "";

  size_t num = -0;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%u";
  char str1[100] = "";
  char str2[100] = "";

  size_t num = +0;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%u%u%u%u%u";
  char str1[100] = "";
  char str2[100] = "";

  size_t num_1 = +0;
  size_t num_2 = -0;
  size_t num_3 = 21;
  size_t num_4 = -21;
  size_t num_5 = +21;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%u  %u  %u%u    %u";
  char str1[100] = "";
  char str2[100] = "";

  size_t num_1 = '\\';
  size_t num_2 = '\t';
  size_t num_3 = '\n';
  size_t num_4 = '\0';
  size_t num_5 = '%%%%';

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "\n%-u\n%4u\n%-4u\n%1u\n%.1u";
  char str1[100] = "";
  char str2[100] = "";

  size_t num_1 = +0;
  size_t num_2 = -0;
  size_t num_3 = 21;
  size_t num_4 = -21;
  size_t num_5 = +21;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%-*.*u%*u%-.*u%1u%.1u";
  char str1[100] = "";
  char str2[100] = "";

  size_t num_1 = +0;
  size_t num_2 = -0;
  size_t num_3 = 21;
  size_t num_4 = -21;
  size_t num_5 = +21;

  int weight = 3;
  int tochnost = 3;

  int s21 = s21_sprintf(str1, format, weight, tochnost, num_1, weight, num_2,
                        tochnost, num_3, num_4, num_5);
  int orig = sprintf(str2, format, weight, tochnost, num_1, weight, num_2,
                     tochnost, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "%-*.*hu%*hu%-.*hu%1hu%.1hu";
  char str1[100] = "";
  char str2[100] = "";

  unsigned short num_1 = +0;
  unsigned short num_2 = -0;
  unsigned short num_3 = 21;
  unsigned short num_4 = -21;
  unsigned short num_5 = +21;

  int weight = 3;
  int tochnost = 3;

  int s21 = s21_sprintf(str1, format, weight, tochnost, num_1, weight, num_2,
                        tochnost, num_3, num_4, num_5);
  int orig = sprintf(str2, format, weight, tochnost, num_1, weight, num_2,
                     tochnost, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "%-*.*lu%*lu%-.*lu%1lu%.1lu";
  char str1[100] = "";
  char str2[100] = "";

  size_t num_1 = +0;
  size_t num_2 = -0;
  size_t num_3 = 21;
  size_t num_4 = -21;
  size_t num_5 = +21;

  int weight = 3;
  int tochnost = 3;

  int s21 = s21_sprintf(str1, format, weight, tochnost, num_1, weight, num_2,
                        tochnost, num_3, num_4, num_5);
  int orig = sprintf(str2, format, weight, tochnost, num_1, weight, num_2,
                     tochnost, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_11) {
  char format[100] = "%-*.*lu%*hu%-.*lu%1hu%.1lu";
  char str1[100] = "";
  char str2[100] = "";

  size_t num_1 = +0;
  unsigned short num_2 = -0;
  size_t num_3 = 21;
  unsigned short num_4 = -21;
  size_t num_5 = +21;

  int weight = 3;
  int tochnost = 3;

  int s21 = s21_sprintf(str1, format, weight, tochnost, num_1, weight, num_2,
                        tochnost, num_3, num_4, num_5);
  int orig = sprintf(str2, format, weight, tochnost, num_1, weight, num_2,
                     tochnost, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* test_s21_sprintf_u() {
  Suite* s = suite_create("\033[1;34m S21_SPRINTF_U \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sprintf_u \033[0m");

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

  suite_add_tcase(s, tc);
  return s;
}