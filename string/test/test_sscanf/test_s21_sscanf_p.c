#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%p";
  char str[100] = "0x7ffc3b2a4b90 ";

  long int int_s21 = 0, int_orig = 0;

  int s21 = s21_sscanf(str, format, &int_s21);
  int orig = sscanf(str, format, &int_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_ptr_eq(int_s21, int_orig);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%p%p";
  char str[100] = "0x7ffc3b2a4b90  0x7ffc3b2a4c00";

  long int int_s21_1 = 0, int_s21_2 = 0;
  long int int_orig_1 = 0, int_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_ptr_eq(int_s21_1, int_orig_1);
  ck_assert_ptr_eq(int_s21_2, int_orig_2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%p%p";
  char str[100] = "0x7ffc3b2a4c00";

  long int int_s21_1 = 0, int_s21_2 = 0;
  long int int_orig_1 = 0, int_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_ptr_eq(int_s21_1, int_orig_1);
  ck_assert_ptr_eq(int_s21_2, int_orig_2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%p";
  char str[100] = "";

  long int int_s21 = 0, int_orig = 0;

  int s21 = s21_sscanf(str, format, &int_s21);
  int orig = sscanf(str, format, &int_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_ptr_eq(int_s21, int_orig);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%p";
  char str[100] = "\0";

  void *int_s21 = 0, *int_orig = 0;

  int s21 = s21_sscanf(str, format, &int_s21);
  int orig = sscanf(str, format, &int_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_ptr_eq(int_s21, int_orig);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%p %p %p %p %p";
  char str[100] =
      "0x1aac3b2a4c00 0x452c3b2a4c10 0xabc13b2a4c00 0x7ffc3b211100 "
      "0x11111b2a4c00";

  void *int_s21_1 = 0, *int_s21_2 = 0, *int_s21_3 = 0, *int_s21_4 = 0,
       *int_s21_5 = 0;
  void *int_orig_1 = 0, *int_orig_2 = 0, *int_orig_3 = 0, *int_orig_4 = 0,
       *int_orig_5 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2, &int_s21_3,
                       &int_s21_4, &int_s21_5);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2, &int_orig_3,
                    &int_orig_4, &int_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_ptr_eq(int_s21_1, int_orig_1);
  ck_assert_ptr_eq(int_s21_2, int_orig_2);
  ck_assert_ptr_eq(int_s21_3, int_orig_3);
  ck_assert_ptr_eq(int_s21_4, int_orig_4);
  ck_assert_ptr_eq(int_s21_5, int_orig_5);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%100p%*p%*p%25p%p%p";
  char str[100] =
      "0x1aac3b2a4c00 0x452c3b2a4c10 0xabc13b2a4c00 0x7ffc3b211100 "
      "0x11111b2a4c00";

  void *int_s21_1 = 0, *int_s21_2 = 0, *int_s21_3 = 0, *int_s21_4 = 0,
       *int_s21_5 = 0, *int_s21_6 = 0;
  void *int_orig_1 = 0, *int_orig_2 = 0, *int_orig_3 = 0, *int_orig_4 = 0,
       *int_orig_5 = 0, *int_orig_6 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2, &int_s21_3,
                       &int_s21_4, &int_s21_5, &int_s21_6);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2, &int_orig_3,
                    &int_orig_4, &int_orig_5, &int_orig_6);

  ck_assert_int_eq(s21, orig);
  ck_assert_ptr_eq(int_s21_1, int_orig_1);
  ck_assert_ptr_eq(int_s21_2, int_orig_2);
  ck_assert_ptr_eq(int_s21_3, int_orig_3);
  ck_assert_ptr_eq(int_s21_4, int_orig_4);
  ck_assert_ptr_eq(int_s21_5, int_orig_5);
  ck_assert_ptr_eq(int_s21_6, int_orig_6);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%*p%*p%10p%2p%21p%25p";
  char str[100] =
      "0x1aac3b2a4c00 0x452c3b2a4c10 0xabc13b2a4c00 0x7ffc3b211100 "
      "0x11111b2a4c00";

  void *int_s21_1 = 0, *int_s21_2 = 0, *int_s21_3 = 0, *int_s21_4 = 0,
       *int_s21_5 = 0, *int_s21_6 = 0;
  void *int_orig_1 = 0, *int_orig_2 = 0, *int_orig_3 = 0, *int_orig_4 = 0,
       *int_orig_5 = 0, *int_orig_6 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2, &int_s21_3,
                       &int_s21_4, &int_s21_5, &int_s21_6);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2, &int_orig_3,
                    &int_orig_4, &int_orig_5, &int_orig_6);

  ck_assert_int_eq(s21, orig);
  ck_assert_ptr_eq(int_s21_1, int_orig_1);
  ck_assert_ptr_eq(int_s21_2, int_orig_2);
  ck_assert_ptr_eq(int_s21_3, int_orig_3);
  ck_assert_ptr_eq(int_s21_4, int_orig_4);
  ck_assert_ptr_eq(int_s21_5, int_orig_5);
  ck_assert_ptr_eq(int_s21_6, int_orig_6);
}
END_TEST

Suite *test_s21_sscanf_p() {
  Suite *s = suite_create("\033[32m S21_SSCANF_P \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_sscanf_p \033[0m");

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