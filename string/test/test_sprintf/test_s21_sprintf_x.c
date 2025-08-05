#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%x";
  char str1[100] = "";
  char str2[100] = "";

  int num = 0XbF;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%X";
  char str1[100] = "";
  char str2[100] = "";

  int num = 0XbF;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%x";
  char str1[100] = "";
  char str2[100] = "";

  int num = -0;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%x";
  char str1[100] = "";
  char str2[100] = "";

  int num = +0;

  int s21 = s21_sprintf(str1, format, num);
  int orig = sprintf(str2, format, num);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%x%X%x%X%x";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = +0;
  int num_2 = -0;
  int num_3 = 0x1BB44948D8D;
  int num_4 = -0x2123;
  int num_5 = +0X21123;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "|% x|  |% x|  |% x|% x|    |% x|";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = '\\';
  int num_2 = '\t';
  int num_3 = '\n';
  int num_4 = '\0';
  int num_5 = '%%%%';

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%+010X%%%-5.5x%+X%X% x";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = +0x213;
  int num_2 = -0x849;
  int num_3 = 0xC33;
  int num_4 = -218018;
  int num_5 = 0x212311;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%+ 10.1x|% -10.3X|%%\n\t|%+   3.2X|%-*x% 05x";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0x12312;
  int num_2 = -0x897345;
  int num_3 = 0x11;
  int num_4 = 0x12;
  int num_5 = 0x13;

  int weight = 15;

  int s21 =
      s21_sprintf(str1, format, num_1, num_2, num_3, weight, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, weight, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "% *x|% -10.3x|%%\n\t|% 3.2X|%*x";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0x12312;
  int num_2 = 0x200B20;
  int num_3 = 0xabc11;
  int num_4 = 0xeee;
  int num_5 = 0xadc;

  int weight = 15;
  int tochnost = 5;

  int s21 = s21_sprintf(str1, format, tochnost, num_1, num_2, num_3, weight,
                        num_4, weight, num_5);
  int orig = sprintf(str2, format, tochnost, num_1, num_2, num_3, weight, num_4,
                     num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "\n|% lx|\n| %hx|\n| %hX|\n|% hX|\n";
  char str1[100] = "";
  char str2[100] = "";

  long int num_1 = LONG_MIN;
  short int num_2 = SHRT_MAX;
  short int num_3 = SHRT_MIN;
  long int num_4 = LONG_MAX;

  int s21 = s21_sprintf(str1, format, num_1, num_2, num_3, num_4);
  int orig = sprintf(str2, format, num_1, num_2, num_3, num_4);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_11) {
  char format[100] = "\n%*lX|%-10.3hx|%%\n\t|% 3.2hx|%-*x%05lX";
  char str1[100] = "";
  char str2[100] = "";

  long int num_1 = LONG_MIN;
  short int num_2 = SHRT_MAX;
  short int num_3 = SHRT_MIN;
  short int num_4 = -0;
  long int num_5 = LONG_MAX;

  int weight = 10;
  int tochnost = 5;

  int s21 = s21_sprintf(str1, format, tochnost, num_1, num_2, num_3, weight,
                        num_4, num_5);
  int orig = sprintf(str2, format, tochnost, num_1, num_2, num_3, weight, num_4,
                     num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_12) {
  char format[100] = "%+-10.1X|%+-10.3x|%%\n\t|%+-3.2x|%+-*X% 05X";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0x12312;
  int num_2 = 0x200B20;
  int num_3 = 0xabc11;
  int num_4 = 0xeee;
  int num_5 = 0xadc;

  int weight = 10;

  int s21 =
      s21_sprintf(str1, format, num_1, num_2, num_3, weight, num_4, num_5);
  int orig = sprintf(str2, format, num_1, num_2, num_3, weight, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_13) {
  char format[100] = "%+-*x|%+-10.*x|%%\n\t|%+-3.2x|%+-*x% 05X";
  char str1[100] = "";
  char str2[100] = "";

  int num_1 = 0x12312;
  int num_2 = 0x200B20;
  int num_3 = 0xabc11;
  int num_4 = 0xeee;
  int num_5 = 0xadc;

  int weight = 10;
  int tochnost = 5;

  int s21 = s21_sprintf(str1, format, tochnost, num_1, tochnost, num_2, num_3,
                        weight, num_4, num_5);
  int orig = sprintf(str2, format, tochnost, num_1, tochnost, num_2, num_3,
                     weight, num_4, num_5);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* test_s21_sprintf_x() {
  Suite* s = suite_create("\033[1;34m S21_SPRINTF_X \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sprintf_x \033[0m");

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