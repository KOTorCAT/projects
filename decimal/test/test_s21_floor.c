#include "test_s21_decimal.h"

START_TEST(test_1) {
  s21_decimal dec = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  s21_decimal result = {0};
  s21_decimal real = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  int code = s21_floor(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_2) {
  s21_decimal dec = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};  // -1
  s21_decimal result = {0};
  s21_decimal real = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};  // -1
  int code = s21_floor(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 1);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_3) {
  s21_decimal dec = {{0x00000000, 0x00000000, 0x00000000, 0x00020000}};  // 0.00
  s21_decimal result = {0};
  s21_decimal real = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0
  int code = s21_floor(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_4) {
  s21_decimal dec = {
      {0x000F4240, 0x00000000, 0x00000000, 0x80020000}};  // -10000.00
  s21_decimal result = {0};
  s21_decimal real = {
      {0x00002710, 0x00000000, 0x00000000, 0x80000000}};  //-10000
  int code = s21_floor(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 1);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_5) {
  s21_decimal dec = {
      {0x00000467, 0x0000007A, 0x00000000, 0x00040000}};  // 52398601.1239
  s21_decimal result = {0};
  s21_decimal real = {
      {0x031F8A09, 0x00000000, 0x00000000, 0x00000000}};  // 52398601
  int code = s21_floor(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_6) {
  s21_decimal dec = {{0x00000467, 0x0000007A, 0x00003215,
                      0x00010000}};  // 23650570576955414727997.5
  s21_decimal result = {0};
  s21_decimal real = {{0xCCCCCD3D, 0x199999A5, 0x00000502,
                       0x00000000}};  // 23650570576955414727997
  int code = s21_floor(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_7) {
  s21_decimal dec = {{0x000F4240, 0x00002710, 0x00002710,
                      0x80050000}};  // -1844674407800451901.20000
  s21_decimal result = {0};
  s21_decimal real = {
      {0xB333333E, 0x19999999, 0x00000000, 0x80000000}};  //-1844674407800451902
  int code = s21_floor(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 1);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_8) {
  s21_decimal dec = {{0x0000000B, 0x00000000, 0x00000000, 0x80010000}};  // -1.1
  s21_decimal result = {0};
  s21_decimal real = {{0x00000002, 0x00000000, 0x00000000, 0x80000000}};  //-2
  int code = s21_floor(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 1);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_9) {
  s21_decimal dec = {
      {0xC2AC6A00, 0x00000021, 0x00000000, 0x000A0000}};  // 14.5000000000
  s21_decimal result = {0};
  s21_decimal real = {{0x0000000E, 0x00000000, 0x00000000, 0x00000000}};  // 14
  int code = s21_floor(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 0);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_10) {
  s21_decimal dec = {
      {0xFFFFFFFF, 0x00000000, 0x00000000, 0x80060000}};  // -4294.967295
  s21_decimal result = {0};
  s21_decimal real = {
      {0x000010C7, 0x00000000, 0x00000000, 0x80000000}};  //-4295
  int code = s21_floor(dec, &result);
  int sign = get_sign(result);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(sign, 1);
  ck_assert_int_eq(result.bits[0], real.bits[0]);
  ck_assert_int_eq(result.bits[1], real.bits[1]);
  ck_assert_int_eq(result.bits[2], real.bits[2]);
  ck_assert_int_eq(result.bits[3], real.bits[3]);
}
END_TEST

Suite *test_s21_floor() {
  Suite *s = suite_create("\033[33m S21_FLOOR \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_floor \033[0m");

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