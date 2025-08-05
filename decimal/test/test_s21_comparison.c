#include "test_s21_decimal.h"

// #include <check.h>
// #include <limits.h>
// #include <stdlib.h>

// #include "s21_comparison.h"
// #include "s21_function.h"

START_TEST(test_decimal_init_zero) {
  s21_decimal dec;
  reset_decimal_to_zero(&dec);
  ck_assert_uint_eq(dec.bits[0], 0);
  ck_assert_uint_eq(dec.bits[1], 0);
  ck_assert_uint_eq(dec.bits[2], 0);
  ck_assert_uint_eq(dec.bits[3], 0);
}
END_TEST

START_TEST(test_big_decimal_init_zero) {
  s21_big_decimal big;
  reset_big_decimal_to_zero(&big);
  for (int i = 0; i < 8; i++) {
    ck_assert_uint_eq(big.bits[i], 0);
  }
}
END_TEST

START_TEST(test_bit_operations) {
  s21_decimal dec;
  reset_decimal_to_zero(&dec);

  for (int i = 0; i < 32; i++) {
    set_bit(&dec, i, 1);
    ck_assert_int_eq(get_bit(dec, i), 1);
    set_bit(&dec, i, 0);
    ck_assert_int_eq(get_bit(dec, i), 0);
  }
}
END_TEST

START_TEST(test_big_bit_operations) {
  s21_big_decimal big;
  reset_big_decimal_to_zero(&big);

  big_set_bit(&big, 0, 1);
  ck_assert_int_eq(big_get_bit(big, 0), 1);

  big_set_bit(&big, 255, 1);
  ck_assert_int_eq(big_get_bit(big, 255), 1);
}
END_TEST

START_TEST(test_sign_operations) {
  s21_decimal dec;
  reset_decimal_to_zero(&dec);

  set_sign(&dec, 1);
  ck_assert_int_eq(get_sign(dec), 1);

  set_sign(&dec, 0);
  ck_assert_int_eq(get_sign(dec), 0);
}
END_TEST

START_TEST(test_scale_operations) {
  s21_decimal dec;
  reset_decimal_to_zero(&dec);

  for (int scale = 0; scale <= 28; scale++) {
    set_scale(&dec, scale);
    ck_assert_int_eq(get_scale(dec), scale);
  }
}
END_TEST

START_TEST(test_add_basic) {
  s21_big_decimal a = {{5, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal b = {{3, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal res;

  big_decimal_add(a, b, &res);
  ck_assert_uint_eq(res.bits[0], 8);
}
END_TEST

START_TEST(test_add_with_carry) {
  s21_big_decimal a = {{UINT_MAX, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal b = {{1, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal res;

  big_decimal_add(a, b, &res);
  ck_assert_uint_eq(res.bits[0], 0);
  ck_assert_uint_eq(res.bits[1], 1);
}
END_TEST

START_TEST(test_mul_basic) {
  s21_big_decimal a = {{5, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal b = {{3, 0, 0, 0, 0, 0, 0, 0}};
  s21_big_decimal res;

  big_decimal_mul(a, b, &res);
  ck_assert_uint_eq(res.bits[0], 15);
}
END_TEST

END_TEST

START_TEST(test_mul_by_10) {
  s21_big_decimal val = {{1, 0, 0, 0, 0, 0, 0, 0}};

  mul_to_ten_degree(&val, 1);
  ck_assert_uint_eq(val.bits[0], 10);

  mul_to_ten_degree(&val, 1);
  ck_assert_uint_eq(val.bits[0], 100);
}
END_TEST

START_TEST(test_convert_decimal_to_big) {
  s21_decimal dec = {{123, 456, 789, 0}};
  s21_big_decimal big;

  decimal_to_big_decimal(dec, 0, &big);
  ck_assert_uint_eq(big.bits[0], 123);
  ck_assert_uint_eq(big.bits[1], 456);
  ck_assert_uint_eq(big.bits[2], 789);
}
END_TEST

START_TEST(test_convert_big_to_decimal) {
  s21_big_decimal big = {{123, 456, 789, 0, 0, 0, 0, 0}};
  s21_decimal dec;

  ck_assert_int_eq(big_decimal_to_decimal(big, &dec), 0);
  ck_assert_uint_eq(dec.bits[0], 123);
  ck_assert_uint_eq(dec.bits[1], 456);
  ck_assert_uint_eq(dec.bits[2], 789);
}
END_TEST

START_TEST(test_convert_overflow) {
  s21_big_decimal big = {{0, 0, 0, 1, 0, 0, 0, 0}};
  s21_decimal dec;

  ck_assert_int_eq(big_decimal_to_decimal(big, &dec), 1);
}
END_TEST

START_TEST(test_comparison_equal) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, 0}};

  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_comparison_unequal) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{456, 0, 0, 0}};

  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_comparison_greater) {
  s21_decimal a = {{456, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, 0}};

  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_comparison_less) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{456, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_comparison_with_sign) {
  s21_decimal pos = {{123, 0, 0, 0}};
  s21_decimal neg = {{123, 0, 0, 0x80000000}};

  ck_assert_int_eq(s21_is_greater(pos, neg), 1);
  ck_assert_int_eq(s21_is_less(neg, pos), 1);
}
END_TEST

START_TEST(test_comparison_equal_different_scale) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  set_scale(&a, 2);
  set_scale(&b, 0);

  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_comparison_zero_negative_vs_positive) {
  s21_decimal a = {{0, 0, 0, 0x80000000}};
  s21_decimal b = {{0, 0, 0, 0x00000000}};

  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_comparison_negative_greater) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};
  s21_decimal b = {{2, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 1);
}
END_TEST

START_TEST(test_comparison_zero_and_small_negative) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal small_neg = {{1, 0, 0, 0x80000000}};

  ck_assert_int_eq(s21_is_greater(zero, small_neg), 1);
  ck_assert_int_eq(s21_is_less(small_neg, zero), 1);
}
END_TEST

START_TEST(test_comparison_large_numbers_equal) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = a;

  set_scale(&a, 5);
  set_scale(&b, 5);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_comparison_large_numbers_not_equal) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = a;

  set_scale(&a, 5);
  set_scale(&b, 6);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_compare_absolute_large_numbers) {
  s21_big_decimal num = {{0x7FFFFFFF}};
  s21_big_decimal del = {{0x9C400000}};

  int result = big_decimal_compare_absolute(num, del);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_compare_max_uint32) {
  s21_decimal max_val = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal near_max = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  ck_assert_int_eq(s21_is_greater(max_val, near_max), 1);
  ck_assert_int_eq(s21_is_less(near_max, max_val), 1);
}
END_TEST

