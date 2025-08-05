
#include "s21_arithmetic.h"
#define PRINT_INFO

/*
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  //  на окургление банковское, на переполнения и т.д
  // еще сделать правильное вычитание
  if (is_decimal_zero(value_1) && !is_decimal_zero(value_2)) {
    *result = value_1;
    return 0;
  } else if (!is_decimal_zero(value_1) && is_decimal_zero(value_2)) {
    *result = value_2;
    return 0;
  }
  int error = 0;
  int scale1 = get_scale(value_1);
  int scale2 = get_scale(value_2);
  int sign1 = get_sign(value_1);
  int sign2 = get_sign(value_2);
  int res_sign = 0;
  int max_scale = 0;

  if (scale1 - scale2 > 0) {
    max_scale = scale1;
    scale2 = scale1 - scale2;
    scale1 = 0;
  } else {
    max_scale = scale2;
    scale1 = scale2 - scale1;
    scale2 = 0;
  }

  s21_big_decimal big_value_1;
  s21_big_decimal big_value_2;
  s21_big_decimal big_result;

  decimal_to_big_decimal(value_1, scale1, &big_value_1);
  decimal_to_big_decimal(value_2, scale2, &big_value_2);

  if (sign1 != sign2) {
    if (big_decimal_compare_absolute(big_value_1, big_value_2) == 1) {
      big_value_2 = invert_big_decimal(big_value_2);
      res_sign = sign1;
    } else {
      big_value_1 = invert_big_decimal(big_value_1);
      res_sign = sign2;
    }
  }

  big_decimal_add(big_value_1, big_value_2, &big_result);

  error = big_decimal_to_decimal(big_result, result);

  set_scale(result, max_scale);
  if (sign1 && sign2) {
    set_sign(result, 1);
  } else if (sign1 || sign2) {
    set_sign(result, res_sign);
  } else {
    set_sign(result, 0);
  }
  return error;
}
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_negate(value_2, &value_2);
  return s21_add(value_1, value_2, result);
}
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (is_decimal_zero(value_1) && !is_decimal_zero(value_2)) {
    *result = value_2;
    return 0;
  } else if (!is_decimal_zero(value_1) && is_decimal_zero(value_2)) {
    *result = value_1;
    return 0;
  }
  int error = 0;
  int sum_scale = get_scale(value_1) + get_scale(value_2);

  s21_big_decimal big_value_1;
  s21_big_decimal big_value_2;

  decimal_to_big_decimal(value_1, 0, &big_value_1);
  decimal_to_big_decimal(value_2, 0, &big_value_2);
  s21_big_decimal big_result;

  big_decimal_mul(big_value_1, big_value_2, &big_result);

  error = big_decimal_to_decimal(big_result, result);
  set_scale(result, sum_scale);
  if (get_sign(value_1) == get_sign(value_2)) {
    set_sign(result, 0);
  } else {
    set_sign(result, 1);
  }
  return error;
}
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!is_decimal_zero(value_1) && is_decimal_zero(value_2)) {
    *result = value_1;
    return 0;
  } else if (is_decimal_zero(value_1) && !is_decimal_zero(value_2)) {
    return 3;
  }
  int error = 0;
  int scale1 = get_scale(value_1);
  int scale2 = get_scale(value_2);

  if (scale1 - scale2 > 0) {
    scale2 = scale1 - scale2;
    scale1 = 0;
  } else {
    scale1 = scale2 - scale1;
    scale2 = 0;
  }

  s21_big_decimal remainder;
  s21_big_decimal delitel;
  s21_big_decimal big_result;
  reset_big_decimal_to_zero(&big_result);

  decimal_to_big_decimal(value_1, scale1, &remainder);
  decimal_to_big_decimal(value_2, scale2, &delitel);

  int scale = 0;

  while (is_big_decimal_zero(remainder)) {
    s21_decimal two = {{1, 0, 0, 0b00000000000000000000000000000000}};
    s21_big_decimal big_two;
    decimal_to_big_decimal(two, 0, &big_two);
    int q = 0;
    s21_big_decimal del = delitel;
    while (big_decimal_compare_absolute(remainder, del) == 1) {
      q++;
      del = shift_left(del, 1);
      if (big_decimal_compare_absolute(remainder, del) != 1) {
        q--;
      }
    }
    del = shift_left(delitel, q);
    s21_big_decimal shift_two = shift_left(big_two, q);
    big_decimal_add(big_result, shift_two, &big_result);
    big_decimal_add(remainder, invert_big_decimal(del), &remainder);
    if (!is_big_decimal_zero(remainder)) {
      break;
    }
    if (big_decimal_compare_absolute(remainder, delitel) == -1) {
      mul_to_ten_degree(&remainder, 1);
      mul_to_ten_degree(&big_result, 1);
      scale++;
    }
  }
  error = big_decimal_to_decimal(big_result, result);
  set_scale(result, scale);
  if (get_sign(value_1) == get_sign(value_2)) {
    set_sign(result, 0);
  } else {
    set_sign(result, 1);
  }
  return error;
}
int s21_negate(s21_decimal value, s21_decimal *result) {
  *result = value;
  result->bits[3] ^= MINUS;
  return 0;
}
*/
// s21_big_decimal div_get_remainder(s21_big_decimal number,
//                                   s21_big_decimal delitel,
//                                   s21_big_decimal *integer_result) {
//   while (big_decimal_compare_absolute(number, delitel) >= 0) {
//     s21_decimal two = {{1, 0, 0, 0b00000000000000000000000000000000}};
//     s21_big_decimal big_two;
//     decimal_to_big_decimal(two, 0, &big_two);
//     int q = 0;
//     s21_big_decimal del = delitel;
//     while (big_decimal_compare_absolute(number, del) == 1) {
//       q++;
//       del = shift_left(del, 1);
//       if (big_decimal_compare_absolute(number, del) != 1) {
//         q--;
//       }
//     }
//     del = shift_left(delitel, q);
//     s21_big_decimal shift_two = shift_left(big_two, q);
//     big_decimal_add(*integer_result, shift_two, integer_result);
//     big_decimal_add(number, invert_big_decimal(del), &number);
//   }

