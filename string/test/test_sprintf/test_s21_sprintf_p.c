#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%p";
  char str1[100] = "";
  char str2[100] = "";

  int num = 21;

  int s21 = s21_sprintf(str1, format, (void*)&num);
  int orig = sprintf(str2, format, (void*)&num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%p%p%p%p%p";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = +0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = +21;

  int s21 = s21_sprintf(str1, format, (void*)&num_1, (void*)&num_2,
                        (void*)&num_3, (void*)&num_4, (void*)&num_5);
  int orig = sprintf(str2, format, (void*)&num_1, (void*)&num_2, (void*)&num_3,
                     (void*)&num_4, (void*)&num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%-10p%%%-5p%p%p%p";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = +0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = 21;

  int s21 = s21_sprintf(str1, format, (void*)&num_1, (void*)&num_2,
                        (void*)&num_3, (void*)&num_4, (void*)&num_5);
  int orig = sprintf(str2, format, (void*)&num_1, (void*)&num_2, (void*)&num_3,
                     (void*)&num_4, (void*)&num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%p|%10p|%%\n\t|%-01p|%p%p";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = +21;

  int weight = 15;

  int s21 = s21_sprintf(str1, format, (void*)&num_1, (void*)&num_2,
                        (void*)&num_3, weight, (void*)&num_4, (void*)&num_5);
  int orig = sprintf(str2, format, (void*)&num_1, (void*)&num_2, (void*)&num_3,
                     weight, (void*)&num_4, (void*)&num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%.p|%-.p|%%\n\t|%-0.5p|%p%-.p";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = +21;

  int weight = 15;
  int tochnost = 5;

  int s21 = s21_sprintf(str1, format, tochnost, (void*)&num_1, (void*)&num_2,
                        (void*)&num_3, weight, (void*)&num_4, (void*)&num_5);
  int orig = sprintf(str2, format, tochnost, (void*)&num_1, (void*)&num_2,
                     (void*)&num_3, weight, (void*)&num_4, (void*)&num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%*p|%10.*p|%%\n\t|%p|%*p%p";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0;
  int num_2 = -0;
  int num_3 = 21;
  int num_4 = -21;
  int num_5 = +21;

  int weight = 10;
  int tochnost = 5;

  int s21 = s21_sprintf(str1, format, tochnost, (void*)&num_1, tochnost,
                        (void*)&num_2, (void*)&num_3, weight, (void*)&num_4,
                        (void*)&num_5);
  int orig =
      sprintf(str2, format, tochnost, (void*)&num_1, tochnost, (void*)&num_2,
              (void*)&num_3, weight, (void*)&num_4, (void*)&num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* test_s21_sprintf_p() {
  Suite* s = suite_create("\033[1;34m S21_SPRINTF_P \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sprintf_p \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);

  suite_add_tcase(s, tc);
  return s;
}