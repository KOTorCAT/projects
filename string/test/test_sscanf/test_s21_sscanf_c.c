#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%c";
  char str[100] = "h";

  char ch_s21 = 0, ch_orig = 0;

  int s21 = s21_sscanf(str, format, &ch_s21);
  int orig = sscanf(str, format, &ch_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(ch_s21, ch_orig);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%c%c";
  char str[100] = "hh";

  char ch_s21_1 = 0, ch_s21_2 = 0;
  char ch_orig_1 = 0, ch_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &ch_s21_1, &ch_s21_2);
  int orig = sscanf(str, format, &ch_orig_1, &ch_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(ch_s21_1, ch_orig_1);
  ck_assert_int_eq(ch_s21_2, ch_orig_2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%c%c";
  char str[100] = "h\th";

  char ch_s21_1 = 0, ch_s21_2 = 0;
  char ch_orig_1 = 0, ch_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &ch_s21_1, &ch_s21_2);
  int orig = sscanf(str, format, &ch_orig_1, &ch_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(ch_s21_1, ch_orig_1);
  ck_assert_int_eq(ch_s21_2, ch_orig_2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%c";
  char str[100] = "";

  char ch_s21 = 0, ch_orig = 0;

  int s21 = s21_sscanf(str, format, &ch_s21);
  int orig = sscanf(str, format, &ch_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(ch_s21, ch_orig);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%c%c%c%c%c";
  char str[100] = "c\t\\\0s";

  char ch_s21_1 = 0, ch_s21_2 = 0, ch_s21_3 = 0, ch_s21_4 = 0, ch_s21_5 = 0;
  char ch_orig_1 = 0, ch_orig_2 = 0, ch_orig_3 = 0, ch_orig_4 = 0,
       ch_orig_5 = 0;

  int s21 = s21_sscanf(str, format, &ch_s21_1, &ch_s21_2, &ch_s21_3, &ch_s21_4,
                       &ch_s21_5);
  int orig = sscanf(str, format, &ch_orig_1, &ch_orig_2, &ch_orig_3, &ch_orig_4,
                    &ch_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(ch_s21_1, ch_orig_1);
  ck_assert_int_eq(ch_s21_2, ch_orig_2);
  ck_assert_int_eq(ch_s21_3, ch_orig_3);
  ck_assert_int_eq(ch_s21_4, ch_orig_4);
  ck_assert_int_eq(ch_s21_5, ch_orig_5);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%c";
  char str[100] = "\0";

  char ch_s21 = 0, ch_orig = 0;

  int s21 = s21_sscanf(str, format, &ch_s21);
  int orig = sscanf(str, format, &ch_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(ch_s21, ch_orig);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%lc";
  const char* str = "Hello";

  wchar_t ch_s21 = 0, ch_orig = 0;

  int s21 = s21_sscanf(str, format, &ch_s21);
  int orig = sscanf(str, format, &ch_orig);

  ck_assert_int_eq(ch_s21, ch_orig);
  ck_assert_int_eq(s21, orig);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%c";
  char str[100] = "%%";

  char ch_s21 = 0, ch_orig = 0;

  int s21 = s21_sscanf(str, format, &ch_s21);
  int orig = sscanf(str, format, &ch_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(ch_s21, ch_orig);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "%c%c";
  char str[100] = "%%%%";

  char ch_s21_1 = 0, ch_s21_2 = 0;
  char ch_orig_1 = 0, ch_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &ch_s21_1, &ch_s21_2);
  int orig = sscanf(str, format, &ch_orig_1, &ch_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(ch_s21_1, ch_orig_1);
  ck_assert_int_eq(ch_s21_2, ch_orig_2);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "%%%c%c";
  char str[100] = "%%%%";

  char ch_s21_1 = 0, ch_s21_2 = 0;
  char ch_orig_1 = 0, ch_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &ch_s21_1, &ch_s21_2);
  int orig = sscanf(str, format, &ch_orig_1, &ch_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(ch_s21_1, ch_orig_1);
  ck_assert_int_eq(ch_s21_2, ch_orig_2);
}
END_TEST

START_TEST(test_11) {
  char format[100] = "%*c%*c%c%   c   %c";
  char str[100] = "c\t\\\0s";

  char ch_s21_1 = 0, ch_s21_2 = 0, ch_s21_3 = 0, ch_s21_4 = 0, ch_s21_5 = 0;
  char ch_orig_1 = 0, ch_orig_2 = 0, ch_orig_3 = 0, ch_orig_4 = 0,
       ch_orig_5 = 0;

  int s21 = s21_sscanf(str, format, &ch_s21_1, &ch_s21_2, &ch_s21_3, &ch_s21_4,
                       &ch_s21_5);
  int orig = sscanf(str, format, &ch_orig_1, &ch_orig_2, &ch_orig_3, &ch_orig_4,
                    &ch_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(ch_s21_1, ch_orig_1);
  ck_assert_int_eq(ch_s21_2, ch_orig_2);
  ck_assert_int_eq(ch_s21_3, ch_orig_3);
  ck_assert_int_eq(ch_s21_4, ch_orig_4);
  ck_assert_int_eq(ch_s21_5, ch_orig_5);
}
END_TEST

START_TEST(test_12) {
  char format[100] = "%3c%4c";
  char str[100] = "Hello school 21!!";

  char ch_s21_1[3] = "", ch_s21_2[4] = "";
  char ch_orig_1[3] = "", ch_orig_2[4] = "";

  ch_s21_1[3] = '\0';
  ch_orig_1[3] = '\0';

  ch_s21_2[4] = '\0';
  ch_orig_2[4] = '\0';

  int s21 = s21_sscanf(str, format, ch_s21_1, ch_s21_2);
  int orig = sscanf(str, format, ch_orig_1, ch_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(ch_s21_1, ch_orig_1);
  ck_assert_str_eq(ch_s21_2, ch_orig_2);
}
END_TEST

START_TEST(test_13) {
  char format[100] = "%*c%10c";
  char str[100] = "Hello school 21!!";

  char ch_s21_1[3] = "", ch_s21_2[10] = "";
  char ch_orig_1[3] = "", ch_orig_2[10] = "";

  ch_s21_1[3] = '\0';
  ch_orig_1[3] = '\0';

  ch_s21_2[10] = '\0';
  ch_orig_2[10] = '\0';

  int s21 = s21_sscanf(str, format, ch_s21_1, ch_s21_2);
  int orig = sscanf(str, format, ch_orig_1, ch_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(ch_s21_1, ch_orig_1);
  ck_assert_str_eq(ch_s21_2, ch_orig_2);
}
END_TEST

Suite* test_s21_sscanf_c() {
  Suite* s = suite_create("\033[32m S21_SSCANF_C \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sscanf_c \033[0m");

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
