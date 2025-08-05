#include "../test_s21_string.h"

START_TEST(test_1) {
  char src[] = "123Hello world!123";
  char alf[] = "123";

  char *s21_res = s21_trim(src, alf);

  ck_assert_pstr_eq(s21_res, "Hello world!");
  free(s21_res);
}
END_TEST

START_TEST(test_2) {
  char src[] = "123Hello123 123world!123";
  char alf[] = "123";

  char *s21_res = s21_trim(src, alf);

  ck_assert_pstr_eq(s21_res, "Hello123 123world!");
  free(s21_res);
}
END_TEST

START_TEST(test_3) {
  char src[] = "1234444Hello123 123world!12443";
  char alf[] = "123";

  char *s21_res = s21_trim(src, alf);

  ck_assert_pstr_eq(s21_res, "4444Hello123 123world!1244");
  free(s21_res);
}
END_TEST

START_TEST(test_4) {
  char src[] = "1234444Hello123 123world!12443";
  char alf[] = "1234Hello ";

  char *s21_res = s21_trim(src, alf);

  ck_assert_pstr_eq(s21_res, "world!");
  free(s21_res);
}
END_TEST

START_TEST(test_5) {
  char src[] = "1234444Hello123 123world!12443";
  char alf[] = "1234Hello w";

  char *s21_res = s21_trim(src, alf);

  ck_assert_pstr_eq(s21_res, "rld!");
  free(s21_res);
}
END_TEST

START_TEST(test_6) {
  char src[] = "1234444Hello\t\t\t\t123 123w123aao\0rld!12443";
  char alf[] = "1234Hello\t ";

  char *s21_res = s21_trim(src, alf);

  ck_assert_pstr_eq(s21_res, "w123aa");
  free(s21_res);
}
END_TEST

Suite *test_s21_trim() {
  Suite *s = suite_create("\033[1;35m S21_TRIM \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_trim \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);
  tcase_add_test(tc, test_6);

  suite_add_tcase(s, tc);

  return s;
}