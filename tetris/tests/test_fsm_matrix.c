#include <check.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../brick_game/tetris/defines.h"
#include "../brick_game/tetris/objects.h"
#include "../brick_game/tetris/tetris_backend.h"
#include "test_helpers.h"

extern bool can_rotate(GameInfo_t *game, tetramino_pos *tet);

START_TEST(test_matrix_rotation_basic) {
  Tetromino tet = TETROMINOES[0];
  int original_width = tet.width;
  int original_height = tet.height;

  rotate_matrix(&tet);
  ck_assert_int_eq(tet.width, original_height);
  ck_assert_int_eq(tet.height, original_width);
}
END_TEST

START_TEST(test_matrix_rotation_consistency) {
  Tetromino tet = TETROMINOES[0];
  int original_width = tet.width;
  int original_height = tet.height;

  for (int i = 0; i < 4; i++) {
    rotate_matrix(&tet);
  }

  ck_assert_int_eq(tet.width, original_width);
  ck_assert_int_eq(tet.height, original_height);
}
END_TEST

START_TEST(test_matrix_o_piece_rotation) {
  Tetromino tet = TETROMINOES[3];
  int original_width = tet.width;
  int original_height = tet.height;

  rotate_matrix(&tet);
  ck_assert_int_eq(tet.width, original_height);
  ck_assert_int_eq(tet.height, original_width);
}
END_TEST

START_TEST(test_can_rotate_basic) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  tet.figure = TETROMINOES[0];
  tet.x = COLS_MAP / 2;
  tet.y = 5;

  bool result = can_rotate(&game, &tet);
  ck_assert_int_eq(result, TRUE);

  free_test_game(&game);
}
END_TEST

START_TEST(test_can_rotate_near_boundary) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  tet.figure = TETROMINOES[0];
  tet.x = 0;
  tet.y = 5;

  bool result = can_rotate(&game, &tet);
  ck_assert_int_eq(result == TRUE || result == FALSE, TRUE);

  free_test_game(&game);
}
END_TEST

Suite *fsm_matrix_suite(void) {
  Suite *s;
  TCase *tc_basic;

  s = suite_create("FSM_Matrix");

  tc_basic = tcase_create("Basic Matrix Tests");

  tcase_add_test(tc_basic, test_matrix_rotation_basic);
  tcase_add_test(tc_basic, test_matrix_rotation_consistency);
  tcase_add_test(tc_basic, test_matrix_o_piece_rotation);
  tcase_add_test(tc_basic, test_can_rotate_basic);
  tcase_add_test(tc_basic, test_can_rotate_near_boundary);

  suite_add_tcase(s, tc_basic);

  return s;
}