#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "s21_matrix.h"

void init_test_matrix(matrix_t *mat, int rows, int columns, double start_value,
                      double step) {
  if (mat) {
    s21_create_matrix(rows, columns, mat);
    double value = start_value;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        mat->matrix[i][j] = value;
        value += step;
      }
    }
  }
}

int matrices_equal(matrix_t *A, matrix_t *B) {
  if (!A || !B || !A->matrix || !B->matrix) return 0;
  if (A->rows != B->rows || A->columns != B->columns) return 0;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) return 0;
    }
  }
  return 1;
}

START_TEST(test_create_matrix_valid) {
  matrix_t mat = {0};
  int res = s21_create_matrix(3, 4, &mat);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(mat.rows, 3);
  ck_assert_int_eq(mat.columns, 4);
  ck_assert_ptr_nonnull(mat.matrix);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq_tol(mat.matrix[i][j], 0.0, 1e-7);
    }
  }

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_matrix_invalid_rows) {
  matrix_t mat = {0};
  int res = s21_create_matrix(0, 5, &mat);
  ck_assert_int_eq(res, 1);
  ck_assert_ptr_null(mat.matrix);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_matrix_invalid_columns) {
  matrix_t mat = {0};
  int res = s21_create_matrix(5, -1, &mat);
  ck_assert_int_eq(res, 1);
  ck_assert_ptr_null(mat.matrix);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_matrix_null_result) {
  int res = s21_create_matrix(2, 2, NULL);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_create_matrix_large) {
  matrix_t mat = {0};
  int res = s21_create_matrix(100, 100, &mat);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(mat.rows, 100);
  ck_assert_int_eq(mat.columns, 100);
  ck_assert_ptr_nonnull(mat.matrix);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_remove_matrix_valid) {
  matrix_t mat = {0};
  s21_create_matrix(2, 2, &mat);

  s21_remove_matrix(&mat);
  ck_assert_ptr_null(mat.matrix);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_null) { s21_remove_matrix(NULL); }
END_TEST

