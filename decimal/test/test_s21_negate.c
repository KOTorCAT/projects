#include "test_s21_decimal.h"

START_TEST(test_1) {
  s21_decimal value = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {{1, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_negate(value, &result);

  ck_assert_int_eq(res, 1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_2) {
  s21_decimal value = {{54321, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal real = {{54321, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal result;

  int res = s21_negate(value, &result);

  ck_assert_int_eq(res, 1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_3) {
  s21_decimal value = {{54321, 0, 0, 0b00000100000000110000000000000000}};
  s21_decimal result;

  int res = s21_negate(value, &result);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_4) {
  s21_decimal value = {{

      0b10110110111101010000110101011001, 0b00110101111100111110111001110101,
      0b00000100100110010011110000010000, 0b10000000000011000000000000000000}};
  s21_decimal real = {{

      0b10110110111101010000110101011001, 0b00110101111100111110111001110101,
      0b00000100100110010011110000010000, 0b00000000000011000000000000000000}};
  s21_decimal result;

  int res = s21_negate(value, &result);

  ck_assert_int_eq(res, 1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_5) {
  s21_decimal value = {
      {0b11101010000110010000100111010100, 0b10000111011100011010000010000000,
       0b00000001001011000001011000100100, 0b00000000000110110000000000000000}};
  ;
  s21_decimal real = {
      {0b11101010000110010000100111010100, 0b10000111011100011010000010000000,
       0b00000001001011000001011000100100, 0b10000000000110110000000000000000}};
  ;
  s21_decimal result;

  int res = s21_negate(value, &result);

  ck_assert_int_eq(res, 1);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

Suite *test_s21_negate() {
  Suite *s = suite_create("\033[33m S21_NEGATE \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_negate \033[0m");
  // print_test_info(value1,value2,result,real);
  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);
  tcase_add_test(tc, test_5);

  suite_add_tcase(s, tc);
  return s;
}