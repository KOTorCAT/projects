#ifndef S21_ARITHMETIC_H

#include "../convertors/convertors.h"
#include "../service/s21_function.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

s21_big_decimal div_get_remainder(s21_big_decimal number,
                                  s21_big_decimal delitel,
                                  s21_big_decimal *integer_result);
#endif