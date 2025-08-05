#include "convertors.h"

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  if (!dst) {
    error = 1;
  }

  if (!error) {
    if (src < 0) {
      set_sign(dst, SIGN_MINUS);
      if (src == INT_MIN)
        src = -src;
      else
        src = abs(src);
    };
    dst->bits[0] = src;
  }
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = 0;

  if (!dst || isinf(src) || /*fabsf(src) > MAX_FLOAT_FOR_DECIMAL ||
      fabsf(src) < MIN_FLOAT_FOR_DECIMAL ||*/
      !valid_decimal(*dst)) {
    status = 1;
  }

  if (!status) {
    if (src == 0.0) return status;

    if (!whole_float(src)) {
      char float_str[50] = {};
      sprintf(float_str, "%.6E", fabsf(src));

      int scale_exp = get_exp(float_str);
      *dst = parse_exponenta(float_str);
      int count_digit_after_point = counter_digits(float_str);

      int scale_decimal = 0;

      scale_decimal = abs(scale_exp - count_digit_after_point);
      set_scale(dst, scale_decimal);
    }
    if (whole_float(src)) {
      char float_str[50] = {};
      sprintf(float_str, "%.6E", fabsf(src));
      int scale_exp = get_exp(float_str);
      int deleted_zero = del_zero_float(float_str, scale_exp);
      *dst = whole_float_to_decimal(float_str);
      if (deleted_zero) {
        s21_decimal mul = {{10}};
        for (int i = 0; i < deleted_zero; i++) {
          s21_mul(*dst, mul, dst);
        }
      }
    }
    if (src < 0) set_sign(dst, 1);
  }

  return status;
}

s21_decimal whole_float_to_decimal(char *float_str) {
  s21_decimal result = {0};
  s21_big_decimal res_dec = {0};

  char *ptr = float_str;

  while (*ptr != '\0') {
    if (is_digit(*ptr)) {
      mul_to_ten_degree(&res_dec, 1);
      s21_big_decimal tmp_dec = {0};
      tmp_dec.bits[0] = *ptr - '0';
      big_decimal_add(res_dec, tmp_dec, &res_dec);
    }
    ptr++;
  }
  big_decimal_to_decimal(res_dec, &result);

  return result;
}

int del_zero_float(char *str, int scale_exp) {
  int count_zero;
  char *ptr = strchr(str, 'E');
  while (*ptr != '\0') {
    *ptr = '\0';
    ptr++;
  }

  int len_str = strlen(str) - 1;
  int count_digit_after_point = counter_digits(str);
  count_zero = abs(scale_exp - count_digit_after_point);
  for (int i = len_str; i >= 0; i--) {
    if (str[i] == '0' && count_zero > 0) {
      str[i] = '\0';
      count_zero--;
    } else
      break;
  }
  return count_zero;
}

int whole_float(float num) {
  int result = 1;
  if (fabsf(num - truncf(num)) > 1e-30) result = 0;
  return result;
}

int counter_digits(char *str) {
  int count = 0;
  char *ptr = strchr(str, '.');
  ptr++;
  while (*ptr != '\0') {
    count++;
    ptr++;
  }
  return count;
}
void transform_str(char *str) {
  int len_str = strlen(str);
  char str_copy[50] = {0};
  strcpy(str_copy, str);
  char *ptr = str_copy;

  for (int i = len_str; i >= 0; i--) {
    if (ptr[i] == 'E') {
      ptr[i] = '\0';
      break;
    }
    ptr[i] = '\0';
  }
  len_str = strlen(str_copy) - 1;
  while (len_str > 0) {
    if (ptr[len_str] == '0') {
      ptr[len_str] = '\0';
    } else
      break;
    len_str--;
  }
  strcpy(str, str_copy);
}

int get_exp(char *str) {
  int result = 0;
  int sign = 1;
  char *ptr = strchr(str, 'E');
  while (*ptr != '\0') {
    if (*ptr == '-') sign = -1;
    if (is_digit(*ptr)) {
      result *= 10;
      result += *ptr - '0';
    }
    ptr++;
  }

  return result * sign;
}
s21_decimal parse_exponenta(char *float_str) {
  s21_decimal result = {0};
  s21_big_decimal res_dec = {0};

  transform_str(float_str);
  char *ptr = float_str;

  while (*ptr != '\0') {
    if (is_digit(*ptr)) {
      mul_to_ten_degree(&res_dec, 1);
      s21_big_decimal tmp_dec = {0};
      tmp_dec.bits[0] = *ptr - '0';
      big_decimal_add(res_dec, tmp_dec, &res_dec);
    }
    ptr++;
  }
  big_decimal_to_decimal(res_dec, &result);

  return result;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0;
  if (!valid_decimal(src) || !dst) error = 1;

  if (!error) {
    s21_truncate(src, &src);
    if (src.bits[1] != 0 || src.bits[2] != 0) {
      error = 1;
    }

    if (!error) {
      *dst = src.bits[0];
      if (get_sign(src)) *dst = -*dst;
    }
  }
  return error;
}

int digit_to_decimal(s21_decimal *dec, int number) {
  int error = 0;
  if (!dec) error = 1;
  if (!error) {
    dec->bits[0] = number;
  }
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  convertation_status code = CONVERTATION_OK;
  if (!valid_decimal(src) || !dst) code = CONVERTATION_ERROR;
  double tmp = 0.0;
  int scale = get_scale(src);
  for (int i = 0; i < 96; i++) {
    if (decimal_is_set_bit(src, i) != 0) tmp += pow(2.0, i);
  }
  double powerten = pow(10, scale);
  tmp /= powerten;

  *dst = (float)tmp;

  if (get_sign(src)) *dst *= -1;

  return code;
}

int decimal_is_set_bit(s21_decimal decimal, int index) {
  int bit = decimal.bits[index / 32] & (1U << (index % 32));
  return bit ? 1 : 0;
}