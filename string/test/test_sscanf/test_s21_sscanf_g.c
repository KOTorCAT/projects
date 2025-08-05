#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%g";
  char str[100] = "1213123.121123";

  double f_s21 = 0, f_orig = 0;

  int s21 = s21_sscanf(str, format, &f_s21);
  int orig = sscanf(str, format, &f_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21, f_orig, 0.00001);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%G";
  char str[100] = "-1123.145345";

  double d_s21 = 0, d_orig = 0;

  int s21 = s21_sscanf(str, format, &d_s21);
  int orig = sscanf(str, format, &d_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21, d_orig, 0.00001);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%g   %G";
  char str[100] = "21.001213123 -1312.11241212";

  double d_s21_1 = 0, d_s21_2 = 0;
  double d_orig_1 = 0, d_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &d_s21_1, &d_s21_2);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_double_eq_tol(d_s21_2, d_orig_2, 0.00001);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%g   %G";
  char str[100] = "";

  double d_s21_1 = 0, d_s21_2 = 0;
  double d_orig_1 = 0, d_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &d_s21_1, &d_s21_2);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_double_eq_tol(d_s21_2, d_orig_2, 0.00001);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%G %G";
  char str[100] = "-000.0001 4.002131e-3";

  double d_s21_1 = 0, d_s21_2 = 0;
  double d_orig_1 = 0, d_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &d_s21_1, &d_s21_2);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_double_eq_tol(d_s21_2, d_orig_2, 0.00001);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%g %g";
  char str[100] = "-100.0021312301 2.131e-6";

  double d_s21_1 = 0, d_s21_2 = 0;
  double d_orig_1 = 0, d_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &d_s21_1, &d_s21_2);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_double_eq_tol(d_s21_2, d_orig_2, 0.00001);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%G%g%g%G%g";
  char str[100] = "1.213211213124e+5 c \t \\ \0 ";

  double d_s21_1 = 0, d_s21_2 = 0, d_s21_3 = 0, d_s21_4 = 0, d_s21_5 = 0;
  double d_orig_1 = 0, d_orig_2 = 0, d_orig_3 = 0, d_orig_4 = 0, d_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &d_s21_1, &d_s21_2, &d_s21_3, &d_s21_4, &d_s21_5);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2, &d_orig_3, &d_orig_4,
                    &d_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_double_eq_tol(d_s21_2, d_orig_2, 0.00001);
  ck_assert_double_eq_tol(d_s21_3, d_orig_3, 0.00001);
  ck_assert_double_eq_tol(d_s21_4, d_orig_4, 0.00001);
  ck_assert_double_eq_tol(d_s21_5, d_orig_5, 0.00001);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%g%G%g%g%G";
  char str[100] = "1.213211213124e+5c\t\\\0 ";

  double d_s21_1 = 0, d_s21_2 = 0, d_s21_3 = 0, d_s21_4 = 0, d_s21_5 = 0;
  double d_orig_1 = 0, d_orig_2 = 0, d_orig_3 = 0, d_orig_4 = 0, d_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &d_s21_1, &d_s21_2, &d_s21_3, &d_s21_4, &d_s21_5);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2, &d_orig_3, &d_orig_4,
                    &d_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_double_eq_tol(d_s21_2, d_orig_2, 0.00001);
  ck_assert_double_eq_tol(d_s21_3, d_orig_3, 0.00001);
  ck_assert_double_eq_tol(d_s21_4, d_orig_4, 0.00001);
  ck_assert_double_eq_tol(d_s21_5, d_orig_5, 0.00001);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "%*g%5G %10G %2g%3g";
  char str[100] =
      "2.1312231231e+4 -213.000000 +2.3112e-1 0.2131231231 000000.000000";

  double d_s21_1 = 0, d_s21_2 = 0, d_s21_3 = 0, d_s21_4 = 0, d_s21_5 = 0;
  double d_orig_1 = 0, d_orig_2 = 0, d_orig_3 = 0, d_orig_4 = 0, d_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &d_s21_1, &d_s21_2, &d_s21_3, &d_s21_4, &d_s21_5);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2, &d_orig_3, &d_orig_4,
                    &d_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_double_eq_tol(d_s21_2, d_orig_2, 0.00001);
  ck_assert_double_eq_tol(d_s21_3, d_orig_3, 0.00001);
  ck_assert_double_eq_tol(d_s21_4, d_orig_4, 0.00001);
  ck_assert_double_eq_tol(d_s21_5, d_orig_5, 0.00001);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "%*g%*G %*G %*g%3G";
  char str[100] =
      "2.1312231231e+4 -213.000000 +2.3112e-1 0.2131231231 000000.000000";

  double d_s21_1 = 0, d_s21_2 = 0, d_s21_3 = 0, d_s21_4 = 0, d_s21_5 = 0;
  double d_orig_1 = 0, d_orig_2 = 0, d_orig_3 = 0, d_orig_4 = 0, d_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &d_s21_1, &d_s21_2, &d_s21_3, &d_s21_4, &d_s21_5);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2, &d_orig_3, &d_orig_4,
                    &d_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_double_eq_tol(d_s21_2, d_orig_2, 0.00001);
  ck_assert_double_eq_tol(d_s21_3, d_orig_3, 0.00001);
  ck_assert_double_eq_tol(d_s21_4, d_orig_4, 0.00001);
  ck_assert_double_eq_tol(d_s21_5, d_orig_5, 0.00001);
}
END_TEST