START_TEST(test_compare_min_scale) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{12300, 0, 0, 0x00020000}};

  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_compare_max_scale) {
  s21_decimal a = {{123, 0, 0, 0x001C0000}};
  s21_decimal b = {{123000, 0, 0, 0x001E0000}};

  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_compare_special_zero_cases) {
  s21_decimal pos_zero = {{0, 0, 0, 0}};
  s21_decimal neg_zero = {{0, 0, 0, 0x80000000}};
  s21_decimal one = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_is_equal(pos_zero, neg_zero), 1);
  ck_assert_int_eq(s21_is_less_or_equal(neg_zero, pos_zero), 1);
  ck_assert_int_eq(s21_is_greater(one, pos_zero), 1);
  ck_assert_int_eq(s21_is_less(neg_zero, one), 1);
}
END_TEST

START_TEST(test_compare_denormal_values) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};
  s21_decimal b = {{10, 0, 0, 0x001C0000}};

  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_greater(b, a), 1);
}
END_TEST

START_TEST(test_compare_infinity_like) {
  s21_decimal max_pos = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal max_neg = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  ck_assert_int_eq(s21_is_greater(max_pos, max_neg), 1);
  ck_assert_int_eq(s21_is_less(max_neg, max_pos), 1);
}
END_TEST

START_TEST(test_compare_with_overflow) {
  s21_decimal almost_max = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal one = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_is_greater(almost_max, one), 1);
  ck_assert_int_eq(s21_is_less(one, almost_max), 1);
}
END_TEST

START_TEST(test_compare_big_differences) {
  s21_decimal small = {{1, 0, 0, 0x001C0000}};
  s21_decimal huge = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};

  ck_assert_int_eq(s21_is_less(small, huge), 1);
  ck_assert_int_eq(s21_is_greater(huge, small), 1);
}
END_TEST

START_TEST(test_compare_equal_high_bits) {
  s21_decimal a = {{0, 0xFFFFFFFF, 0, 0}};
  s21_decimal b = {{0, 0xFFFFFFFF, 0, 0}};

  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_compare_different_sign_equal_value) {
  s21_decimal pos = {{12345, 0, 0, 0}};
  s21_decimal neg = {{12345, 0, 0, 0x80000000}};

  ck_assert_int_eq(s21_is_equal(pos, neg), 0);
  ck_assert_int_eq(s21_is_greater(pos, neg), 1);
}
END_TEST

