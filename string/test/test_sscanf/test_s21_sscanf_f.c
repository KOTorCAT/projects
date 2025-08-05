#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%f";
  char str[100] = "1.1";

  float f_s21 = 0, f_orig = 0;

  int s21 = s21_sscanf(str, format, &f_s21);
  int orig = sscanf(str, format, &f_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21, f_orig, 0.00001);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%f";
  char str[100] = "-1.1";

  float f_s21 = 0, f_orig = 0;

  int s21 = s21_sscanf(str, format, &f_s21);
  int orig = sscanf(str, format, &f_orig);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21, f_orig, 0.00001);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%f   %f";
  char str[100] = "21.001 -1.31211241212e+3";

  float f_s21_1 = 0, f_s21_2 = 0;
  float f_orig_1 = 0, f_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &f_s21_1, &f_s21_2);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_float_eq_tol(f_s21_2, f_orig_2, 0.00001);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%f   %f";
  char str[100] = "";

  float f_s21_1 = 0, f_s21_2 = 0;
  float f_orig_1 = 0, f_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &f_s21_1, &f_s21_2);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_float_eq_tol(f_s21_2, f_orig_2, 0.00001);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%f %f";
  char str[100] = "-000.0001 4.002131e-3";

  float f_s21_1 = 0, f_s21_2 = 0;
  float f_orig_1 = 0, f_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &f_s21_1, &f_s21_2);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_float_eq_tol(f_s21_2, f_orig_2, 0.00001);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%f %f";
  char str[100] = "-100.0001 2.131e-6";

  float f_s21_1 = 0, f_s21_2 = 0;
  float f_orig_1 = 0, f_orig_2 = 0;

  int s21 = s21_sscanf(str, format, &f_s21_1, &f_s21_2);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_float_eq_tol(f_s21_2, f_orig_2, 0.00001);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%f%f%f%f%f";
  char str[100] = "1.1 c \t \\ \0 ";

  float f_s21_1 = 0, f_s21_2 = 0, f_s21_3 = 0, f_s21_4 = 0, f_s21_5 = 0;
  float f_orig_1 = 0, f_orig_2 = 0, f_orig_3 = 0, f_orig_4 = 0, f_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &f_s21_1, &f_s21_2, &f_s21_3, &f_s21_4, &f_s21_5);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2, &f_orig_3, &f_orig_4,
                    &f_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_float_eq_tol(f_s21_2, f_orig_2, 0.00001);
  ck_assert_float_eq_tol(f_s21_3, f_orig_3, 0.00001);
  ck_assert_float_eq_tol(f_s21_4, f_orig_4, 0.00001);
  ck_assert_float_eq_tol(f_s21_5, f_orig_5, 0.00001);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%f%f%f%f%f";
  char str[100] = "1.1c\t\\\0 ";

  float f_s21_1 = 0, f_s21_2 = 0, f_s21_3 = 0, f_s21_4 = 0, f_s21_5 = 0;
  float f_orig_1 = 0, f_orig_2 = 0, f_orig_3 = 0, f_orig_4 = 0, f_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &f_s21_1, &f_s21_2, &f_s21_3, &f_s21_4, &f_s21_5);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2, &f_orig_3, &f_orig_4,
                    &f_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_float_eq_tol(f_s21_2, f_orig_2, 0.00001);
  ck_assert_float_eq_tol(f_s21_3, f_orig_3, 0.00001);
  ck_assert_float_eq_tol(f_s21_4, f_orig_4, 0.00001);
  ck_assert_float_eq_tol(f_s21_5, f_orig_5, 0.00001);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "%*f%5f %10f %2f%3f";
  char str[100] =
      "2.1312231231e+4 -213.000000 +2.3112e-1 0.2131231231 000000.000000";

  float f_s21_1 = 0, f_s21_2 = 0, f_s21_3 = 0, f_s21_4 = 0, f_s21_5 = 0;
  float f_orig_1 = 0, f_orig_2 = 0, f_orig_3 = 0, f_orig_4 = 0, f_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &f_s21_1, &f_s21_2, &f_s21_3, &f_s21_4, &f_s21_5);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2, &f_orig_3, &f_orig_4,
                    &f_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_float_eq_tol(f_s21_2, f_orig_2, 0.00001);
  ck_assert_float_eq_tol(f_s21_3, f_orig_3, 0.00001);
  ck_assert_float_eq_tol(f_s21_4, f_orig_4, 0.00001);
  ck_assert_float_eq_tol(f_s21_5, f_orig_5, 0.00001);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "%*f%*f %*f %*f%3f";
  char str[100] =
      "2.1312231231e+4 -213.000000 +2.3112e-1 0.2131231231 000000.000000";

  float f_s21_1 = 0, f_s21_2 = 0, f_s21_3 = 0, f_s21_4 = 0, f_s21_5 = 0;
  float f_orig_1 = 0, f_orig_2 = 0, f_orig_3 = 0, f_orig_4 = 0, f_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &f_s21_1, &f_s21_2, &f_s21_3, &f_s21_4, &f_s21_5);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2, &f_orig_3, &f_orig_4,
                    &f_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_float_eq_tol(f_s21_2, f_orig_2, 0.00001);
  ck_assert_float_eq_tol(f_s21_3, f_orig_3, 0.00001);
  ck_assert_float_eq_tol(f_s21_4, f_orig_4, 0.00001);
  ck_assert_float_eq_tol(f_s21_5, f_orig_5, 0.00001);
}
END_TEST

