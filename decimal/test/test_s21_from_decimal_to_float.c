#include "test_s21_decimal.h"

START_TEST(test_1) {
  s21_decimal dec = {{56, 0, 0, 0}};
  set_scale(&dec, 2);
  float f = 0.0;
  s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, 0.56);
}
END_TEST

START_TEST(test_2) {
  s21_decimal dec = {{0, 0b11, 0, 0}};
  set_scale(&dec, 3);
  float f = 0.0;
  s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, 12884901.888);
}
END_TEST

START_TEST(test_3) {
  s21_decimal dec = {{56, 0, 0, 0}};
  set_scale(&dec, 2);
  set_sign(&dec, 1);
  float f = 0.0;
  s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, -0.56);
}
END_TEST

START_TEST(test_4) {
  s21_decimal dec = {{0, 0b11, 0, 0}};
  set_scale(&dec, 3);
  set_sign(&dec, 1);
  float f = 0.0;
  s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, -12884901.888);
}
END_TEST

START_TEST(test_5) {
  s21_decimal dec = {{0, 0, 0, 0}};
  set_scale(&dec, 3);
  set_sign(&dec, 1);
  float f = 0.0;
  s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, 0);
}
END_TEST

START_TEST(test_6) {
  s21_decimal dec = {
      {0x000026B9, 0x00000000, 0x00000000, 0x00030000}};  // 9.913
  float f = 9.913;
  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_int_eq(dec.bits[0], 9913);
  ck_assert_int_eq(get_scale(dec), 3);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_7) {
  s21_decimal dec = {{0}};

  float f = 1.5;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_int_eq(dec.bits[0], 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_8) {
  s21_decimal dec = {{0x00000009, 0x00000000, 0x00000000, 0x80010000}};  // -0.9

  float f = 7.0;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_int_eq(dec.bits[0], 9);
  ck_assert_int_eq(get_scale(dec), 1);
  ck_assert_int_eq(get_sign(dec), 1);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_9) {
  s21_decimal dec = {
      {0x00002F0D, 0x00000000, 0x00000000, 0x80030000}};  // -12.045

  float f = 0.0;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_int_eq(dec.bits[0], 12045);
  ck_assert_int_eq(get_scale(dec), 3);
  ck_assert_int_eq(get_sign(dec), 1);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_10) {
  s21_decimal dec = {
      {0x00000000, 0x00000000, 0x00000000, 0x800A0000}};  // 0.0000000000

  float f = 3.0;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, 0.0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_11) {
  s21_decimal dec = {
      {0xF533512E, 0x0000004B, 0x00000000, 0x00060000}};  // 326236.328238

  float f = 0.0;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, 326236.328238);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_12) {
  s21_decimal dec = {
      {0x51A337CD, 0x00000002, 0x00000000, 0x80040000}};  // -995958.5741

  float f = 0.0;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, -995958.5741);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_13) {
  s21_decimal dec = {
      {0xDC425734, 0x01C068FA, 0x00000000, 0x00070000}};  // 12621621621.2821812

  float f = 0.0;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, 12621621621.2821812);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_14) {
  s21_decimal dec = {
      {0xCC133B70, 0x004D86D4, 0x00000000, 0x000B0000}};  // 218218.21721721712

  float f = 0.0;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, 218218.21721721712);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_15) {
  s21_decimal dec = {{0x00000001, 0x00000000, 0x00000000,
                      0x00140000}};  // 0.00000000000000000001

  float f = 0.0;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, 0.00000000000000000001);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_16) {
  s21_decimal dec = {{0x003A6E50, 0x007F1483, 0x003215CF,
                      0x00020000}};  // 605492791886648540813348.641

  float f = 0.0;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, 605492791886648540813348.641);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_17) {
  s21_decimal dec = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                      0x80000000}};  // -79228162514264337593543950335

  float f = 0.0;

  int result = s21_from_decimal_to_float(dec, &f);

  ck_assert_float_eq(f, -79228162514264337593543950335.);
  ck_assert_int_eq(result, 0);
}
END_TEST

Suite *test_s21_from_decimal_to_float() {
  Suite *s = suite_create("\033[33m S21_FROM_DECIMAL_TO_FLOAT \033[0m");
  TCase *tc = tcase_create("\033[31m test s21_from_decimal_to_float \033[0m");

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

  suite_add_tcase(s, tc);
  return s;
}