START_TEST(test_compare_bit_overflow) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal one = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_is_equal(max, one), 0);
  ck_assert_int_eq(s21_is_greater(max, one), 1);
  ck_assert_int_eq(s21_is_less(one, max), 1);
}
END_TEST

START_TEST(test_compare_different_scales) {
  s21_decimal a = {{123456, 0, 0, 0x00050000}};
  s21_decimal b = {{123456000, 0, 0, 0x00080000}};

  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(b, a), 1);
}
END_TEST

START_TEST(test_compare_max_scale_edge) {
  s21_decimal a = {{1, 0, 0, 0x001C0000}};
  s21_decimal b = {{100000, 0, 0, 0x001C0000}};

  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_greater(b, a), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_compare_negative_with_scales) {
  s21_decimal a = {{12345, 0, 0, 0x80020000}};
  s21_decimal b = {{1234500, 0, 0, 0x80040000}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(b, a), 1);
}
END_TEST

START_TEST(test_compare_with_zero_extreme) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal almost_zero = {{1, 0, 0, 0x001C0000}};
  s21_decimal small_neg = {{1, 0, 0, 0x801C0000}};

  ck_assert_int_eq(s21_is_greater(almost_zero, zero), 1);
  ck_assert_int_eq(s21_is_less(small_neg, zero), 1);
  ck_assert_int_eq(s21_is_not_equal(almost_zero, zero), 1);
}
END_TEST

START_TEST(test_compare_bit_manipulation) {
  s21_decimal a = {{0xAAAAAAAA, 0x55555555, 0xAAAAAAAA, 0}};
  s21_decimal b = {{0x55555555, 0xAAAAAAAA, 0x55555555, 0}};

  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_compare_special_bit_patterns) {
  s21_decimal pattern1 = {{0xDEADBEEF, 0xCAFEBABE, 0x0BADF00D, 0}};
  s21_decimal pattern2 = {{0xBAADF00D, 0xDEADBEEF, 0xCAFEBABE, 0}};

  ck_assert_int_eq(s21_is_less(pattern1, pattern2), 1);
  ck_assert_int_eq(s21_is_greater(pattern2, pattern1), 1);
  ck_assert_int_eq(s21_is_not_equal(pattern1, pattern2), 1);
}
END_TEST

START_TEST(test_compare_max_scale_max_value) {
  s21_decimal max_scale = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal min_scale = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  ck_assert_int_eq(s21_is_less(max_scale, min_scale), 1);
  ck_assert_int_eq(s21_is_greater(min_scale, max_scale), 1);
}
END_TEST

START_TEST(test_normalization_edge_cases) {
  s21_decimal a = {{1, 0, 0, 0x00010000}};
  s21_decimal b = {{10, 0, 0, 0x00020000}};

  s21_big_decimal big_a, big_b;
  int norm_result = normalize_and_convert(a, b, &big_a, &big_b);

  ck_assert_int_eq(norm_result, 0);
  ck_assert_int_eq(big_decimal_compare_absolute(big_a, big_b), 0);
}
END_TEST

START_TEST(test_sign_comparison_edge) {
  s21_decimal max_pos = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal max_neg = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  ck_assert_int_eq(s21_is_less(max_neg, max_pos), 1);
  ck_assert_int_eq(s21_is_greater(max_pos, max_neg), 1);
  ck_assert_int_eq(s21_is_not_equal(max_pos, max_neg), 1);
}
END_TEST

START_TEST(test_near_equal_values) {
  s21_decimal a = {{123456789, 0, 0, 0x00050000}};
  s21_decimal b = {{123456788, 0, 0, 0x00050000}};

  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 1);
}
END_TEST

START_TEST(test_compare_with_shifted_bits) {
  s21_decimal base = {{0x1, 0, 0, 0}};
  s21_decimal shifted = {{0x1 << 31, 0, 0, 0}};

  ck_assert_int_eq(s21_is_less(base, shifted), 1);
  ck_assert_int_eq(s21_is_greater(shifted, base), 1);
}
END_TEST

START_TEST(test_sign_scale_combinations) {
  s21_decimal cases[] = {{{123, 0, 0, 0x80010000}},
                         {{123, 0, 0, 0x00010000}},
                         {{123, 0, 0, 0x80020000}},
                         {{123, 0, 0, 0x00020000}}};

  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 4; j++) {
      ck_assert_int_eq(s21_is_equal(cases[i], cases[j]), 0);
    }
  }
}
END_TEST

