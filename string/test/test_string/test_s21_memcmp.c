#include "../test_s21_string.h"

START_TEST(test_1) {
  char str1[] = "Hello world!!";
  char str2[] = "Hello";
  int len = 10;

  int res1 = s21_memcmp(str1, str2, len);
  int res2 = memcmp(str1, str2, len);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}
END_TEST

START_TEST(test_2) {
  char str1[] = "Hello world!!";
  char str2[] = "Hel\0lo";
  int len = 5;
  int res1 = s21_memcmp(str1, str2, len);
  int res2 = memcmp(str1, str2, len);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}

START_TEST(test_3) {
  char str1[] = "Hel\0lo world!!";
  char str2[] = "Hel\0lo";
  int len = 5;
  int res1 = s21_memcmp(str1, str2, len);
  int res2 = memcmp(str1, str2, len);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}

START_TEST(test_4) {
  char str1[] = "";
  char str2[] = "";
  int len = 5;
  int res1 = s21_memcmp(str1, str2, len);
  int res2 = memcmp(str1, str2, len);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}

START_TEST(test_5) {
  char str1[] = "21312jh3c\t \t qqwq \t\t\t ffffffff";
  char str2[] = "21312jh3c\t \t qqwq \t\t\t ffffffff";
  int len = 10;
  int res1 = s21_memcmp(str1, str2, len);
  int res2 = memcmp(str1, str2, len);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}

START_TEST(test_6) {
  char str1[] = "21312jh3c\t \t q\0qwq \t\t\t ffffffff";
  char str2[] = "21312jh3c\t \t qqwq \t\t\t ffffffff";
  int len = 14;
  int res1 = s21_memcmp(str1, str2, len);
  int res2 = memcmp(str1, str2, len);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}

START_TEST(test_7) {
  char str1[] = "2131\t\t\2jh3c\t \t q\0qwq \t\t\t ffffffff";
  char str2[] = "21312jh3c\t \t qqwq \t\t\t ffffffff";
  int len = 14;
  int res1 = s21_memcmp(str1, str2, len);
  int res2 = memcmp(str1, str2, len);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}

START_TEST(test_8) {
  char str1[] = "\0";
  char str2[] = "\0fdsf";
  int len = 3;
  int res1 = s21_memcmp(str1, str2, len);
  int res2 = memcmp(str1, str2, len);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}

START_TEST(test_9) {
  char str1[] = "";
  char str2[] = "fdsf";
  int len = 3;
  int res1 = s21_memcmp(str1, str2, len);
  int res2 = memcmp(str1, str2, len);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}

START_TEST(test_10) {
  char str1[] = "hello school 21!!";
  char str2[] = "hello school 21!!";
  int len = 10;
  int res1 = s21_memcmp(str1, str2, len);
  int res2 = memcmp(str1, str2, len);

  ck_assert((res1 > 0 && res2 > 0) || (res1 < 0 && res2 < 0) ||
            (res1 == 0 && res2 == 0));
}

Suite* test_s21_memcmp() {
  Suite* s = suite_create("\033[33m S21_MEMCMP \033[0m");
  TCase* tc = tcase_create("\033[31m test s21_memcmp \033[0m");

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