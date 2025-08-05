#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%u";
  char str[100] = "1";

  size_t int_s21 = 0, int_orig = 0;

  int s21 = s21_sscanf(str, format, &int_s21);
  int orig = sscanf(str, format, &int_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21, int_orig);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%u%u";
  char str[100] = "21 21";

  size_t int_s21_1 = 0, int_s21_2 = 0;
  size_t int_orig_1 = 0, int_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21_1, int_orig_1);
  ck_assert_uint_eq(int_s21_2, int_orig_2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%u%u";
  char str[100] = "21";

  size_t int_s21_1 = 0, int_s21_2 = 0;
  size_t int_orig_1 = 0, int_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21_1, int_orig_1);
  ck_assert_uint_eq(int_s21_2, int_orig_2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%u%u";
  char str[100] = "h \th";

  size_t int_s21_1 = 0, int_s21_2 = 0;
  size_t int_orig_1 = 0, int_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21_1, int_orig_1);
  ck_assert_uint_eq(int_s21_2, int_orig_2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%u";
  char str[100] = "";

  size_t int_s21 = 0, int_orig = 0;

  int s21 = s21_sscanf(str, format, &int_s21);
  int orig = sscanf(str, format, &int_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21, int_orig);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%u%u%u%u%u";
  char str[100] = "21 \t \\ \0 ";

  size_t int_s21_1 = 0, int_s21_2 = 0, int_s21_3 = 0, int_s21_4 = 0,
         int_s21_5 = 0;
  size_t int_orig_1 = 0, int_orig_2 = 0, int_orig_3 = 0, int_orig_4 = 0,
         int_orig_5 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2, &int_s21_3,
                       &int_s21_4, &int_s21_5);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2, &int_orig_3,
                    &int_orig_4, &int_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21_1, int_orig_1);
  ck_assert_uint_eq(int_s21_2, int_orig_2);
  ck_assert_uint_eq(int_s21_3, int_orig_3);
  ck_assert_uint_eq(int_s21_4, int_orig_4);
  ck_assert_uint_eq(int_s21_5, int_orig_5);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%u";
  char str[100] = "\0";

  size_t int_s21 = 0, int_orig = 0;

  int s21 = s21_sscanf(str, format, &int_s21);
  int orig = sscanf(str, format, &int_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21, int_orig);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%u";
  char str[100] = "-10";

  size_t int_s21 = 0, int_orig = 0;

  int s21 = s21_sscanf(str, format, &int_s21);
  int orig = sscanf(str, format, &int_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21, int_orig);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "%u %u %u %u %u";
  char str[100] = "-1 0 11 -2002321 1";

  size_t int_s21_1 = 0, int_s21_2 = 0, int_s21_3 = 0, int_s21_4 = 0,
         int_s21_5 = 0;
  size_t int_orig_1 = 0, int_orig_2 = 0, int_orig_3 = 0, int_orig_4 = 0,
         int_orig_5 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2, &int_s21_3,
                       &int_s21_4, &int_s21_5);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2, &int_orig_3,
                    &int_orig_4, &int_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21_1, int_orig_1);
  ck_assert_uint_eq(int_s21_2, int_orig_2);
  ck_assert_uint_eq(int_s21_3, int_orig_3);
  ck_assert_uint_eq(int_s21_4, int_orig_4);
  ck_assert_uint_eq(int_s21_5, int_orig_5);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "%u";
  char str[100] = "+10";

  size_t int_s21 = 0, int_orig = 0;

  int s21 = s21_sscanf(str, format, &int_s21);
  int orig = sscanf(str, format, &int_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21, int_orig);
}
END_TEST

START_TEST(test_11) {
  char format[100] = "%u%u%u%u%u%u";
  char str[100] = "+21 -1 0 +0 -0  -21";

  size_t int_s21_1 = 0, int_s21_2 = 0, int_s21_3 = 0, int_s21_4 = 0,
         int_s21_5 = 0, int_s21_6 = 0;
  size_t int_orig_1 = 0, int_orig_2 = 0, int_orig_3 = 0, int_orig_4 = 0,
         int_orig_5 = 0, int_orig_6 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2, &int_s21_3,
                       &int_s21_4, &int_s21_5, &int_s21_6);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2, &int_orig_3,
                    &int_orig_4, &int_orig_5, &int_orig_6);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21_1, int_orig_1);
  ck_assert_uint_eq(int_s21_2, int_orig_2);
  ck_assert_uint_eq(int_s21_3, int_orig_3);
  ck_assert_uint_eq(int_s21_4, int_orig_4);
  ck_assert_uint_eq(int_s21_5, int_orig_5);
  ck_assert_uint_eq(int_s21_6, int_orig_6);
}
END_TEST

