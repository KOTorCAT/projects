
#include "../arithmetic/s21_arithmetic.h"

#ifndef S21_COMPARISON_H
#define S21_COMPARISON_H

#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SIGN_MASK 0x80000000

int normalize_and_convert(s21_decimal a, s21_decimal b, s21_big_decimal *out_a,
                          s21_big_decimal *out_b);
int big_decimal_compare(s21_big_decimal a, s21_big_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);

#endif