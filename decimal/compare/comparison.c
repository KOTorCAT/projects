#include "comparison.h"

int big_decimal_compare(s21_big_decimal a, s21_big_decimal b) {
  int a_sign = a.bits[7] >> 31;
  int b_sign = b.bits[7] >> 31;

  if (a_sign != b_sign) {
    return (a_sign) ? -1 : 1;
  }

  int cmp = big_decimal_compare_absolute(a, b);
  return (a_sign) ? -cmp : cmp;
}

int normalize_and_convert(s21_decimal a, s21_decimal b, s21_big_decimal *out_a,
                          s21_big_decimal *out_b) {
  int scale_a = get_scale(a);
  int scale_b = get_scale(b);

  s21_big_decimal big_a, big_b;
  decimal_to_big_decimal(a, -1, &big_a);
  decimal_to_big_decimal(b, -1, &big_b);

  if (scale_a > scale_b) {
    mul_to_ten_degree(&big_b, scale_a - scale_b);
  } else if (scale_b > scale_a) {
    mul_to_ten_degree(&big_a, scale_b - scale_a);
  }

  *out_a = big_a;
  *out_b = big_b;
  return 0;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int a_zero = !a.bits[0] && !a.bits[1] && !a.bits[2];
  int b_zero = !b.bits[0] && !b.bits[1] && !b.bits[2];
  if (a_zero && b_zero) return 1;

  if (get_sign(a) != get_sign(b)) return 0;

  s21_big_decimal big_a, big_b;
  normalize_and_convert(a, b, &big_a, &big_b);
  return big_decimal_compare(big_a, big_b) == 0;
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int sign_a = get_sign(a);
  int sign_b = get_sign(b);

  if (sign_a != sign_b) {
    return !sign_a;
  }

  s21_big_decimal big_a, big_b;
  normalize_and_convert(a, b, &big_a, &big_b);
  return sign_a ? big_decimal_compare(big_a, big_b) < 0
                : big_decimal_compare(big_a, big_b) > 0;
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_greater(a, b) || s21_is_equal(a, b);
}

int s21_is_less(s21_decimal a, s21_decimal b) {
  return !s21_is_greater_or_equal(a, b);
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_greater(a, b);
}
