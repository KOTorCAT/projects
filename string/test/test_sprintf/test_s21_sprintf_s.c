#include "../test_s21_string.h"

START_TEST(test_1) {
  char format[100] = "%s";
  char str1[100] = "";
  char str2[100] = "";

  char ch[100] = "Hello school 21!";

  int s21 = s21_sprintf(str1, format, ch);
  int orig = sprintf(str2, format, ch);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_2) {
  char format[100] = "%s";
  char str1[100] = "";
  char str2[100] = "";

  char ch[100] = "";

  int s21 = s21_sprintf(str1, format, ch);
  int orig = sprintf(str2, format, ch);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_3) {
  char format[100] = "%s";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[100] = "Hello school 21!";
  char ch_2[100] = "Hello nedosip";

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_4) {
  char format[100] = "%s%ssad";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[100] = "Hello school 21!";
  char ch_2[100] = "Hello nedosip";

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_5) {
  char format[100] = "%s    sadasd   %s";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[100] = "Hello school 21!";
  char ch_2[100] = "Hello nedosip";

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_6) {
  char format[100] = "%s";
  char str1[100] = "";
  char str2[100] = "";

  char ch[100] = "\0";

  int s21 = s21_sprintf(str1, format, ch);
  int orig = sprintf(str2, format, ch);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_7) {
  char format[100] = "%%%s    sadasd  %% %s";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[100] = "\t\nasdasd   1312";
  char ch_2[100] = "\\\\\e1231gre\0eqwe\t";

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_8) {
  char format[100] = "%s    sad%%asd   %s";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[100] = "\0\0\0\t\nasdasd   1312";
  char ch_2[100] = "\0\0\\\\\e1231gre\0eqwe\t";

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_9) {
  char format[100] = "%s    %%sadasd   %s";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[100] = "1.0213001 \n\n23123";
  char ch_2[100] = "000.1312.fdfs\0\t\t\t";

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_10) {
  char format[100] = "%s    %%sadasd   %s";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[100] = "1.0213001 \n\n23123";
  char ch_2[100] = "000.1312.fdfs\0\t\t\t";

  int s21 = s21_sprintf(str1, format, ch_1, ch_2);
  int orig = sprintf(str2, format, ch_1, ch_2);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_11) {
  char format[100] = "|%-15s|    |%%sadasd%5s|   |%.3s|";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[100] = "1.021323123";
  char ch_2[100] = "000.1312.fdfs\t\t\t";
  char ch_3[100] = "hellooooo";

  int s21 = s21_sprintf(str1, format, ch_1, ch_2, ch_3);
  int orig = sprintf(str2, format, ch_1, ch_2, ch_3);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_12) {
  char format[100] = "|%05s|    |%%sadasd%-5.5s|   |%-10.3s|";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[100] = "1.021323123";
  char ch_2[100] = "000.1312.fdfs\t\t\t";
  char ch_3[100] = "hellooooo";

  int s21 = s21_sprintf(str1, format, ch_1, ch_2, ch_3);
  int orig = sprintf(str2, format, ch_1, ch_2, ch_3);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_13) {
  char format[100] = "|%*.*s|    |%%sadasd%-*.*s|   |%-*.*s|";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[20] = "1.021323123";
  char ch_2[20] = "000.1312.fdfs\t\t\t";
  char ch_3[20] = "hellooooo";

  int weight = 10;
  int tochnost = 5;

  int s21 = s21_sprintf(str1, format, weight, tochnost, ch_1, weight, tochnost,
                        ch_2, weight, tochnost, ch_3);
  int orig = sprintf(str2, format, weight, tochnost, ch_1, weight, tochnost,
                     ch_2, weight, tochnost, ch_3);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_14) {
  char format[100] = "|%*.*s|    |%%sadasd%-10.*s|   |%-1.1s|";
  char str1[100] = "";
  char str2[100] = "";

  char ch_1[100] = "1.021323123";
  char ch_2[100] = "000.1312.fdfs\t\t\t";
  char ch_3[100] = "hellooooo";

  int weight = 10;
  int tochnost = 5;

  int s21 =
      s21_sprintf(str1, format, weight, tochnost, ch_1, tochnost, ch_2, ch_3);
  int orig =
      sprintf(str2, format, weight, tochnost, ch_1, tochnost, ch_2, ch_3);

  ck_assert_int_eq(s21, orig);
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* test_s21_sprintf_s() {
  Suite* s = suite_create("\033[1;34m S21_SPRINTF_S \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_sprintf_S \033[0m");

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
  // tcase_add_test(tc, test_14);

  suite_add_tcase(s, tc);
  return s;
}