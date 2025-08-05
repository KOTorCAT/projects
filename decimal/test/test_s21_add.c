#include "test_s21_decimal.h"

START_TEST(test_1) {
  s21_decimal value1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value2 = {{3, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {{4, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_2) {
  s21_decimal value1 = {{1, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {{3, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {{2, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal result;
  int res = s21_add(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_3) {
  s21_decimal value1 = {{15, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value2 = {{4, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal real = {{11, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_4) {
  s21_decimal value1 = {{15, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {{4, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {{11, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_5) {
  s21_decimal value1 = {{15, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {{4, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal real = {{19, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_6) {
  s21_decimal value1 = {{12345, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value2 = {{54321, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal real = {{1288821, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_7) {
  s21_decimal value1 = {{0, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value2 = {{54321, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal real = {{54321, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_8) {
  s21_decimal value1 = {{12345, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value2 = {{0, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal real = {{12345, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_9) {
  s21_decimal value1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  s21_decimal value2 = {{6, 0, 0, 0b10000000000000010000000000000000}};
  s21_decimal real = {
      {0b11111111111111111111111111111110, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_10) {
  s21_decimal value1 = {
      {0b00101100100001111001110011110100, 0b10111000000101011110000001100010,
       0b00000000000000000000000010110100, 0b00000000000000100000000000000000}};
  s21_decimal value2 = {
      {0b11010000001111111110011010001000, 0b01101110011010101111011100101010,
       0b00000000000000011111000000000110, 0b00000000000011010000000000000000}};
  s21_decimal real = {
      {0b01011110011011100010011111011100, 0b11001001011101000011011110001011,
       0b01101011101101111000101101000010, 0b00000000000010010000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_11) {
  s21_decimal value1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b00000000000000000000000000000000}};
  s21_decimal value2 = {
      {0b01111000001000100110101010001000, 0b00011110001010100011101001100011,
       0b01101011101101111000101100110110, 0b00000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_12) {
  s21_decimal value1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {
      {0b01111000001000100110101010001000, 0b00011110001010100011101001100011,
       0b01101011101101111000101100110110, 0b10000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(test_13) {
  s21_decimal a = {{15, 0, 0, 0}};
  s21_decimal b = {{10, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{25, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_14) {
  s21_decimal a = {{999999999, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{1000000000, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_15) {
  s21_decimal a = {{123456789, 0, 0, 0}};
  s21_decimal b = {{987654321, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{1111111110, 0, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
}
END_TEST

START_TEST(test_16) {
  s21_decimal a = {{15, 0, 0, 0x80000000}};
  s21_decimal b = {{10, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{25, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_17) {
  s21_decimal a = {{123456, 0, 0, 0x00030000}};
  s21_decimal b = {{654321, 0, 0, 0x00050000}};
  s21_decimal result = {0};
  s21_decimal expected = {{12999921, 0, 0, 0x00050000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_18) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};
  s21_decimal b = {{1, 0, 0, 0x001C0000}};
  s21_decimal result = {0};
  s21_decimal expected = {{2, 0, 0, 0x001C0000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_19) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal result = {0};
  s21_decimal expected = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

START_TEST(test_20) {
  s21_decimal a = {{0x12A05F20, 0x1, 0, 0}};
  s21_decimal b = {{0x12A05F20, 0x1, 0, 0}};
  s21_decimal result = {0};
  s21_decimal expected = {{0x2540BE40, 0x2, 0, 0}};
  ck_assert_int_eq(s21_add(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
}
END_TEST

START_TEST(test_21) {
  s21_decimal value1 = {
      {0b11111111111111111111111111111111, 0b11111111111111111111111111111111,
       0b11111111111111111111111111111111, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {
      {0b01111000001000100110101010001000, 0b00011110001010100011101001100011,
       0b01101011101101111000101100110110, 0b10000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_add(value1, value2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

Suite *test_s21_add() {
  Suite *s = suite_create("\033[33m S21_ADD \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_add \033[0m");
  // print_test_info(value1,value2,result,real);
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
  tcase_add_test(tc, test_15);
  tcase_add_test(tc, test_16);
  tcase_add_test(tc, test_17);
  tcase_add_test(tc, test_18);
  tcase_add_test(tc, test_19);
  tcase_add_test(tc, test_20);
  tcase_add_test(tc, test_21);

  suite_add_tcase(s, tc);
  return s;
}
