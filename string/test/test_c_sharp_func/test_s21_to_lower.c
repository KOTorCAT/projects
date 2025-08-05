#include "../test_s21_string.h"

START_TEST(test_1) {
  char str[] = "HELLO WORLD!";
  char *s21_res = s21_to_lower(str);
  ck_assert_pstr_eq(s21_res, "hello world!");
  free(s21_res);
}
END_TEST

START_TEST(test_2) {
  char str[] = "21312HELLO ##WO2131RLD!!";
  char *s21_res = s21_to_lower(str);
  ck_assert_pstr_eq(s21_res, "21312hello ##wo2131rld!!");
  free(s21_res);
}
END_TEST

START_TEST(test_3) {
  char str[] = "";
  char *s21_res = s21_to_lower(str);
  ck_assert_pstr_eq(s21_res, "");
  free(s21_res);
}
END_TEST

START_TEST(test_4) {
  char str[] = "\0";
  char *s21_res = s21_to_lower(str);
  ck_assert_pstr_eq(s21_res, "\0");
  free(s21_res);
}
END_TEST

START_TEST(test_5) {
  char str[] = "AaaAA\t\t OO \e\0LLll";
  char *s21_res = s21_to_lower(str);
  ck_assert_pstr_eq(s21_res, "aaaaa\t\t oo \e\0llll");
  free(s21_res);
}
END_TEST

Suite *test_s21_to_lower() {
  Suite *s = suite_create("\033[1;35m S21_TO_LOWER \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_to_lower \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);

  suite_add_tcase(s, tc);

  return s;
}