START_TEST(test_remove_matrix_already_removed) {
  matrix_t mat = {0};
  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(test_eq_matrix_equal) {
  matrix_t A = {0}, B = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);
  init_test_matrix(&B, 2, 2, 1.0, 1.0);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_not_equal_values) {
  matrix_t A = {0}, B = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);
  init_test_matrix(&B, 2, 2, 1.0, 2.0);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_different_rows) {
  matrix_t A = {0}, B = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);
  init_test_matrix(&B, 3, 2, 1.0, 1.0);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_different_columns) {
  matrix_t A = {0}, B = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);
  init_test_matrix(&B, 2, 3, 1.0, 1.0);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_null_first) {
  matrix_t A = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);

  ck_assert_int_eq(s21_eq_matrix(NULL, &A), FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_eq_matrix_null_second) {
  matrix_t A = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);

  ck_assert_int_eq(s21_eq_matrix(&A, NULL), FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_eq_matrix_precision) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 1.0 + EPS / 2.0;
  B.matrix[0][0] = 1.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_valid) {
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);
  init_test_matrix(&B, 2, 2, 2.0, 2.0);
  init_test_matrix(&expected, 2, 2, 3.0, 3.0);

  int res = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sum_matrix_zeros) {
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 2, 0.0, 0.0);
  init_test_matrix(&B, 2, 2, 0.0, 0.0);
  init_test_matrix(&expected, 2, 2, 0.0, 0.0);

  int res = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sum_matrix_negative) {
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 2, 5.0, 1.0);
  init_test_matrix(&B, 2, 2, -3.0, -2.0);
  init_test_matrix(&expected, 2, 2, 2.0, -1.0);

  int res = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sum_matrix_different_rows) {
  matrix_t A = {0}, B = {0}, result = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);
  init_test_matrix(&B, 3, 2, 1.0, 1.0);

  int res = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_different_columns) {
  matrix_t A = {0}, B = {0}, result = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);
  init_test_matrix(&B, 2, 3, 1.0, 1.0);

  int res = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_null_A) {
  matrix_t B = {0}, result = {0};
  init_test_matrix(&B, 2, 2, 1.0, 1.0);

  int res = s21_sum_matrix(NULL, &B, &result);

  ck_assert_int_eq(res, 1);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_null_B) {
  matrix_t A = {0}, result = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);

  int res = s21_sum_matrix(&A, NULL, &result);

  ck_assert_int_eq(res, 1);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_null_result) {
  matrix_t A = {0}, B = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);
  init_test_matrix(&B, 2, 2, 1.0, 1.0);

  int res = s21_sum_matrix(&A, &B, NULL);

  ck_assert_int_eq(res, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_valid) {
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 2, 5.0, 1.0);
  init_test_matrix(&B, 2, 2, 2.0, 2.0);
  init_test_matrix(&expected, 2, 2, 3.0, -1.0);

  int res = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sub_matrix_zeros) {
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 2, 0.0, 0.0);
  init_test_matrix(&B, 2, 2, 0.0, 0.0);
  init_test_matrix(&expected, 2, 2, 0.0, 0.0);

  int res = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_sub_matrix_negative_result) {
  matrix_t A = {0}, B = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 2, 2.0, 1.0);
  init_test_matrix(&B, 2, 2, 5.0, 2.0);
  init_test_matrix(&expected, 2, 2, -3.0, -1.0);

  int res = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mult_number_valid) {
  matrix_t A = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 2, 1.0, 2.0);
  init_test_matrix(&expected, 2, 2, 2.0, 4.0);

  int res = s21_mult_number(&A, 2.0, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mult_number_zero) {
  matrix_t A = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 2, 1.0, 2.0);
  init_test_matrix(&expected, 2, 2, 0.0, 0.0);

  int res = s21_mult_number(&A, 0.0, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mult_number_negative) {
  matrix_t A = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 2, 1.0, 2.0);
  init_test_matrix(&expected, 2, 2, -2.0, -4.0);

  int res = s21_mult_number(&A, -2.0, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_mult_number_null_A) {
  matrix_t result = {0};

  int res = s21_mult_number(NULL, 2.0, &result);

  ck_assert_int_eq(res, 1);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_null_result) {
  matrix_t A = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);

  int res = s21_mult_number(&A, 2.0, NULL);

  ck_assert_int_eq(res, 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_matrix_valid) {
  matrix_t A = {0}, B = {0}, result = {0};
  init_test_matrix(&A, 2, 3, 1.0, 1.0);
  init_test_matrix(&B, 3, 2, 2.0, 0.5);

  int res = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);
  ck_assert_double_eq_tol(result.matrix[0][0], 20.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 23.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 47.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 54.5, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_identity) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 1;

  init_test_matrix(&B, 2, 2, 1.0, 1.0);

  int res = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &B));

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_matrix_incompatible) {
  matrix_t A = {0}, B = {0}, result = {0};
  init_test_matrix(&A, 2, 3, 1.0, 1.0);
  init_test_matrix(&B, 2, 2, 1.0, 1.0);

  int res = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(res, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_valid) {
  matrix_t A = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 3, 1.0, 1.0);
  s21_create_matrix(3, 2, &expected);

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 4;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 5;
  expected.matrix[2][0] = 3;
  expected.matrix[2][1] = 6;

  int res = s21_transpose(&A, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_transpose_square) {
  matrix_t A = {0}, result = {0}, expected = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);
  init_test_matrix(&expected, 2, 2, 1.0, 2.0);

  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = 3;
  expected.matrix[1][0] = 2;
  expected.matrix[1][1] = 4;

  int res = s21_transpose(&A, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_transpose_null_A) {
  matrix_t result = {0};

  int res = s21_transpose(NULL, &result);

  ck_assert_int_eq(res, 1);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_null_result) {
  matrix_t A = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);

  int res = s21_transpose(&A, NULL);

  ck_assert_int_eq(res, 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_1x1) {
  matrix_t A = {0};
  init_test_matrix(&A, 1, 1, 5.0, 0.0);
  double det = 0;

  int res = s21_determinant(&A, &det);

  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(det, 5.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_2x2) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  double det = 0;

  int res = s21_determinant(&A, &det);

  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(det, -2.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_3x3) {
  matrix_t A = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 3;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 7;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 1;
  A.matrix[2][0] = 9;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  double det = 0;
  int res = s21_determinant(&A, &det);

  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(det, -12.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_zero) {
  matrix_t A = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;
  double det = 0;

  int res = s21_determinant(&A, &det);

  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(det, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_not_square) {
  matrix_t A = {0};
  init_test_matrix(&A, 2, 3, 1.0, 1.0);
  double det = 0;

  int res = s21_determinant(&A, &det);

  ck_assert_int_eq(res, 2);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_determinant_null_A) {
  double det = 0;
  int res = s21_determinant(NULL, &det);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_determinant_null_result) {
  matrix_t A = {0};
  init_test_matrix(&A, 2, 2, 1.0, 1.0);

  int res = s21_determinant(&A, NULL);
  ck_assert_int_eq(res, 1);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_2x2) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  expected.matrix[0][0] = 4;
  expected.matrix[0][1] = -3;
  expected.matrix[1][0] = -2;
  expected.matrix[1][1] = 1;

  int res = s21_calc_complements(&A, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_calc_complements_3x3) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  int res = s21_calc_complements(&A, &result);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_not_square) {
  matrix_t A = {0}, result = {0};
  init_test_matrix(&A, 2, 3, 1.0, 1.0);

  int res = s21_calc_complements(&A, &result);

  ck_assert_int_eq(res, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_1x1) {
  matrix_t A = {0}, result = {0};
  init_test_matrix(&A, 1, 1, 5.0, 0.0);

  int res = s21_calc_complements(&A, &result);

  ck_assert_int_eq(res, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_2x2) {
  matrix_t A = {0}, result = {0}, expected = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  expected.matrix[0][0] = 0.6;
  expected.matrix[0][1] = -0.7;
  expected.matrix[1][0] = -0.2;
  expected.matrix[1][1] = 0.4;

  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, 0);
  ck_assert(matrices_equal(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(test_inverse_matrix_3x3) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_singular) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;

  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_not_square) {
  matrix_t A = {0}, result = {0};
  init_test_matrix(&A, 2, 3, 1.0, 1.0);

  int res = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(res, 2);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_inverse_matrix_null_A) {
  matrix_t result = {0};

  int res = s21_inverse_matrix(NULL, &result);

  ck_assert_int_eq(res, 1);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&result);
}
END_TEST

Suite *s21_matrix_suite(void) {
  Suite *s = suite_create("s21_matrix");

  TCase *tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_create_matrix_valid);
  tcase_add_test(tc_core, test_create_matrix_invalid_rows);
  tcase_add_test(tc_core, test_create_matrix_invalid_columns);
  tcase_add_test(tc_core, test_create_matrix_null_result);
  tcase_add_test(tc_core, test_create_matrix_large);
  tcase_add_test(tc_core, test_remove_matrix_valid);
  tcase_add_test(tc_core, test_remove_matrix_null);
  tcase_add_test(tc_core, test_remove_matrix_already_removed);
  suite_add_tcase(s, tc_core);

  TCase *tc_eq = tcase_create("Comparison");
  tcase_add_test(tc_eq, test_eq_matrix_equal);
  tcase_add_test(tc_eq, test_eq_matrix_not_equal_values);
  tcase_add_test(tc_eq, test_eq_matrix_different_rows);
  tcase_add_test(tc_eq, test_eq_matrix_different_columns);
  tcase_add_test(tc_eq, test_eq_matrix_null_first);
  tcase_add_test(tc_eq, test_eq_matrix_null_second);
  tcase_add_test(tc_eq, test_eq_matrix_precision);
  suite_add_tcase(s, tc_eq);

  TCase *tc_arith = tcase_create("Arithmetic");
  tcase_add_test(tc_arith, test_sum_matrix_valid);
  tcase_add_test(tc_arith, test_sum_matrix_zeros);
  tcase_add_test(tc_arith, test_sum_matrix_negative);
  tcase_add_test(tc_arith, test_sum_matrix_different_rows);
  tcase_add_test(tc_arith, test_sum_matrix_different_columns);
  tcase_add_test(tc_arith, test_sum_matrix_null_A);
  tcase_add_test(tc_arith, test_sum_matrix_null_B);
  tcase_add_test(tc_arith, test_sum_matrix_null_result);
  tcase_add_test(tc_arith, test_sub_matrix_valid);
  tcase_add_test(tc_arith, test_sub_matrix_zeros);
  tcase_add_test(tc_arith, test_sub_matrix_negative_result);
  tcase_add_test(tc_arith, test_mult_number_valid);
  tcase_add_test(tc_arith, test_mult_number_zero);
  tcase_add_test(tc_arith, test_mult_number_negative);
  tcase_add_test(tc_arith, test_mult_number_null_A);
  tcase_add_test(tc_arith, test_mult_number_null_result);
  tcase_add_test(tc_arith, test_mult_matrix_valid);
  tcase_add_test(tc_arith, test_mult_matrix_identity);
  tcase_add_test(tc_arith, test_mult_matrix_incompatible);
  suite_add_tcase(s, tc_arith);

  TCase *tc_matrix = tcase_create("Matrix Operations");
  tcase_add_test(tc_matrix, test_transpose_valid);
  tcase_add_test(tc_matrix, test_transpose_square);
  tcase_add_test(tc_matrix, test_transpose_null_A);
  tcase_add_test(tc_matrix, test_transpose_null_result);
  suite_add_tcase(s, tc_matrix);

  TCase *tc_alg = tcase_create("Algebra");
  tcase_add_test(tc_alg, test_determinant_1x1);
  tcase_add_test(tc_alg, test_determinant_2x2);
  tcase_add_test(tc_alg, test_determinant_3x3);
  tcase_add_test(tc_alg, test_determinant_zero);
  tcase_add_test(tc_alg, test_determinant_not_square);
  tcase_add_test(tc_alg, test_determinant_null_A);
  tcase_add_test(tc_alg, test_determinant_null_result);
  tcase_add_test(tc_alg, test_calc_complements_2x2);
  tcase_add_test(tc_alg, test_calc_complements_3x3);
  tcase_add_test(tc_alg, test_calc_complements_not_square);
  tcase_add_test(tc_alg, test_calc_complements_1x1);
  tcase_add_test(tc_alg, test_inverse_matrix_2x2);
  tcase_add_test(tc_alg, test_inverse_matrix_3x3);
  tcase_add_test(tc_alg, test_inverse_matrix_singular);
  tcase_add_test(tc_alg, test_inverse_matrix_not_square);
  tcase_add_test(tc_alg, test_inverse_matrix_null_A);
  suite_add_tcase(s, tc_alg);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_matrix_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}