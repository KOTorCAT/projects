#include "s21_function.h"

void big_decimal_add(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  int remains = 0;
  reset_big_decimal_to_zero(result);
  for (int i = 0; i < 32 * 8; i++) {
    int sum = big_get_bit(value_1, i) + big_get_bit(value_2, i) + remains;
    remains = sum / 2;
    big_set_bit(result, i, sum % 2);
  }
}

void big_decimal_mul(s21_big_decimal value_1, s21_big_decimal value_2,
                     s21_big_decimal *result) {
  reset_big_decimal_to_zero(result);
  for (int i = 32 * 3 - 1; i >= 0; i--) {
    s21_big_decimal temp = *result;
    if (big_get_bit(value_1, i)) {
      big_decimal_add(value_2, temp, result);
    }
    if (i != 0) {
      *result = shift_left(*result, 1);
    }
  }
}

void mul_to_ten_degree(s21_big_decimal *value, int degree) {
  for (int i = 0; i < degree; i++) {
    s21_big_decimal a = shift_left(*value, 3);
    s21_big_decimal b = shift_left(*value, 1);
    big_decimal_add(a, b, value);
  }
}
s21_big_decimal shift_left(s21_big_decimal value, int shift_value) {
  if (shift_value <= 0) {
    return value;
  }
  int full_shifts = shift_value / 32;
  int bit_shift = shift_value % 32;
  if (full_shifts > 0) {
    for (int i = 7; i >= full_shifts; i--) {
      value.bits[i] = value.bits[i - full_shifts];
    }
    for (int i = 0; i < full_shifts; i++) {
      value.bits[i] = 0;
    }
  }
  if (bit_shift > 0) {
    unsigned int remains = 0;
    for (int i = 0; i < 8; i++) {
      unsigned int temp = value.bits[i];
      value.bits[i] <<= bit_shift;
      value.bits[i] |= remains;
      remains = temp >> (32 - bit_shift);
    }
  }

  return value;
}

void decimal_to_big_decimal(s21_decimal value, int scale,
                            s21_big_decimal *result) {
  reset_big_decimal_to_zero(result);
  for (int i = 0; i < 3; i++) {
    result->bits[i] = value.bits[i];
  }
  mul_to_ten_degree(result, scale);
}

int big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result) {
  reset_decimal_to_zero(result);
  for (int i = 3; i < 8; i++) {
    if (value.bits[i] != 0) {
      return 1;
    }
  }
  for (int i = 0; i < 3; i++) {
    result->bits[i] = value.bits[i];
  }
  return 0;
}

int get_scale(s21_decimal value) { return ((value.bits[3] & SCALE) >> 16); }
void set_scale(s21_decimal *value, int scale) {
  int sign = get_sign(*value);
  value->bits[3] &= ~SCALE;
  value->bits[3] |= (scale << 16);
  set_sign(value, sign);
}
int get_sign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }
void set_sign(s21_decimal *value, int sign) {
  if (sign) {
    value->bits[3] |= (1u << 31);
  } else {
    value->bits[3] &= ~(1u << 31);
  }
}
int get_bit(s21_decimal value, int position) {
  int part = position / 32;
  int bit = position % 32;
  return (value.bits[part] >> bit) & 1;
}
void set_bit(s21_decimal *result, int position, int result_bit) {
  int part = position / 32;
  int bit = position % 32;
  if (result_bit) {
    result->bits[part] |= (1u << bit);
  } else {
    result->bits[part] &= ~(1u << bit);
  }
}

int big_get_bit(s21_big_decimal value, int position) {
  int part = position / 32;
  int bit = position % 32;
  return (value.bits[part] >> bit) & 1;
}

void big_set_bit(s21_big_decimal *result, int position, int result_bit) {
  int part = position / 32;
  int bit = position % 32;
  if (result_bit) {
    result->bits[part] |= (1u << bit);
  } else {
    result->bits[part] &= ~(1u << bit);
  }
}

s21_big_decimal invert_big_decimal(s21_big_decimal value) {
  for (int i = 0; i < 8; i++) {
    value.bits[i] = ~value.bits[i];
  }
  s21_big_decimal one = {{1}};
  big_decimal_add(value, one, &value);
  return value;
}

void reset_decimal_to_zero(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = 0;
  }
}
void reset_big_decimal_to_zero(s21_big_decimal *value) {
  for (int i = 0; i < 8; i++) {
    value->bits[i] = 0;
  }
}

int is_decimal_zero(s21_decimal value) {
  for (size_t i = 0; i < 3; i++) {
    if (value.bits[i] != 0) {
      return 1;
    }
  }
  return 0;
}
int is_big_decimal_zero(s21_big_decimal value) {
  for (size_t i = 0; i < 8; i++) {
    if (value.bits[i] != 0) {
      return 1;
    }
  }
  return 0;
}

int big_decimal_compare_absolute(s21_big_decimal a, s21_big_decimal b) {
  for (int i = 7; i >= 0; i--) {
    int a_bit, b_bit;
    for (int j = 31; j >= 0; j--) {
      a_bit = (a.bits[i] >> j) & 1;
      b_bit = (b.bits[i] >> j) & 1;
      if (a_bit != b_bit) {
        return (a_bit > b_bit) ? 1 : -1;
      }
    }
  }
  return 0;
}
