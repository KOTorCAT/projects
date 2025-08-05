#ifndef OTHER_H
#define OTHER_H

#include "../arithmetic/s21_arithmetic.h"
#include "../compare/comparison.h"

int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int is_digit(char c);
int dec_compare_half_one(s21_decimal value);

int valid_decimal(s21_decimal number);
int get_fractional_part(s21_decimal number, s21_decimal *fractional_part,
                        s21_decimal *tr_num);
int s21_truncate_big_decimal(s21_big_decimal value, int scale,
                             s21_big_decimal *result);
void s21_round_big_decimal(s21_big_decimal src, int *scale,
                           s21_big_decimal *dst);
int get_fractional_part_big_decimal(s21_big_decimal number, int scale,
                                    s21_big_decimal *fractional_part,
                                    s21_big_decimal *tr_num);
void s21_sub_big_decimal(s21_big_decimal value_1, s21_big_decimal value_2,
                         s21_big_decimal *result);
int compare_big(s21_big_decimal value, int scale);

typedef enum { CALCULATION_OK = 0, CALCULATION_ERROR = 1 } calculation_error;

#endif