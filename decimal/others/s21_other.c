#include "s21_other.h"

#include <math.h>
#include <stdint.h>

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = CALCULATION_OK;

  if (!result || !valid_decimal(value)) status = CALCULATION_ERROR;

  if (status == CALCULATION_OK) {
    int scale = get_scale(value);
    if (scale) {
      s21_big_decimal number = {0};
      decimal_to_big_decimal(value, 0, &number);
      s21_big_decimal delitel = {{1}};
      for (int i = 0; i < scale; i++) {
        s21_big_decimal ten = {{10}};
        big_decimal_mul(delitel, ten, &delitel);
      }
      s21_big_decimal result_tmp = {0};
      div_get_remainder(number, delitel, &result_tmp);
      big_decimal_to_decimal(result_tmp, result);
    } else
      *result = value;

    if (get_sign(value)) set_sign(result, 1);
  }

  return status;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = valid_decimal(value);
  if (error) {
    *result = value;
    result->bits[3] ^= MINUS;
  }
  return error;
}

int valid_decimal(s21_decimal number) {
  int result = 0;
  int bits_0_15 = 0b00000000000000001111111111111111;
  int bits_24_30 = 0b01111111000000000000000000000000;
  if ((number.bits[3] & bits_0_15) == 0 && (number.bits[3] & bits_24_30) == 0)
    result = 1;

  return result;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int error = 0;
  s21_decimal tr_num = {0};
  s21_decimal fractional_part = {0};
  s21_decimal one = {{1}};
  if (!result) error = 1;

  if (!error) {
    get_fractional_part(value, &fractional_part, &tr_num);
    int result_compare = dec_compare_half_one(fractional_part);
    if (result_compare == 2) {
      *result = tr_num;
    }
    if (result_compare == 3) {
      if (get_sign(tr_num))
        s21_sub(tr_num, one, result);
      else
        s21_add(tr_num, one, result);
    }
    if (result_compare == 1) {
      if (tr_num.bits[0] % 2 == 0)
        *result = tr_num;
      else
        s21_add(tr_num, one, result);
    }
  }

  return error;
}

int is_digit(char c) {
  int result = 0;
  if (c >= '0' && c <= '9') result = 1;
  return result;
}

int dec_compare_half_one(s21_decimal value) {
  /*
  compare s21_decimal value with 0.5.
  if value == 0.5 return 1
  if value < 0.5 return 2
  if value > 0.5 return 3
  */
  int result = 0;
  int scale_1 = get_scale(value);
  int scale_2 = 1;

  s21_decimal dec_half_1 = {
      {5, 0, 0, 0b00000000000000010000000000000000}};  // number 0.5

  if (scale_1 == scale_2) {
    if (value.bits[0] == dec_half_1.bits[0] && value.bits[1] == 0 &&
        value.bits[2] == 0)
      result = 1;
    if (value.bits[0] < dec_half_1.bits[0] && value.bits[1] == 0 &&
        value.bits[2] == 0)
      result = 2;
    if (value.bits[0] > dec_half_1.bits[0] && value.bits[1] == 0 &&
        value.bits[2] == 0)
      result = 3;
  }

  else {
    s21_big_decimal dec_big = {0};
    decimal_to_big_decimal(dec_half_1, (scale_1 - scale_2), &dec_big);
    big_decimal_to_decimal(dec_big, &dec_half_1);

    int stop = 0;
    for (int i = 2; i >= 0; i--) {
      if (stop) break;
      for (int j = 31; j >= 0; j--) {
        if (((value.bits[i] >> j) & 1) != ((dec_half_1.bits[i] >> j) & 1)) {
          result = ((value.bits[i] >> j) & 1) < ((dec_half_1.bits[i] >> j) & 1)
                       ? 2
                       : 3;
          stop = 1;
          break;
        }
      }
      if (!stop) result = 1;
    }
  }
  return result;
}

int get_fractional_part(s21_decimal number, s21_decimal *fractional_part,
                        s21_decimal *tr_num) {
  int error = 0;
  s21_truncate(number, tr_num);
  s21_sub(number, *tr_num, fractional_part);

  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  s21_decimal tr_num = {0};
  s21_decimal fractional_part = {0};
  if (!result) error = 1;

  if (!error) {
    get_fractional_part(value, &fractional_part, &tr_num);
    dec_compare_half_one(fractional_part);
    if (get_sign(tr_num) &&
        (fractional_part.bits[0] || fractional_part.bits[1] ||
         fractional_part.bits[2])) {
      s21_decimal one = {
          {0x00000001, 0x00000000, 0x00000000, 0x80000000}};  //-1
      s21_add(tr_num, one, &tr_num);
    }

    *result = tr_num;
  }

  return error;
}

void s21_round_big_decimal(s21_big_decimal src, int *scale,
                           s21_big_decimal *dst) {
  s21_big_decimal src_copy = src;
  s21_big_decimal tmp = {{0}};
  s21_big_decimal delitel = {{10}};
  s21_big_decimal remainder = {{0}};
  s21_big_decimal one = {{1}};
  s21_big_decimal ten = {{10}};

  int count = 0;
  while (*scale > 0) {
    if (*scale <= 28 && !src_copy.bits[3] && !src_copy.bits[4] &&
        !src_copy.bits[5] && !src_copy.bits[6] && !src_copy.bits[7])
      break;
    div_get_remainder(src_copy, delitel, &tmp);
    (*scale)--;
    count++;
    reset_big_decimal_to_zero(&src_copy);
    src_copy = tmp;
    reset_big_decimal_to_zero(&tmp);
  }

  delitel.bits[0] = 1;
  for (int i = 0; i < count; i++) {
    big_decimal_mul(delitel, ten, &delitel);
  }

  remainder = div_get_remainder(src, delitel, &tmp);

  s21_decimal remainder_finish = {0};
  big_decimal_to_decimal(remainder, &remainder_finish);
  set_scale(&remainder_finish, count);
  s21_decimal half_one = {
      {0b101, 0, 0, 0b00000000000000010000000000000000}};  // 0.5
  if (s21_is_greater_or_equal(remainder_finish, half_one)) {
    big_decimal_add(tmp, one, &tmp);
  }

  reset_big_decimal_to_zero(&src_copy);
  reset_big_decimal_to_zero(&remainder);

  remainder = div_get_remainder(tmp, ten, &src_copy);

  while (!remainder.bits[0] && *scale > 0) {
    reset_big_decimal_to_zero(&tmp);
    tmp = src_copy;
    (*scale)--;

    reset_big_decimal_to_zero(&remainder);
    s21_big_decimal tmp_inner = {0};
    remainder = div_get_remainder(src_copy, ten, &tmp_inner);
    reset_big_decimal_to_zero(&src_copy);
    src_copy = tmp_inner;
  }
  *dst = tmp;
}
