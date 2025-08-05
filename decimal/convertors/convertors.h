#ifndef CONVERTORS_H
#define CONVERTORS_H

#define MAX_FLOAT_FOR_DECIMAL 79228157791897854723898736640.0f
#define MIN_FLOAT_FOR_DECIMAL \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

#include "../arithmetic/s21_arithmetic.h"
#include "../others/s21_other.h"

typedef enum {
  CONVERTATION_OK = 0,
  CONVERTATION_ERROR = 1
} convertation_status;

typedef enum { SIGN_MINUS = 1, SIGN_PLUS = 0 } signs;

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int digit_to_decimal(s21_decimal *dec, int number);
s21_decimal parse_exponenta(char *float_str);
int decimal_is_set_bit(s21_decimal decimal, int index);
void transform_str(char *str);
int counter_digits(char *str);
int get_exp(char *str);
int whole_float(float num);
int del_zero_float(char *str, int scale_exp);
s21_decimal whole_float_to_decimal(char *float_str);

#endif