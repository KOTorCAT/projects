#include "test_s21_decimal.h"

START_TEST(test_1) {
  s21_decimal value1 = {{3, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value2 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {{3, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_div(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_2) {
  s21_decimal value1 = {{3, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {{3, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result;
  int res = s21_div(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_3) {
  s21_decimal value1 = {{16, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value2 = {{4, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal real = {{4, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_div(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_4) {
  s21_decimal value1 = {{40, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {{5, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {{8, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_div(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_5) {
  s21_decimal value1 = {{10, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal value2 = {{4, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal real = {{25, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal result;

  int res = s21_div(value1, value2, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_6) {
  s21_decimal value1 = {{1234, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value2 = {{1234, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal real = {{10, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal result;

  int res = s21_div(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_7) {
  s21_decimal value1 = {{1234, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value2 = {{25, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal real = {{4936, 0, 0, 0b00000000000000100000000000000000}};
  s21_decimal result;

  int res = s21_div(value1, value2, &result);

  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_8) {
  s21_decimal value1 = {{12345, 0, 0, 0b00000000000000010000000000000000}};
  s21_decimal value2 = {{0, 0, 0, 0b10000000000000110000000000000000}};
  s21_decimal result;

  int res = s21_div(value1, value2, &result);

  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(test_9) {
  s21_decimal value1 = {{1, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal value2 = {{3, 0, 0, 0b00000000000000000000000000000000}};
  s21_decimal real = {
      {0b00000101010101010101010101010101, 0b00010100101101110000000011001011,
       0b00001010110001010100010011001010, 0b00000000000111000000000000000000}};
  s21_decimal result;
  int res = s21_div(value1, value2, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_10) {
  s21_decimal value1 = {
      {0b01100100000001110100010100110010, 0b00010001101000100010110010001101,
       0b00000000000000000000001010011101, 0b00000000000010100000000000000000}};
  s21_decimal value2 = {
      {0b01000111100110111011111011110011, 0b00000000000000000000000011011000,
       0b00000000000000000000000000000000, 0b00000000000001100000000000000000}};
  s21_decimal real = {
      {0b11111110101011011001011101101101, 0b01101001000010101000100110011110,
       0b00101010111011100111000110101101, 0b00000000000101100000000000000000}};
  s21_decimal result;
  int res = s21_div(value1, value2, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 3; i++) {
    ck_assert_int_eq(result.bits[i], real.bits[i]);
  }
}
END_TEST

START_TEST(test_11) {
  s21_decimal dec1 = {{

      0b00111000110000111110101010000111, 0b11001110101001000000111100001011,
      0b00000000000000000000000000000001,
      0b10000000000000000000000000000000}};  // -33336786882574674567

  s21_decimal dec2 = {{

      0b00000000000000000101101110000000, 0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b10000000000000000000000000000000}};  // -23424

  s21_decimal pattern = {{
      0b00010111010100101001011000111100,
      0b00011011100001110101000010011001,
      0b00101101111111000101100010100010,
      0b00000000000011010000000000000000,
  }};  // 1423189330711008.9893698770492

  s21_decimal result = {0};
  int code = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_12) {
  s21_decimal dec1 = {{0b00101110101110111110100000010101,
                       0b00000000000000000000001100001000,
                       0b00000000000000000000000000000000,
                       0b00000000000000100000000000000000}};  // 33336786882.77

  s21_decimal dec2 = {{

      0b00000001011001010110100111010100, 0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000001000000000000000000}};  //     2342.3444

  s21_decimal pattern = {{

      0b00011110011100100110111001111100, 0b01101101101011000001011100011000,
      0b00101101111111001010000000101011,
      0b00000000000101010000000000000000}};  // 14232231.128253385795871862396

  s21_decimal result = {0};
  int code = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_13) {
  s21_decimal dec1 = {
      {0b00101100100001111001110011110100, 0b10111000000101011110000001100010,
       0b00000000000000000000000010110100,
       0b10000000000000100000000000000000}};  // -33336786882574674567.56

  s21_decimal dec2 = {{

      0b00000000000000000101101110000000, 0b00000000000000000000000000000000,
      0b00000000000000000000000000000000,
      0b00000000000000000000000000000000}};  // 23424

  s21_decimal pattern = {{

      0b10110110111101010000110101011001, 0b00110101111100111110111001110101,
      0b00000100100110010011110000010000,
      0b10000000000011000000000000000000}};  // -1423189330711008.989393784153

  s21_decimal result = {0};
  int code = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 0);
}
END_TEST

START_TEST(test_14) {
  s21_decimal dec1 = {
      {0b00111000110000111110101010000111, 0b11001110101001000000111100001011,
       0b00000000000000000000000000000001,
       0b00000000000000000000000000000000}};  // 33336786882574674567

  s21_decimal dec2 = {{0b01110010000100101111100010001100,
                       0b00000000000000000000000000001100,
                       0b00000000000000000000000000000000,
                       0b00000000000010110000000000000000}};  // 0.53453453452

  s21_decimal pattern = {{

      0b11100011111101011111010001100101, 0b01011110110001011001001000010101,
      0b11001001100000111111010010011101,
      0b00000000000010010000000000000000}};  // 62366011416849540034.092987493

  s21_decimal result = {0};
  int code = s21_div(dec1, dec2, &result);
  ck_assert_int_eq(result.bits[0], pattern.bits[0]);
  ck_assert_int_eq(result.bits[1], pattern.bits[1]);
  ck_assert_int_eq(result.bits[2], pattern.bits[2]);
  ck_assert_int_eq(result.bits[3], pattern.bits[3]);
  ck_assert_int_eq(code, 0);
}
END_TEST

Suite *test_s21_div() {
  Suite *s = suite_create("\033[33m S21_DIV \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_div \033[0m");
  // print_test_info(result,real);

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

  suite_add_tcase(s, tc);
  return s;
}