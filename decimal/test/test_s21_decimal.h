#ifndef TEST_S21_DECIMAL_H
#include <check.h>

#include "../compare/comparison.h"
#include "../convertors/convertors.h"
// #include "../arithmetic/s21_arithmetic.h"

Suite *test_s21_add();
Suite *test_s21_div();
Suite *test_s21_mul();
Suite *test_s21_sub();
Suite *decimal_suite();
Suite *test_s21_from_float_to_decimal();
Suite *test_s21_from_decimal_to_float();
Suite *test_s21_from_int_to_decimal();
Suite *test_s21_from_decimal_to_int();
Suite *test_s21_truncate();
Suite *test_s21_round_big_decimal();
Suite *test_s21_arithmetic();
Suite *test_s21_round();
Suite *test_s21_floor();
Suite *test_s21_negate();

#endif
