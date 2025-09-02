#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows < 1 || columns < 1 || result == NULL) return 1;

  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) return 1;

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) free(result->matrix[j]);
      free(result->matrix);
      result->matrix = NULL;
      return 1;
    }
  }
  return 0;
}

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      A->rows != B->rows || A->columns != B->columns)
    return FAILURE;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) return FAILURE;
    }
  }

  return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL)
    return 1;
  if (A->rows != B->rows || A->columns != B->columns) return 2;

  int res = s21_create_matrix(A->rows, A->columns, result);
  if (res != 0) return res;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return 0;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL)
    return 1;
  if (A->rows != B->rows || A->columns != B->columns) return 2;

  int res = s21_create_matrix(A->rows, A->columns, result);
  if (res != 0) return res;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return 0;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || A->matrix == NULL) return 1;

  int res = s21_create_matrix(A->rows, A->columns, result);
  if (res != 0) return res;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return 0;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return 1;
  }

  if (A->matrix == NULL || B->matrix == NULL) {
    return 1;
  }

  if (A->columns != B->rows) {
    return 2;
  }
  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    return 1;
  }

  int res = s21_create_matrix(A->rows, B->columns, result);
  if (res != 0) {
    return res;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return 0;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL) return 1;

  int res = s21_create_matrix(A->columns, A->rows, result);
  if (res != 0) return res;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return 0;
}

static void get_minor(matrix_t *A, int row, int col, matrix_t *minor) {
  s21_remove_matrix(minor);
  s21_create_matrix(A->rows - 1, A->columns - 1, minor);

  for (int i = 0, m_i = 0; i < A->rows; i++) {
    if (i == row) continue;
    for (int j = 0, m_j = 0; j < A->columns; j++) {
      if (j == col) continue;
      minor->matrix[m_i][m_j] = A->matrix[i][j];
      m_j++;
    }
    m_i++;
  }
}

static double calculate_determinant(matrix_t *A) {
  if (A->rows == 1) return A->matrix[0][0];
  if (A->rows == 2)
    return A->matrix[0][0] * A->matrix[1][1] -
           A->matrix[0][1] * A->matrix[1][0];

  double det = 0;
  for (int j = 0; j < A->columns; j++) {
    matrix_t minor = {0};
    get_minor(A, 0, j, &minor);
    det += A->matrix[0][j] * pow(-1, j) * calculate_determinant(&minor);
    s21_remove_matrix(&minor);
  }
  return det;
}

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || A->matrix == NULL || result == NULL) return 1;
  if (A->rows != A->columns) return 2;

  *result = calculate_determinant(A);
  return 0;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL) return 1;
  if (A->rows != A->columns) return 2;

  int res = s21_create_matrix(A->rows, A->columns, result);
  if (res != 0) return res;

  if (A->rows == 1) {
    result->matrix[0][0] = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor = {0};
        get_minor(A, i, j, &minor);
        double det = calculate_determinant(&minor);
        result->matrix[i][j] = pow(-1, i + j) * det;
        s21_remove_matrix(&minor);
      }
    }
  }

  return 0;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL) return 1;
  if (A->rows != A->columns) return 2;

  double det = 0;
  int det_status = s21_determinant(A, &det);
  if (det_status != 0 || fabs(det) < EPS) return 2;

  matrix_t complements = {0}, transposed = {0};
  int comp_status = s21_calc_complements(A, &complements);
  if (comp_status != 0) {
    return comp_status;
  }

  int trans_status = s21_transpose(&complements, &transposed);
  if (trans_status != 0) {
    s21_remove_matrix(&complements);
    return trans_status;
  }

  s21_mult_number(&transposed, 1.0 / det, result);
  s21_remove_matrix(&complements);
  s21_remove_matrix(&transposed);

  return 0;
}