START_TEST(test_11) {
  char format[100] = "%lf%5lf %10lf %2lf%3lf";
  char str[100] =
      "2.1312231231e+4 -213.000000 +2.3112e-1 0.2131231231 000000.000000";

  double f_s21_1 = 0, f_s21_2 = 0, f_s21_3 = 0, f_s21_4 = 0, f_s21_5 = 0;
  double f_orig_1 = 0, f_orig_2 = 0, f_orig_3 = 0, f_orig_4 = 0, f_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &f_s21_1, &f_s21_2, &f_s21_3, &f_s21_4, &f_s21_5);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2, &f_orig_3, &f_orig_4,
                    &f_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_float_eq_tol(f_s21_2, f_orig_2, 0.00001);
  ck_assert_float_eq_tol(f_s21_3, f_orig_3, 0.00001);
  ck_assert_float_eq_tol(f_s21_4, f_orig_4, 0.00001);
  ck_assert_float_eq_tol(f_s21_5, f_orig_5, 0.00001);
}
END_TEST

START_TEST(test_12) {
  char format[100] = "%*Lf%5Lf %10Lf %2Lf%3Lf";
  char str[100] =
      "2.1312231231e+4 -213.000000 +2.3112e-1 0.2131231231 000000.000000";

  long double f_s21_1 = 0, f_s21_2 = 0, f_s21_3 = 0, f_s21_4 = 0, f_s21_5 = 0;
  long double f_orig_1 = 0, f_orig_2 = 0, f_orig_3 = 0, f_orig_4 = 0,
              f_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &f_s21_1, &f_s21_2, &f_s21_3, &f_s21_4, &f_s21_5);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2, &f_orig_3, &f_orig_4,
                    &f_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_ldouble_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_ldouble_eq_tol(f_s21_2, f_orig_2, 0.00001);
  ck_assert_ldouble_eq_tol(f_s21_3, f_orig_3, 0.00001);
  ck_assert_ldouble_eq_tol(f_s21_4, f_orig_4, 0.00001);
  ck_assert_ldouble_eq_tol(f_s21_5, f_orig_5, 0.00001);
}
END_TEST

START_TEST(test_13) {
  char format[100] = "%*lf%5Lf %10lf %2Lf%3lf";
  char str[100] =
      "2.1312231231e+4 -213.000000 +2.3112e-1 0.2131231231 000000.000000";

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

START_TEST(test_14) {
  char format[100] = "%f%f %f %10f%5f";
  char str[100] = ".312312 .100000 .0001 .123213 .001241241";

  float f_s21_1 = 0, f_s21_2 = 0, f_s21_3 = 0, f_s21_4 = 0, f_s21_5 = 0;
  float f_orig_1 = 0, f_orig_2 = 0, f_orig_3 = 0, f_orig_4 = 0, f_orig_5 = 0;

  int s21 =
      s21_sscanf(str, format, &f_s21_1, &f_s21_2, &f_s21_3, &f_s21_4, &f_s21_5);
  int orig = sscanf(str, format, &f_orig_1, &f_orig_2, &f_orig_3, &f_orig_4,
                    &f_orig_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_float_eq_tol(f_s21_1, f_orig_1, 0.00001);
  ck_assert_float_eq_tol(f_s21_2, f_orig_2, 0.00001);
  ck_assert_float_eq_tol(f_s21_3, f_orig_3, 0.00001);
  ck_assert_float_eq_tol(f_s21_4, f_orig_4, 0.00001);
  ck_assert_float_eq_tol(f_s21_5, f_orig_5, 0.00001);
}
END_TEST

Suite* test_s21_sscanf_f() {
  Suite* s = suite_create("\033[32m S21_SSCANF_F \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sscanf_f \033[0m");

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