START_TEST(test_12) {
  char format[100] = "%u%u%u%u%u";
  char str[100] = "21\t\\\0 1";

  size_t int_s21_1 = 0, int_s21_2 = 0, int_s21_3 = 0, int_s21_4 = 0,
         int_s21_5 = 0;
  size_t int_orig_1 = 0, int_orig_2 = 0, int_orig_3 = 0, int_orig_4 = 0,
         int_orig_5 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2, &int_s21_3,
                       &int_s21_4, &int_s21_5);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2, &int_orig_3,
                    &int_orig_4, &int_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21_1, int_orig_1);
  ck_assert_uint_eq(int_s21_2, int_orig_2);
  ck_assert_uint_eq(int_s21_3, int_orig_3);
  ck_assert_uint_eq(int_s21_4, int_orig_4);
  ck_assert_uint_eq(int_s21_5, int_orig_5);
}
END_TEST

START_TEST(test_13) {
  char format[100] = "%4u%10u%3u%1u%2u%4u";
  char str[100] = "+2143234 123423 000 +000 -00  -213244";

  size_t int_s21_1 = 0, int_s21_2 = 0, int_s21_3 = 0, int_s21_4 = 0,
         int_s21_5 = 0, int_s21_6 = 0;
  size_t int_orig_1 = 0, int_orig_2 = 0, int_orig_3 = 0, int_orig_4 = 0,
         int_orig_5 = 0, int_orig_6 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2, &int_s21_3,
                       &int_s21_4, &int_s21_5, &int_s21_6);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2, &int_orig_3,
                    &int_orig_4, &int_orig_5, &int_orig_6);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21_1, int_orig_1);
  ck_assert_uint_eq(int_s21_2, int_orig_2);
  ck_assert_uint_eq(int_s21_3, int_orig_3);
  ck_assert_uint_eq(int_s21_4, int_orig_4);
  ck_assert_uint_eq(int_s21_5, int_orig_5);
  ck_assert_uint_eq(int_s21_6, int_orig_6);
}
END_TEST

START_TEST(test_14) {
  char format[100] = "%4hu%10lu%3hu%1lu%2hu%4lu";
  char str[100] = "+2143234 123423 000 +000 -00  -213244";

  unsigned short int_s21_1 = 0;
  unsigned long int_s21_2 = 0;
  unsigned short int_s21_3 = 0;
  unsigned long int_s21_4 = 0;
  unsigned short int_s21_5 = 0;
  unsigned long int_s21_6 = 0;

  unsigned short int_orig_1 = 0;
  unsigned long int_orig_2 = 0;
  unsigned short int_orig_3 = 0;
  unsigned long int_orig_4 = 0;
  unsigned short int_orig_5 = 0;
  unsigned long int_orig_6 = 0;

  int s21 = s21_sscanf(str, format, &int_s21_1, &int_s21_2, &int_s21_3,
                       &int_s21_4, &int_s21_5, &int_s21_6);
  int orig = sscanf(str, format, &int_orig_1, &int_orig_2, &int_orig_3,
                    &int_orig_4, &int_orig_5, &int_orig_6);

  ck_assert_int_eq(s21, orig);
  ck_assert_uint_eq(int_s21_1, int_orig_1);
  ck_assert_uint_eq(int_s21_2, int_orig_2);
  ck_assert_uint_eq(int_s21_3, int_orig_3);
  ck_assert_uint_eq(int_s21_4, int_orig_4);
  ck_assert_uint_eq(int_s21_5, int_orig_5);
  ck_assert_uint_eq(int_s21_6, int_orig_6);
}
END_TEST

Suite* test_s21_sscanf_u() {
  Suite* s = suite_create("\033[32m S21_SSCANF_U \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sscanf_u \033[0m");

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