START_TEST(test_mixed_components_comparison) {
  s21_decimal val1 = {{0, 1, 0, 0}};
  s21_decimal val2 = {{0, 0, 1, 0}};
  s21_decimal val3 = {{0, 0, 0, 0x10000}};

  ck_assert_int_eq(s21_is_less(val1, val2), 1);
  ck_assert_int_eq(s21_is_greater(val2, val1), 1);
  ck_assert_int_eq(s21_is_not_equal(val3, val1), 1);
}
END_TEST

START_TEST(test_extreme_value_difference) {
  s21_decimal tiny = {{1, 0, 0, 0x001C0000}};
  s21_decimal huge = {{0, 1, 0, 0}};

  ck_assert_int_eq(s21_is_less(tiny, huge), 1);
  ck_assert_int_eq(s21_is_greater(huge, tiny), 1);
  ck_assert_int_eq(s21_is_not_equal(tiny, huge), 1);
}
END_TEST

Suite *decimal_suite() {
  Suite *s = suite_create("\033[33m S21_COMPARISON \033[0m");
  TCase *tc_core = tcase_create("\033[31m test s21_comparison \033[0m");

  tcase_add_test(tc_core, test_decimal_init_zero);
  tcase_add_test(tc_core, test_big_decimal_init_zero);
  tcase_add_test(tc_core, test_bit_operations);
  tcase_add_test(tc_core, test_big_bit_operations);
  tcase_add_test(tc_core, test_sign_operations);
  tcase_add_test(tc_core, test_scale_operations);

  tcase_add_test(tc_core, test_add_basic);
  tcase_add_test(tc_core, test_add_with_carry);
  tcase_add_test(tc_core, test_mul_basic);
  tcase_add_test(tc_core, test_mul_by_10);

  tcase_add_test(tc_core, test_convert_decimal_to_big);
  tcase_add_test(tc_core, test_convert_big_to_decimal);
  tcase_add_test(tc_core, test_convert_overflow);

  tcase_add_test(tc_core, test_comparison_equal);
  tcase_add_test(tc_core, test_comparison_unequal);
  tcase_add_test(tc_core, test_comparison_greater);
  tcase_add_test(tc_core, test_comparison_less);
  tcase_add_test(tc_core, test_comparison_with_sign);
  tcase_add_test(tc_core, test_compare_absolute_large_numbers);
  tcase_add_test(tc_core, test_comparison_equal_different_scale);
  tcase_add_test(tc_core, test_comparison_zero_negative_vs_positive);
  tcase_add_test(tc_core, test_comparison_negative_greater);
  tcase_add_test(tc_core, test_comparison_zero_and_small_negative);
  tcase_add_test(tc_core, test_comparison_large_numbers_equal);
  tcase_add_test(tc_core, test_comparison_large_numbers_not_equal);

  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, test_compare_max_uint32);
  tcase_add_test(tc_core, test_compare_min_scale);
  tcase_add_test(tc_core, test_compare_max_scale);
  tcase_add_test(tc_core, test_compare_special_zero_cases);
  tcase_add_test(tc_core, test_compare_denormal_values);
  tcase_add_test(tc_core, test_compare_infinity_like);
  tcase_add_test(tc_core, test_compare_with_overflow);
  tcase_add_test(tc_core, test_compare_big_differences);
  tcase_add_test(tc_core, test_compare_equal_high_bits);
  tcase_add_test(tc_core, test_compare_different_sign_equal_value);

  tcase_add_test(tc_core, test_compare_bit_overflow);
  tcase_add_test(tc_core, test_compare_different_scales);
  tcase_add_test(tc_core, test_compare_max_scale_edge);
  tcase_add_test(tc_core, test_compare_negative_with_scales);
  tcase_add_test(tc_core, test_compare_with_zero_extreme);
  tcase_add_test(tc_core, test_compare_bit_manipulation);
  tcase_add_test(tc_core, test_compare_special_bit_patterns);
  tcase_add_test(tc_core, test_compare_max_scale_max_value);

  tcase_add_test(tc_core, test_normalization_edge_cases);
  tcase_add_test(tc_core, test_sign_comparison_edge);
  tcase_add_test(tc_core, test_near_equal_values);
  tcase_add_test(tc_core, test_compare_with_shifted_bits);
  tcase_add_test(tc_core, test_sign_scale_combinations);
  tcase_add_test(tc_core, test_mixed_components_comparison);
  tcase_add_test(tc_core, test_extreme_value_difference);

  suite_add_tcase(s, tc_core);
  return s;
}
