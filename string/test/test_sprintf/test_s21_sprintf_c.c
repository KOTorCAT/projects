#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%c";
  char str1[100] = "";
  char str2[100] = "";

  char ch = 'a';

  int s21 = s21_sprintf(str1, format, ch);
  int orig = sprintf(str2, format, ch);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%c";
  char str1[100] = "";
  char str2[100] = "";

  char ch = '\0';

  int s21 = s21_sprintf(str1, format, ch);
  int orig = sprintf(str2, format, ch);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%c    %c";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1 = '\\';
  char ch_2 = '\n';

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%c    %c%c %c  ";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1 = '\t';
  char ch_2 = '\\';
  char ch_3 = '%';
  char ch_4 = 'o';
  char ch_5 = '@';

  int s21 = s21_sprintf(str1, format, ch_1, ch_2, ch_3, ch_4, ch_5);
  int orig = sprintf(str2, format, ch_1, ch_2, ch_3, ch_4, ch_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%lc    %lc%lc %lc   %lc";
  char str1[100] = "";
  char str2[100] = "";

  wchar_t ch_1 = 'п';
  wchar_t ch_2 = 'р';
  wchar_t ch_3 = 'и';
  wchar_t ch_4 = 'в';
  wchar_t ch_5 = 'е';
  wchar_t ch_6 = 'т';

  int s21 = s21_sprintf(str1, format, ch_1, ch_2, ch_3, ch_4, ch_5, ch_6);
  int orig = sprintf(str2, format, ch_1, ch_2, ch_3, ch_4, ch_5, ch_6);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%c";
  char str1[100] = "";
  char str2[100] = "";

  char ch = '%';

  int s21 = s21_sprintf(str1, format, ch);
  int orig = sprintf(str2, format, ch);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%c%c";
  char str1[100] = "";
  char str2[100] = "";

  char ch = '%';

  int s21 = s21_sprintf(str1, format, ch);
  int orig = sprintf(str2, format, ch);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%c%c%c%c%c";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1 = '\t';
  char ch_2 = '\\';
  char ch_3 = '%';
  char ch_4 = '\0';
  char ch_5 = '@';

  int s21 = s21_sprintf(str1, format, ch_1, ch_2, ch_3, ch_4, ch_5);
  int orig = sprintf(str2, format, ch_1, ch_2, ch_3, ch_4, ch_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "%c    ";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1 = '%';
  char ch_2 = '\t';

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "%c  %%  ";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1 = '%';
  char ch_2 = '\t';

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_11) {
  char format[100] = "|%%%-10c|%%%-5c|%%";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1 = '%';
  char ch_2 = '1';

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_12) {
  char format[100] = "|%%%010c|%%%05c|%%";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1 = '%';
  char ch_2 = '1';

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_13) {
  char format[100] = "|%%%*c|%%%*c|%%";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1 = '%';
  char ch_2 = '1';

  int weight = 10;

  int s21 = s21_sprintf(str1, format, weight, ch_1, weight, ch_2);
  int orig = sprintf(str2, format, weight, ch_1, weight, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_14) {
  char format[100] = "%10c%-10c%-5c%%%%%05c%%%*c";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1 = '\t';
  char ch_2 = '\\';
  char ch_3 = '%';
  char ch_4 = '\0';
  char ch_5 = '@';

  int weight = 10;

  int s21 = s21_sprintf(str1, format, ch_1, ch_2, ch_3, ch_4, weight, ch_5);
  int orig = sprintf(str2, format, ch_1, ch_2, ch_3, ch_4, weight, ch_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* test_s21_sprintf_c() {
  Suite* s = suite_create("\033[1;34m S21_SPRINTF_C \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sprintf_c \033[0m");

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
  tcase_add_test(tc, test_14);

  suite_add_tcase(s, tc);
  return s;
}