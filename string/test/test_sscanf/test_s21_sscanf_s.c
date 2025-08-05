#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%s";
  char str[100] = "Hello_school21!";

  char str_s21[100] = "";
  char str_orig[100] = "";

  int s21 = s21_sscanf(str, format, str_s21);
  int orig = sscanf(str, format, str_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%s";
  char str[100] = "";

  char str_s21[100] = "";
  char str_orig[100] = "";

  int s21 = s21_sscanf(str, format, str_s21);
  int orig = sscanf(str, format, str_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%s";
  char str[100] = "\0";

  char str_s21[100] = "";
  char str_orig[100] = "";

  int s21 = s21_sscanf(str, format, str_s21);
  int orig = sscanf(str, format, str_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%s";
  char str[100] = "\t1231df\\%%\0asdasd";

  char str_s21[100] = "";
  char str_orig[100] = "";

  int s21 = s21_sscanf(str, format, str_s21);
  int orig = sscanf(str, format, str_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str_s21, str_orig);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%s%s%s";
  char str[100] = "\t1231df\\%%asdasd 1..001 /213/1aa\0\e";

  char str_s21_1[100] = "";
  char str_s21_2[100] = "";
  char str_s21_3[100] = "";

  char str_orig_1[100] = "";
  char str_orig_2[100] = "";
  char str_orig_3[100] = "";

  int s21 = s21_sscanf(str, format, str_s21_1, str_s21_2, str_s21_3);
  int orig = sscanf(str, format, str_orig_1, str_orig_2, str_orig_3);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str_s21_1, str_orig_1);
  ck_assert_str_eq(str_s21_2, str_orig_2);
  ck_assert_str_eq(str_s21_3, str_orig_3);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%s    %s%s";
  char str[100] = "\t1231df\\%%asdasd 1..001 /213/1aa\0\e";

  char str_s21_1[100] = "";
  char str_s21_2[100] = "";
  char str_s21_3[100] = "";

  char str_orig_1[100] = "";
  char str_orig_2[100] = "";
  char str_orig_3[100] = "";

  int s21 = s21_sscanf(str, format, str_s21_1, str_s21_2, str_s21_3);
  int orig = sscanf(str, format, str_orig_1, str_orig_2, str_orig_3);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str_s21_1, str_orig_1);
  ck_assert_str_eq(str_s21_2, str_orig_2);
  ck_assert_str_eq(str_s21_3, str_orig_3);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%10s    %5s%3s";
  char str[100] = "\t1231df\\%%asdasd 1..001 /213/1aa\0\e";

  char str_s21_1[100] = "";
  char str_s21_2[100] = "";
  char str_s21_3[100] = "";

  char str_orig_1[100] = "";
  char str_orig_2[100] = "";
  char str_orig_3[100] = "";

  int s21 = s21_sscanf(str, format, str_s21_1, str_s21_2, str_s21_3);
  int orig = sscanf(str, format, str_orig_1, str_orig_2, str_orig_3);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str_s21_1, str_orig_1);
  ck_assert_str_eq(str_s21_2, str_orig_2);
  ck_assert_str_eq(str_s21_3, str_orig_3);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%*s    %*s%*s";
  char str[100] = "\t1231df\\%%asdasd 1..001 /213/1aa\0\e";

  char str_s21_1[100] = "";
  char str_s21_2[100] = "";
  char str_s21_3[100] = "";

  char str_orig_1[100] = "";
  char str_orig_2[100] = "";
  char str_orig_3[100] = "";

  int s21 = s21_sscanf(str, format, str_s21_1, str_s21_2, str_s21_3);
  int orig = sscanf(str, format, str_orig_1, str_orig_2, str_orig_3);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str_s21_1, str_orig_1);
  ck_assert_str_eq(str_s21_2, str_orig_2);
  ck_assert_str_eq(str_s21_3, str_orig_3);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "%10s    %*s%3s";
  char str[100] = "\t1231df\\%%asdasd 1..001 /213/1aa\0\e";

  char str_s21_1[100] = "";
  char str_s21_2[100] = "";
  char str_s21_3[100] = "";

  char str_orig_1[100] = "";
  char str_orig_2[100] = "";
  char str_orig_3[100] = "";

  int s21 = s21_sscanf(str, format, str_s21_1, str_s21_2, str_s21_3);
  int orig = sscanf(str, format, str_orig_1, str_orig_2, str_orig_3);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str_s21_1, str_orig_1);
  ck_assert_str_eq(str_s21_2, str_orig_2);
  ck_assert_str_eq(str_s21_3, str_orig_3);
}
END_TEST

Suite* test_s21_sscanf_s() {
  Suite* s = suite_create("\033[32m S21_SSCANF_S \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sscanf_S \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);
  tcase_add_test(tc, test_7);
  tcase_add_test(tc, test_8);
  tcase_add_test(tc, test_9);

  suite_add_tcase(s, tc);
  return s;
}