#include "test_s21_decimal.h"

START_TEST(test_1) {
  s21_decimal value1 = {{3, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value2 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {{3, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_mul(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_2) {
  s21_decimal value1 = {{1, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {{3, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {{3, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result;
  int res = s21_mul(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_3) {
  s21_decimal value1 = {{15, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value2 = {{4, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal real = {{60, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_mul(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_4) {
  s21_decimal value1 = {{15, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {{4, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {{60, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_mul(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_5) {
  s21_decimal value1 = {{15, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {{4, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal real = {{60, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_mul(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_6) {
  s21_decimal value1 = {{12345, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value2 = {{54321, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal real = {{670592745, 0, 0, 0b00000000000001000000000000000000}};
  s21_decimal result;

  int res = s21_mul(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_7) {
  s21_decimal value1 = {{0, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value2 = {{54321, 0, 0, 0b00000000000000110000000000000000}};
  s21_decimal real = {{0, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_mul(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_8) {
  s21_decimal value1 = {{12345, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value2 = {{0, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal real = {{0, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal result;

  int res = s21_mul(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_9) {
  s21_decimal dec1 = {{

      0b00111000110000111110101010000111, 0b11001110101001000000111100001011,
      0b00000000000000000000000000000001,
      0b10000000000000000000000000000000}};  // -33336786882574674567

  s21_decimal dec2 = {{

      0b00000000000000000101101110000000, 0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b10000000000000000000000000000000}};  // -23424

  s21_decimal pattern = {{

      0b00000110010100110100000010000000, 0b10100011011000001000001011001010,
      0b00000000000000001010010101011011,
      0b00000000000000000000000000000000}};  // 780880895937429177057408

  s21_decimal result = {0};
  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_10) {
  s21_decimal dec1 = {
      {0b00111000110000111110101010000111, 0b11001110101001000000111100001011,
       0b00000000000000000000000000000001,
       0b00000000000000000000000000000000}};  // 33336786882574674567

  s21_decimal dec2 = {{0b01110010000100101111100010001100,
                       0b00000000000000000000000000001100,
                       0b00000000000000000000000000000000,
                       0b00000000000010110000000000000000}};  // 0.53453453452

  s21_decimal pattern = {
      {0b01000110010000100010000101100001, 0b01101101001100100000100010000100,
       0b00111001100101000001010010011001,
       0b00000000000010010000000000000000}};  // 17819663858669495568.811827553

  s21_decimal result = {0};
  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_11) {
  s21_decimal dec1 = {
      {0b00111100111111101110101010000111, 0b00000000000110000001110010100010,
       0b00000000000000000000000000000000,
       0b00000000000100000000000000000000}};  // 0.6786882574674567

  s21_decimal dec2 = {{0b01110010000100101111100010001100,
                       0b00000000000000000000000000001100,
                       0b00000000000000000000000000000000,
                       0b00000000000010110000000000000000}};  // 0.53453453452

  s21_decimal pattern = {
      {0b11101010000110010000100111010100, 0b10000111011100011010000010000000,
       0b00000001001011000001011000100100,
       0b00000000000110110000000000000000}};  // 0.362782311789556881182755284

  s21_decimal result = {0};
  int code = s21_mul(dec1, dec2, &result);
  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 0);
}

START_TEST(test_12) {
  s21_decimal value1 = {
      {0b00111001100011011000111110001010, 0b10111000001101111101110011111101,
       0b00000000000000000000000010110100, 0b00000000000001100000000000000000}};
  s21_decimal value2 = {
      {0b00110101010000111110011010001000, 0b10001000001010111010000110110010,
       0b00000111100100011001100100010100, 0b00000000000011010000000000000000}};
  s21_decimal result;

  int res = s21_mul(value1, value2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_13) {
  s21_decimal value1 = {
      {0b00111001100011011000111110001010, 0b10111000001101111101110011111101,
       0b00000000000000000000000010110100, 0b10000000000001100000000000000000}};
  s21_decimal value2 = {
      {0b00110101010000111110011010001000, 0b10001000001010111010000110110010,
       0b00000111100100011001100100010100, 0b00000000000011010000000000000000}};
  s21_decimal result;

  int res = s21_mul(value1, value2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

Suite *test_s21_mul() {
  Suite *s = suite_create("\033[33m S21_MUL \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_mul \033[0m");
  //   print_test_info(value1,value2,result,real);
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