START_TEST(test_11) {
  char format[100] = "%lG%5lg %10lg %2lg%3lG";
  char str[100] =
      "2.1312231231e+4 -213.000000 +2.3112e-1 0.2131231231 000000.000000";

  double d_s21_1 = 0, d_s21_2 = 0, d_s21_3 = 0, d_s21_4 = 0, d_s21_5 = 0;
  double d_orig_1 = 0, d_orig_2 = 0, d_orig_3 = 0, d_orig_4 = 0, d_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &d_s21_1, &d_s21_2, &d_s21_3, &d_s21_4, &d_s21_5);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2, &d_orig_3, &d_orig_4,
                    &d_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_double_eq_tol(d_s21_2, d_orig_2, 0.00001);
  ck_assert_double_eq_tol(d_s21_3, d_orig_3, 0.00001);
  ck_assert_double_eq_tol(d_s21_4, d_orig_4, 0.00001);
  ck_assert_double_eq_tol(d_s21_5, d_orig_5, 0.00001);
}
END_TEST

START_TEST(test_12) {
  char format[100] = "%*LG%5Lg %10Lg %2LG%3LG";
  char str[100] =
      "2.1312231231e+4 -213.000000 +2.3112e-1 0.2131233241231 000000.000000";

  long double d_s21_1 = 0, d_s21_2 = 0, d_s21_3 = 0, d_s21_4 = 0, d_s21_5 = 0;
  long double d_orig_1 = 0, d_orig_2 = 0, d_orig_3 = 0, d_orig_4 = 0,
              d_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &d_s21_1, &d_s21_2, &d_s21_3, &d_s21_4, &d_s21_5);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2, &d_orig_3, &d_orig_4,
                    &d_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_double_eq_tol(d_s21_2, d_orig_2, 0.00001);
  ck_assert_double_eq_tol(d_s21_3, d_orig_3, 0.00001);
  ck_assert_double_eq_tol(d_s21_4, d_orig_4, 0.00001);
  ck_assert_double_eq_tol(d_s21_5, d_orig_5, 0.00001);
}
END_TEST

START_TEST(test_13) {
  char format[100] = "%*lg%5LG %10lg %2Lg%3lg";
  char str[100] =
      "2.1312231231e+4 -213.000000 +2.3112e-1 0.21312356751231 000000.000000";

  double d_s21_1 = 0;
  long double d_s21_2 = 0;
  double d_s21_3 = 0;
  long double d_s21_4 = 0;
  double d_s21_5 = 0;

  double d_orig_1 = 0;
  long double d_orig_2 = 0;
  double d_orig_3 = 0;
  long double d_orig_4 = 0;
  double d_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &d_s21_1, &d_s21_2, &d_s21_3, &d_s21_4, &d_s21_5);
  int orig = sscanf(str, format, &d_orig_1, &d_orig_2, &d_orig_3, &d_orig_4,
                    &d_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_double_eq_tol(d_s21_1, d_orig_1, 0.00001);
  ck_assert_ldouble_eq_tol(d_s21_2, d_orig_2, 0.00001);
  ck_assert_double_eq_tol(d_s21_3, d_orig_3, 0.00001);
  ck_assert_ldouble_eq_tol(d_s21_4, d_orig_4, 0.00001);
  ck_assert_double_eq_tol(d_s21_5, d_orig_5, 0.00001);
}
END_TEST

Suite* test_s21_sscanf_g() {
  Suite* s = suite_create("\033[32m S21_SSCANF_G \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sscanf_g \033[0m");

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