//   return number;
// }

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (is_decimal_zero(value_1) && !is_decimal_zero(value_2)) {
    *result = value_1;
    return 0;
  } else if (!is_decimal_zero(value_1) && is_decimal_zero(value_2)) {
    *result = value_2;
    return 0;
  }
  int error = 0;
  int scale1 = get_scale(value_1), scale2 = get_scale(value_2);
  int sign1 = get_sign(value_1), sign2 = get_sign(value_2);
  int res_sign = sign1 && sign2;
  int max_scale = 0;
  if (scale1 - scale2 > 0) {
    max_scale = scale1;
    scale2 = scale1 - scale2;
    scale1 = 0;
  } else {
    max_scale = scale2;
    scale1 = scale2 - scale1;
    scale2 = 0;
  }
  s21_big_decimal big_value_1, big_value_2, big_result;

  decimal_to_big_decimal(value_1, scale1, &big_value_1);
  decimal_to_big_decimal(value_2, scale2, &big_value_2);

  if (sign1 != sign2) {
    if (big_decimal_compare_absolute(big_value_1, big_value_2) == 1) {
      big_value_2 = invert_big_decimal(big_value_2);
      res_sign = sign1;
    } else {
      big_value_1 = invert_big_decimal(big_value_1);
      res_sign = sign2;
    }
  }

  big_decimal_add(big_value_1, big_value_2, &big_result);
  error = big_decimal_to_decimal(big_result, result);
  if (error) {
    s21_round_big_decimal(big_result, &max_scale, &big_result);
    error = big_decimal_to_decimal(big_result, result);
  }
  if (error) {
    if (res_sign == 1) {
      error = 2;
    }
  } else {
    set_scale(result, max_scale);
    set_sign(result, res_sign);
  }
  return error;
}
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = s21_negate(value_2, &value_2);
  if (error) {
    return s21_add(value_1, value_2, result);
  }
  return error;
}
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (is_decimal_zero(value_1) && !is_decimal_zero(value_2)) {
    *result = value_2;
    return 0;
  } else if (!is_decimal_zero(value_1) && is_decimal_zero(value_2)) {
    *result = value_1;
    return 0;
  }
  int error = 0;
  int sum_scale = get_scale(value_1) + get_scale(value_2);
  int res_sign = get_sign(value_1) == get_sign(value_2) ? 0 : 1;
  s21_big_decimal big_value_1, big_value_2, big_result;

  decimal_to_big_decimal(value_1, 0, &big_value_1);
  decimal_to_big_decimal(value_2, 0, &big_value_2);

  big_decimal_mul(big_value_1, big_value_2, &big_result);

  error = big_decimal_to_decimal(big_result, result);

  if (error) {
    s21_round_big_decimal(big_result, &sum_scale, &big_result);
    error = big_decimal_to_decimal(big_result, result);
  }
  if (error) {
    if (res_sign == 1) {
      error = 2;
    }
  } else {
    set_sign(result, res_sign);
    set_scale(result, sum_scale);
  }

  return error;
}
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!is_decimal_zero(value_1) && is_decimal_zero(value_2)) {
    *result = value_1;
    return 0;
  } else if (is_decimal_zero(value_1) && !is_decimal_zero(value_2)) {
    return 3;
  }
  int error = 0;
  int scale1 = get_scale(value_1), scale2 = get_scale(value_2);
  if (scale1 - scale2 > 0) {
    scale2 = scale1 - scale2;
    scale1 = 0;
  } else {
    scale1 = scale2 - scale1;
    scale2 = 0;
  }

  s21_big_decimal remainder, delitel, big_result;
  reset_big_decimal_to_zero(&big_result);

  decimal_to_big_decimal(value_1, scale1, &remainder);
  decimal_to_big_decimal(value_2, scale2, &delitel);
  int res_sign = get_sign(value_1) == get_sign(value_2) ? 0 : 1;
  int scale = 0;
  while (is_big_decimal_zero(remainder) && scale <= 29 &&
         big_result.bits[4] == 0) {
    remainder = div_get_remainder(remainder, delitel, &big_result);
    if (!is_big_decimal_zero(remainder)) {
      break;
    }
    if (big_decimal_compare_absolute(remainder, delitel) == -1) {
      mul_to_ten_degree(&remainder, 1);
      mul_to_ten_degree(&big_result, 1);
      scale++;
    }
  }
  error = big_decimal_to_decimal(big_result, result);
  if (error) {
    s21_round_big_decimal(big_result, &scale, &big_result);
    error = big_decimal_to_decimal(big_result, result);
  }
  if (error) {
    if (res_sign == 1) {
      error = 2;
    }
  } else {
    set_sign(result, res_sign);
    set_scale(result, scale);
  }
  return error;
}

s21_big_decimal div_get_remainder(s21_big_decimal number,
                                  s21_big_decimal delitel,
                                  s21_big_decimal *integer_result) {
  while (big_decimal_compare_absolute(number, delitel) >= 0) {
    s21_decimal two = {{1, 0, 0, 0b00000000000000000000000000000000}};
    s21_big_decimal big_two;
    decimal_to_big_decimal(two, 0, &big_two);
    int q = 0;
    s21_big_decimal del = delitel;
    while (big_decimal_compare_absolute(number, del) == 1) {
      q++;
      del = shift_left(del, 1);
      if (big_decimal_compare_absolute(number, del) != 1) {
        q--;
      }
    }
    del = shift_left(delitel, q);
    s21_big_decimal shift_two = shift_left(big_two, q);
    big_decimal_add(*integer_result, shift_two, integer_result);
    big_decimal_add(number, invert_big_decimal(del), &number);
  }
  return number;
}