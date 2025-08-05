#ifndef S21_FUNCTION_H

// #ifndef S21_ARITHMETIC_H
// #include "../arithmetic/s21_arithmetic.h"
// #endif

#include "../s21_decimal.h"

void big_decimal_add(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);
void big_decimal_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result);

int get_bit(s21_decimal value, int position);
void set_bit(s21_decimal *result, int position, int result_bit);
void big_set_bit(s21_big_decimal *result, int position, int result_bit);
int big_get_bit(s21_big_decimal value, int position);
int get_sign(s21_decimal value);
void set_sign(s21_decimal *value, int sign);
int get_scale(s21_decimal value);
void set_scale(s21_decimal *value, int scale);
s21_big_decimal invert_big_decimal(s21_big_decimal value);
void mul_to_ten_degree(s21_big_decimal *value, int degree);
s21_big_decimal shift_left(s21_big_decimal value, int shift_value);
void decimal_to_big_decimal(s21_decimal value, int scale,
                            s21_big_decimal *result);
int big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result);
int is_decimal_zero(s21_decimal value);
int is_big_decimal_zero(s21_big_decimal value);
void reset_big_decimal_to_zero(s21_big_decimal *value);
void reset_decimal_to_zero(s21_decimal *value);
int big_decimal_compare_absolute(s21_big_decimal a, s21_big_decimal b);

#endif