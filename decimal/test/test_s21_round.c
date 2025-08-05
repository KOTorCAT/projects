#include "test_s21_decimal.h"

START_TEST(test_1) {
  s21_decimal dec = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal result = {0};
  s21_decimal real = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  int code = s21_round(dec, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_2) {
  s21_decimal dec = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};  // 1
  s21_decimal result = {0};
  s21_decimal real = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};  // 1
  int code = s21_round(dec, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_3) {
  s21_decimal dec = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};  // -1
  s21_decimal result = {0};
  s21_decimal real = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};  //-1
  int code = s21_round(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(sign, 1);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_4) {
  s21_decimal dec = {
      {0xCF5C048C, 0x004D2BEF, 0x00000000, 0x00070000}};  // 2172188218.2812812
  s21_decimal result = {0};
  s21_decimal real = {
      {0x8178F63A, 0x00000000, 0x00000000, 0x00000000}};  // 2172188218
  int code = s21_round(dec, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_5) {
  s21_decimal dec = {
      {0xFEADBDA2, 0x000001FB, 0x00000000, 0x80060000}};  // -2181821.218210
  s21_decimal result = {0};
  s21_decimal real = {
      {0x00214ABD, 0x00000000, 0x00000000, 0x80000000}};  //-2181821
  int code = s21_round(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(sign, 1);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_6) {
  s21_decimal dec = {{0x00000000, 0x00000000, 0x00000000, 0x00020000}};  // 0.00
  s21_decimal result = {0};
  s21_decimal real = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  int code = s21_round(dec, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_7) {
  s21_decimal dec = {{0x00000467, 0x0000007A, 0x00003215,
                      0x00010000}};  // 23650570576955414727997.5
  s21_decimal result = {0};
  s21_decimal real = {{0xCCCCCD3E, 0x199999A5, 0x00000502,
                       0x00000000}};  // 23650570576955414727998
  int code = s21_round(dec, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_8) {
  s21_decimal dec = {{0x000F4240, 0x00002710, 0x00002710,
                      0x80050000}};  // -1844674407800451901.20000
  s21_decimal result = {0};
  s21_decimal real = {
      {0xB333333D, 0x19999999, 0x00000000, 0x80000000}};  //-1844674407800451901
  int code = s21_round(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(sign, 1);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_9) {
  s21_decimal dec = {
      {0x52453C00, 0x0000013A, 0x00000000, 0x000B0000}};  // 13.50000000000
  s21_decimal result = {0};
  s21_decimal real = {{0x0000000E, 0x00000000, 0x00000000, 0x00000000}};  // 14
  int code = s21_round(dec, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_10) {
  s21_decimal dec = {{0x075BCD15, 0x00000000, 0x00000000,
                      0x001B0000}};  // 0.000000000000000000123456789
  s21_decimal result = {0};
  s21_decimal real = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  int code = s21_round(dec, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_11) {
  s21_decimal dec = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                      0x801C0000}};  // -7.92281625142643375935439503359
  s21_decimal result = {0};
  s21_decimal real = {{0x00000008, 0x00000000, 0x00000000, 0x80000000}};  //-8
  int code = s21_round(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 1);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_12) {
  s21_decimal dec = {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
                      0x80050000}};  // -184467440737095.51615
  s21_decimal result = {0};
  s21_decimal real = {
      {0xAC471B48, 0x0000A7C5, 0x00000000, 0x80000000}};  //-184467440737096
  int code = s21_round(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 1);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

Suite *test_s21_round() {
  Suite *s = suite_create("\033[33m S21_ROUND \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_round \033[0m");

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

  suite_add_tcase(s, tc);
  return s;
}