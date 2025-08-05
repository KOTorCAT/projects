#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%d%n";
  char str[100] = "1";

  int int_s21 = 0, int_orig = 0;

  int s21_count = -1;
  int orig_count = -1;

  int s21 = s21_sscanf(str, format, &int_s21, &s21_count);
  int orig = sscanf(str, format, &int_orig, &orig_count);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(int_s21, int_orig);
  ck_assert_int_eq(s21_count, orig_count);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%d%d%n";
  char str[100] = "21 21";

  int int_s21_1 = 0, int_s21_2 = 0;
  int int_orig_1 = 0, int_orig_2 = 0;

  int s21_count = -1;
  int orig_count = -1;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2, &s21_count);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2, &orig_count);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(int_s21_1, int_orig_1);
  ck_assert_int_eq(int_s21_2, int_orig_2);
  ck_assert_int_eq(s21_count, orig_count);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%d%n%d";
  char str[100] = "21213  213213";

  int int_s21_1 = 0, int_s21_2 = 0;
  int int_orig_1 = 0, int_orig_2 = 0;

  int s21_count = -1;
  int orig_count = -1;

  int s21 = s21_sscanf(str, format, &int_s21_1, &s21_count, &int_s21_2);
  int orig = sscanf(str, format, &int_orig_1, &orig_count, &int_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_int_eq(int_s21_1, int_orig_1);
  ck_assert_int_eq(int_s21_2, int_orig_2);
  ck_assert_int_eq(s21_count, orig_count);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%s %s %n %d %n %c";
  char str[100] = "sadasd \t\t\t 213123 sda ";

  char s21_str_1[20] = "";
  char s21_str_2[20] = "";
  int s21_int = 0;
  char s21_ch = 0;

  char orig_str_1[20] = "";
  char orig_str_2[20] = "";
  int orig_int = 0;
  char orig_ch = 0;

  int s21_count_1 = -1;
  int s21_count_2 = -1;
  int orig_count_1 = -1;
  int orig_count_2 = -1;

  int s21 = s21_sscanf(str, format, &s21_str_1, &s21_str_2, &s21_count_1,
                       &s21_int, &s21_count_2, &s21_ch);
  int orig = sscanf(str, format, &orig_str_1, &orig_str_2, &orig_count_1,
                    &orig_int, &orig_count_2, &orig_ch);

  ck_assert_int_eq(s21, orig);

  ck_assert_str_eq(s21_str_1, orig_str_1);
  ck_assert_str_eq(s21_str_2, orig_str_2);
  ck_assert_int_eq(s21_int, orig_int);
  ck_assert_int_eq(s21_ch, orig_ch);

  ck_assert_int_eq(s21_count_1, orig_count_1);
  ck_assert_int_eq(s21_count_2, orig_count_2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%s %s %n %d %n %c%n";
  char str[100] = "sadasd \t\t\t 213123 sda ";

  char s21_str_1[20] = "";
  char s21_str_2[20] = "";
  int s21_int = 0;
  char s21_ch = 0;

  char orig_str_1[20] = "";
  char orig_str_2[20] = "";
  int orig_int = 0;
  char orig_ch = 0;

  int s21_count_1 = -1;
  int s21_count_2 = -1;
  int s21_count_3 = -1;
  int orig_count_1 = -1;
  int orig_count_2 = -1;
  int orig_count_3 = -1;

  int s21 = s21_sscanf(str, format, &s21_str_1, &s21_str_2, &s21_count_1,
                       &s21_int, &s21_count_2, &s21_ch, &s21_count_3);
  int orig = sscanf(str, format, &orig_str_1, &orig_str_2, &orig_count_1,
                    &orig_int, &orig_count_2, &orig_ch, &orig_count_3);

  ck_assert_int_eq(s21, orig);

  ck_assert_str_eq(s21_str_1, orig_str_1);
  ck_assert_str_eq(s21_str_2, orig_str_2);
  ck_assert_int_eq(s21_int, orig_int);
  ck_assert_int_eq(s21_ch, orig_ch);

  ck_assert_int_eq(s21_count_1, orig_count_1);
  ck_assert_int_eq(s21_count_2, orig_count_2);
  ck_assert_int_eq(s21_count_3, orig_count_3);
}
END_TEST

Suite* test_s21_sscanf_n() {
  Suite* s = suite_create("\033[32m S21_SSCANF_N \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sscanf_n \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);

  suite_add_tcase(s, tc);
  return s;
}