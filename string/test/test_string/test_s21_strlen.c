#include "../test_s21_string.h"

START_TEST(test_1) {
  char test_str[] = "Hello, world!";
  ck_assert_int_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_2) {
  char test_str[] = "  ksjdhasj    jkkjkasd   ss313 111                 2";
  ck_assert_int_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_3) {
  char test_str[] = "\0";
  ck_assert_int_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_4) {
  char test_str[] = "\n";
  ck_assert_int_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_5) {
  char test_str[] = "Hello, \n\n\0world!";
  ck_assert_int_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_6) {
  char test_str[] = "HFSDF SDAS\\n\n dsklfkllNNNN\0 NDJFNSD";
  ck_assert_int_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_7) {
  char test_str[] = "";
  ck_assert_int_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_8) {
  char test_str[] = "Hello, \t\\t\t\t\tworld!\n\n\0fdsfsd";
  ck_assert_int_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_9) {
  char test_str[] = "\033[31mвадывдо ОооОо \n\n\n \t\t\t dfsd\0 dsfs";
  ck_assert_int_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

START_TEST(test_10) {
  char test_str[] = "\0Hello, world!";
  ck_assert_int_eq(s21_strlen(test_str), strlen(test_str));
}
END_TEST

Suite* test_s21_strlen() {
  Suite* s = suite_create("\033[33m S21_STRLEN \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_strlen \033[0m");

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

  suite_add_tcase(s, tc);
  return s;
}
