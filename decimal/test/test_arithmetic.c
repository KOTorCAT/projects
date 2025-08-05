#include "test_s21_decimal.h"

// максимальное число 79,228,162,514,264,337,593,543,950,335

// умножение

START_TEST(test_1) {
  s21_decimal val_1 = {{0b11111111111111111111111111111111}};  // 4294967295
  s21_decimal val_2 = {{0b1111111111111}};                     // 8191

  s21_decimal result = {0};
  s21_decimal pattern = {
      {0b11111111111111111110000000000001,
       0b00000000000000000001111111111110}};  // 35180077113345
  int code = s21_mul(val_1, val_2, &result);

  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_2) {
  s21_decimal val_1 = {
      {0b10000000000000000000000000000001,
       0b10000000000000000000000000000001}};  // 9223372043297226753
  s21_decimal val_2 = {{0b00000000000000000001111111111111}};  // 8191

  s21_decimal result = {0};
  s21_decimal pattern = {
      {0b10000000000000000001111111111111, 0b10000000000000000010111111111110,
       0b00000000000000000000111111111111}};  // 75548640406647584333823
  int code = s21_mul(val_1, val_2, &result);

  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_3) {
  s21_decimal val_1 = {
      {0b10000000000000000000000000000001,
       0b10000000000000000000000000000001}};  // 9223372043297226753

  s21_decimal result = {0};
  s21_decimal pattern = {{0}};  //
  int code = s21_mul(val_1, val_1, &result);

  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_4) {
  s21_decimal val_1 = {{0b01100011000001110110111100001001,
                        0b00000000000000000000000010110000, 0,
                        0b00000000000000100000000000000000}};  // 7575756756.57
  s21_decimal val_2 = {{0b01001010101101010101001001010100,
                        0b00000000000000000000000010110010, 0,
                        0b00000000000000010000000000000000}};  // 76575757576.4

  s21_decimal pattern = {
      {0b11111011010111100101000011110100, 0b01010100101110100001100000110100,
       0b00000000000000000111101011011000,
       0b00000000000000110000000000000000}};  // 580119312848878667976.948
  s21_decimal result = {{0}};
  int code = s21_mul(val_1, val_2, &result);
  // print_decimal(result);

  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 0);
}
END_TEST

Suite *test_s21_arithmetic() {
  Suite *s = suite_create("\033[33m S21_ARITHMETIC \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_arithmetic \033[0m");

  tcase_add_test(tc, test_1);
  tcase_add_test(tc, test_2);
  tcase_add_test(tc, test_3);
  tcase_add_test(tc, test_4);

  suite_add_tcase(s, tc);
  return s;
}