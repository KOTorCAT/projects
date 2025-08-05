#include "test_s21_decimal.h"

START_TEST(test_1) {
  float a = 5.6;
  s21_decimal dec = {0};

  s21_from_float_to_decimal(a, &dec);
  float b = dec.bits[0] / pow(10, get_scale(dec));

  ck_assert_float_eq(a, b);
}
END_TEST

START_TEST(test_2) {
  float a = 0.56;
  s21_decimal dec = {0};

  s21_from_float_to_decimal(a, &dec);
  ck_assert_int_eq(56, dec.bits[0]);
  ck_assert_int_eq(2, get_scale(dec));
}
END_TEST

START_TEST(test_3) {
  float a = 0.;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};  // 0

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_4) {
  float a = 0.0000000000000000000000000001;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {{0x00000001, 0x00000000, 0x00000000,
                       0x001C0000}};  // 0.0000000000000000000000000001

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_5) {
  float a = 0.011;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {
      {0x0000000B, 0x00000000, 0x00000000, 0x00030000}};  // 0.011

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_6) {
  float a = 0.00000022137;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {
      {0x00005679, 0x00000000, 0x00000000, 0x000B0000}};  // 0.00000022137

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_7) {
  float a = 1.831828;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {
      {0x001BF394, 0x00000000, 0x00000000, 0x00060000}};  // 1.831828

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_8) {
  float a = 0.00075149;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {
      {0x0001258D, 0x00000000, 0x00000000, 0x00080000}};  // 0.00075149

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_9) {
  float a = 0.0000075149;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {
      {0x0001258D, 0x00000000, 0x00000000, 0x000A0000}};  // 0.0000075149

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_10) {
  float a = 0.000000075149;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {
      {0x0001258D, 0x00000000, 0x00000000, 0x000C0000}};  // 0.000000075149

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_11) {
  float a = 0.00000075149;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {
      {0x0001258D, 0x00000000, 0x00000000, 0x000B0000}};  // 0.00000075149

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
}
END_TEST

START_TEST(test_12) {
  float a = -1.;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};  // -1

  int sign_real = get_scale(real);
  int sign_dec = get_scale(dec);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
  ck_assert_int_eq(sign_dec, sign_real);
}
END_TEST

START_TEST(test_13) {
  float a = 212818300.;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {
      {0x0CAF597C, 0x00000000, 0x00000000, 0x00000000}};  // 212818300

  int sign_real = get_scale(real);
  int sign_dec = get_scale(dec);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
  ck_assert_int_eq(sign_dec, sign_real);
}
END_TEST

START_TEST(test_14) {
  float a = 655350.;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {{0x9FFF6, 0x00000000, 0x00000000, 0x00000000}};  // 655350

  int sign_real = get_scale(real);
  int sign_dec = get_scale(dec);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
  ck_assert_int_eq(sign_dec, sign_real);
}
END_TEST

START_TEST(test_15) {
  float a = 33223.;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {
      {0x000081C7, 0x00000000, 0x00000000, 0x00000000}};  // 33223

  int sign_real = get_scale(real);
  int sign_dec = get_scale(dec);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
  ck_assert_int_eq(sign_dec, sign_real);
}
END_TEST

START_TEST(test_16) {
  float a = 56210.;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {
      {0x0000DB92, 0x00000000, 0x00000000, 0x00000000}};  // 56210

  int sign_real = get_scale(real);
  int sign_dec = get_scale(dec);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
  ck_assert_int_eq(sign_dec, sign_real);
}
END_TEST

START_TEST(test_17) {
  float a = 74231170000000000000.;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {{0x47A22000, 0x062A17D2, 0x00000004,
                       0x00000000}};  // 74231170000000000000

  int sign_real = get_scale(real);
  int sign_dec = get_scale(dec);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
  ck_assert_int_eq(sign_dec, sign_real);
}
END_TEST

START_TEST(test_18) {
  float a = 70172130000000000000000000000.;
  s21_decimal dec = {0};

  int code = s21_from_float_to_decimal(a, &dec);
  s21_decimal real = {{0xA9400000, 0xB25EFECA, 0xE2BD0685,
                       0x00000000}};  // 70172130000000000000000000000

  int sign_real = get_scale(real);
  int sign_dec = get_scale(dec);

  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(dec.bits[0], real.bits[0]);
  ck_assert_int_eq(dec.bits[1], real.bits[1]);
  ck_assert_int_eq(dec.bits[2], real.bits[2]);
  ck_assert_int_eq(dec.bits[3], real.bits[3]);
  ck_assert_int_eq(sign_dec, sign_real);
}
END_TEST

Suite *test_s21_from_float_to_decimal() {
  Suite *s = suite_create("\033[33m S21_FROM_FLOAT_TO_DECIMAL \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_from_float_to_decimal \033[0m");

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

  suite_add_tcase(s, tc);
  return s;
}
