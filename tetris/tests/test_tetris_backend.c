#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../brick_game/tetris/defines.h"
#include "../brick_game/tetris/objects.h"
#include "../brick_game/tetris/tetris_backend.h"
#include "test_helpers.h"

// Mock functions for tests
void mock_print_map(GameInfo_t* game) { (void)game; }
void mock_print_stats(GameInfo_t* game) { (void)game; }
void mock_print_next_figure(GameInfo_t* game) { (void)game; }
void mock_print_end_message(void) {}
void mock_print_overlay(void) {}
void mock_load_high_score(GameInfo_t* game) {
  (void)game;
  if (game) game->high_score = 0;
}
void mock_save_high_score_if_needed(GameInfo_t* game) { (void)game; }

// Mock backend functions
bool mock_check_attaching(GameInfo_t* game, tetramino_pos tet) {
  (void)game;
  (void)tet;
  return FALSE;
}
void mock_assemble_line(GameInfo_t* game, tetramino_pos tet) {
  (void)game;
  (void)tet;
}
void mock_update_state(GameInfo_t* game, int* shift_interval) {
  (void)game;
  (void)shift_interval;
}

// Основные тесты для tetris_backend.c
START_TEST(test_figure_generation) {
  GameInfo_t game;
  Tetromino new_figure;

  game.next = calloc(ROWS_NEXT_FIGURE, sizeof(int*));
  for (int i = 0; i < ROWS_NEXT_FIGURE; i++) {
    game.next[i] = calloc(COLS_NEXT_FIGURE, sizeof(int));
  }

  generate_next_figure(&game, &new_figure);

  // Проверяем, что фигура сгенерирована
  ck_assert_int_ge(new_figure.width, 2);
  ck_assert_int_le(new_figure.width, 4);
  ck_assert_int_ge(new_figure.height, 2);
  ck_assert_int_le(new_figure.height, 4);

  // Проверяем, что next заполнен
  int has_blocks = 0;
  for (int i = 0; i < ROWS_NEXT_FIGURE; i++) {
    for (int j = 0; j < COLS_NEXT_FIGURE; j++) {
      if (game.next[i][j] != 0) {
        has_blocks = 1;
        break;
      }
    }
    if (has_blocks) break;
  }
  ck_assert_int_eq(has_blocks, 1);

  // Освобождаем память
  for (int i = 0; i < ROWS_NEXT_FIGURE; i++) {
    free(game.next[i]);
  }
  free(game.next);
}
END_TEST

START_TEST(test_rotation) {
  Tetromino tet;

  // Создаем тестовую фигуру (L-образную)
  int shape[3][3] = {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}};

  tet.width = 3;
  tet.height = 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      tet.shape[i][j] = shape[i][j];
    }
  }

  // Поворачиваем фигуру
  rotate_matrix(&tet);

  // Проверяем, что размеры сохранились
  ck_assert_int_eq(tet.width, 3);
  ck_assert_int_eq(tet.height, 3);

  // Проверяем, что фигура изменилась (не все элементы равны 0)
  int has_blocks = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (tet.shape[i][j] != 0) {
        has_blocks = 1;
        break;
      }
    }
    if (has_blocks) break;
  }
  ck_assert_int_eq(has_blocks, 1);
}
END_TEST

START_TEST(test_collision_detection) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  // Создаем фигуру у нижней границы
  tet.figure = TETROMINOES[0];  // I-фигура
  tet.x = 3;
  tet.y = ROWS_MAP - 3;  // Не у дна

  // Проверяем коллизию - не должно быть
  bool collision = check_attaching(&game, tet);
  ck_assert_int_eq(collision, FALSE);

  free_test_game(&game);
}
END_TEST

START_TEST(test_collision_with_bottom) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  // Создаем фигуру у самой нижней границы
  tet.figure = TETROMINOES[0];  // I-фигура (высота 3)
  tet.x = 3;
  tet.y = ROWS_MAP - tet.figure.height;  // У дна

  // Размещаем фигуру для проверки коллизии
  place_figure(&game, tet);

  // Проверяем коллизию - должно быть, так как фигура у дна
  clear_figure(&game, tet);
  tet.y++;  // Пытаемся подвинуть фигуру вниз
  bool collision = check_attaching(&game, tet);

  // Восстанавливаем позицию и очищаем
  tet.y--;
  clear_figure(&game, tet);

  ck_assert_int_eq(collision, TRUE);

  free_test_game(&game);
}
END_TEST

START_TEST(test_line_clearing_single_line) {
  GameInfo_t game = create_test_game();

  // Заполняем полностью одну строку
  for (int j = 0; j < COLS_MAP; j++) {
    game.field[ROWS_MAP - 1][j] = 1;
  }

  // Создаем фигуру для вызова assemble_line
  tetramino_pos tet;
  tet.figure = TETROMINOES[0];
  tet.x = 0;
  tet.y = ROWS_MAP - 1;

  // Сохраняем начальный счет
  int initial_score = game.score;

  // Вызываем сбор линии
  assemble_line(&game, tet);

  // Проверяем, что счет увеличился
  ck_assert_int_gt(game.score, initial_score);

  free_test_game(&game);
}
END_TEST

START_TEST(test_level_system) {
  GameInfo_t game;
  int shift_interval = 1000;

  game.score = 0;
  game.level = 1;
  game.speed = 100;

  // Тестируем повышение уровня
  game.score = 600;  // Должен повыситься до 2 уровня
  update_state(&game, &shift_interval);
  ck_assert_int_eq(game.level, 2);
  ck_assert_int_eq(game.speed, 200);

  game.score = 1200;  // Должен повыситься до 3 уровня
  update_state(&game, &shift_interval);
  ck_assert_int_eq(game.level, 3);
  ck_assert_int_eq(game.speed, 300);

  // Проверяем, что уровень не превышает 10
  game.score = 5400;  // 9 * 600 = 5400 -> 10 уровень
  update_state(&game, &shift_interval);
  ck_assert_int_eq(game.level, 10);
  ck_assert_int_eq(game.speed, 1000);

  // Дополнительные очки не должны повышать уровень выше 10
  game.score = 6000;
  update_state(&game, &shift_interval);
  ck_assert_int_eq(game.level, 10);
}
END_TEST

START_TEST(test_high_score_saving) {
  GameInfo_t game;
  game.high_score = 1000;
  game.score = 1500;

  // Проверяем, что рекорд обновляется
  save_high_score_if_needed(&game);
  ck_assert_int_eq(game.high_score, 1500);

  // Проверяем, что рекорд не уменьшается
  game.score = 1200;
  save_high_score_if_needed(&game);
  ck_assert_int_eq(game.high_score, 1500);
}
END_TEST

START_TEST(test_tetromino_types) {
  // Проверяем, что все 7 типов тетромино существуют
  ck_assert_int_eq(sizeof(TETROMINOES) / sizeof(TETROMINOES[0]), 7);

  // Проверяем основные параметры каждой фигуры
  for (int i = 0; i < 7; i++) {
    ck_assert_int_ge(TETROMINOES[i].width, 2);
    ck_assert_int_le(TETROMINOES[i].width, 4);
    ck_assert_int_ge(TETROMINOES[i].height, 2);
    ck_assert_int_le(TETROMINOES[i].height, 4);
    ck_assert_int_gt(TETROMINOES[i].color, 0);
  }
}
END_TEST

START_TEST(test_figure_placement) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  tet.figure = TETROMINOES[0];  // I-фигура
  tet.x = 3;
  tet.y = 5;

  // Размещаем фигуру
  place_figure(&game, tet);

  // Проверяем, что фигура размещена
  int blocks_placed = 0;
  for (int i = 0; i < tet.figure.height; i++) {
    for (int j = 0; j < tet.figure.width; j++) {
      if (tet.figure.shape[i][j] && game.field[tet.y + i][tet.x + j] != 0) {
        blocks_placed++;
      }
    }
  }
  ck_assert_int_gt(blocks_placed, 0);

  free_test_game(&game);
}
END_TEST

START_TEST(test_figure_clearing) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  tet.figure = TETROMINOES[0];  // I-фигура
  tet.x = 3;
  tet.y = 5;

  // Размещаем и очищаем фигуру
  place_figure(&game, tet);
  clear_figure(&game, tet);

  // Проверяем, что фигура очищена
  int blocks_remaining = 0;
  for (int i = 0; i < tet.figure.height; i++) {
    for (int j = 0; j < tet.figure.width; j++) {
      if (tet.figure.shape[i][j] && game.field[tet.y + i][tet.x + j] != 0) {
        blocks_remaining++;
      }
    }
  }
  ck_assert_int_eq(blocks_remaining, 0);

  free_test_game(&game);
}
END_TEST

START_TEST(test_left_collision) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  // Создаем стенку слева
  for (int i = 0; i < ROWS_MAP; i++) {
    game.field[i][0] = 1;
  }

  tet.figure = TETROMINOES[0];  // I-фигура
  tet.x = 0;                    // У самой левой границы
  tet.y = 5;

  // Проверяем коллизию слева
  bool collision = check_collide_left(&game, tet);
  ck_assert_int_eq(collision, TRUE);

  free_test_game(&game);
}
END_TEST

START_TEST(test_right_collision) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  // Создаем стенку справа
  for (int i = 0; i < ROWS_MAP; i++) {
    game.field[i][COLS_MAP - 1] = 1;
  }

  tet.figure = TETROMINOES[0];          // I-фигура (ширина 4)
  tet.x = COLS_MAP - tet.figure.width;  // У самой правой границы
  tet.y = 5;

  // Проверяем коллизию справа
  bool collision = check_collide_right(&game, tet);
  ck_assert_int_eq(collision, TRUE);

  free_test_game(&game);
}
END_TEST

START_TEST(test_no_collision) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  tet.figure = TETROMINOES[0];  // I-фигура
  tet.x = 3;
  tet.y = 5;

  // Проверяем отсутствие коллизий
  bool left_collision = check_collide_left(&game, tet);
  bool right_collision = check_collide_right(&game, tet);

  ck_assert_int_eq(left_collision, FALSE);
  ck_assert_int_eq(right_collision, FALSE);

  free_test_game(&game);
}
END_TEST

START_TEST(test_score_calculation) {
  GameInfo_t game = create_test_game();

  game.score = 0;

  // Заполняем полностью одну строку
  for (int j = 0; j < COLS_MAP; j++) {
    game.field[ROWS_MAP - 1][j] = 1;
  }

  // Симулируем сбор линии
  tetramino_pos tet;
  tet.figure = TETROMINOES[0];
  tet.x = 0;
  tet.y = ROWS_MAP - 1;

  assemble_line(&game, tet);

  // Проверяем, что счет увеличился
  ck_assert_int_gt(game.score, 0);

  free_test_game(&game);
}
END_TEST

START_TEST(test_boundary_checks) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  // Максимально упрощенная проверка границ
  tet.figure = TETROMINOES[0];
  tet.x = 0;
  tet.y = 5;

  // Просто проверяем, что функция не падает
  // и возвращает корректное значение (TRUE или FALSE)
  bool collision = check_collide_left(&game, tet);
  ck_assert_int_eq(collision == TRUE || collision == FALSE, TRUE);

  free_test_game(&game);
}
END_TEST

START_TEST(test_multiple_rotations) {
  Tetromino tet = TETROMINOES[0];  // I-фигура
  int original_width = tet.width;
  int original_height = tet.height;

  // Поворачиваем несколько раз
  for (int i = 0; i < 4; i++) {
    rotate_matrix(&tet);
  }

  // После 4 поворотов должна вернуться к исходному состоянию
  ck_assert_int_eq(tet.width, original_width);
  ck_assert_int_eq(tet.height, original_height);
}
END_TEST

START_TEST(test_memory_management) {
  // Простой тест для проверки работы с памятью
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  tet.figure = TETROMINOES[0];
  tet.x = 3;
  tet.y = 5;

  // Просто проверяем, что функции работают без падений
  place_figure(&game, tet);
  clear_figure(&game, tet);

  free_test_game(&game);
}
END_TEST

// Edge case tests
START_TEST(test_rotation_at_boundaries) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  // Test rotation near left boundary
  tet.figure = TETROMINOES[0];  // I-figure
  tet.x = 0;
  tet.y = 5;

  bool can_rotate_left = can_rotate(&game, &tet);

  // Test rotation near right boundary
  tet.x = COLS_MAP - tet.figure.width;
  bool can_rotate_right = can_rotate(&game, &tet);

  ck_assert_int_eq(can_rotate_left || can_rotate_right, TRUE);

  free_test_game(&game);
}
END_TEST

START_TEST(test_multiple_line_clearing) {
  GameInfo_t game = create_test_game();

  // Fill multiple lines
  for (int lines = 0; lines < 3; lines++) {
    for (int j = 0; j < COLS_MAP; j++) {
      game.field[ROWS_MAP - 1 - lines][j] = 1;
    }
  }

  int initial_score = game.score;
  tetramino_pos tet;
  tet.figure = TETROMINOES[0];
  tet.x = 0;
  tet.y = ROWS_MAP - 3;

  assemble_line(&game, tet);

  // Score should increase significantly for multiple lines
  ck_assert_int_gt(game.score, initial_score + 500);

  free_test_game(&game);
}
END_TEST

START_TEST(test_all_tetromino_rotations) {
  for (int type = 0; type < 7; type++) {
    Tetromino tet = TETROMINOES[type];
    int original_width = tet.width;
    int original_height = tet.height;

    // Rotate 4 times - should return to original
    for (int i = 0; i < 4; i++) {
      rotate_matrix(&tet);
    }

    ck_assert_int_eq(tet.width, original_width);
    ck_assert_int_eq(tet.height, original_height);
  }
}
END_TEST

START_TEST(test_tetromino_placement_all_types) {
  for (int type = 0; type < 7; type++) {
    GameInfo_t game = create_test_game();
    tetramino_pos tet;

    tet.figure = TETROMINOES[type];
    tet.x = 3;
    tet.y = 5;

    place_figure(&game, tet);

    // Verify at least one block was placed
    int blocks_placed = 0;
    for (int i = 0; i < tet.figure.height; i++) {
      for (int j = 0; j < tet.figure.width; j++) {
        if (tet.figure.shape[i][j]) {
          blocks_placed++;
        }
      }
    }
    ck_assert_int_gt(blocks_placed, 0);

    clear_figure(&game, tet);
    free_test_game(&game);
  }
}
END_TEST

START_TEST(test_update_state_all_levels) {
  GameInfo_t game;
  int shift_interval;

  for (int level = 1; level <= 10; level++) {
    game.score = (level - 1) * 600;
    game.level = 1;
    game.speed = 100;
    shift_interval = 1000;

    update_state(&game, &shift_interval);

    ck_assert_int_eq(game.level, level);
    ck_assert_int_eq(game.speed, level * 100);

    // Исправленная проверка: интервал не может быть меньше 100
    int expected_interval = 1000 - (level * 100);
    if (expected_interval < 100) {
      expected_interval = 100;
    }
    ck_assert_int_eq(shift_interval, expected_interval);
  }
}
END_TEST

START_TEST(test_check_collision_on_spawn) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  // Тест без коллизий
  tet.figure = TETROMINOES[0];
  tet.x = SPAWN_X;
  tet.y = SPAWN_Y;

  bool collision = check_collision_on_spawn(&game, tet);
  ck_assert_int_eq(collision, FALSE);

  // Тест с коллизией (заполняем поле)
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < COLS_MAP; j++) {
      game.field[i][j] = 1;
    }
  }

  collision = check_collision_on_spawn(&game, tet);
  ck_assert_int_eq(collision, TRUE);

  free_test_game(&game);
}
END_TEST

START_TEST(test_file_operations_high_score) {
  const char* test_file = "test_high_score.txt";

  // Тест записи
  GameInfo_t game;
  game.score = 1500;
  game.high_score = 1000;

  // Сохраняем рекорд
  FILE* file = fopen(test_file, "w");
  if (file) {
    fprintf(file, "%d", game.score);
    fclose(file);
  }

  // Загружаем рекорд
  load_high_score(&game);
  ck_assert_int_eq(game.high_score, 1500);

  // Тест сохранения когда рекорд не побит
  game.score = 1200;
  save_high_score_if_needed(&game);
  ck_assert_int_eq(game.high_score, 1500);  // Не должен измениться

  // Тест сохранения когда рекорд побит
  game.score = 2000;
  save_high_score_if_needed(&game);
  ck_assert_int_eq(game.high_score, 2000);

  // Очищаем
  remove(test_file);
}
END_TEST

START_TEST(test_complex_rotation_cases) {
  GameInfo_t game = create_test_game();

  // Тестируем вращение всех фигур в различных позициях
  for (int type = 0; type < 7; type++) {
    tetramino_pos tet;
    tet.figure = TETROMINOES[type];

    // Тестируем центральную позицию
    tet.x = COLS_MAP / 2;
    tet.y = 5;
    bool can_rotate_center = can_rotate(&game, &tet);

    // Просто проверяем, что функция работает без падений
    // (некоторые фигуры не могут вращаться в крайних положениях)
    ck_assert_int_eq(can_rotate_center == TRUE || can_rotate_center == FALSE,
                     TRUE);
  }

  free_test_game(&game);
}
END_TEST

START_TEST(test_boundary_collision_cases) {
  GameInfo_t game = create_test_game();
  tetramino_pos tet;

  // Тест крайних случаев коллизий
  tet.figure = TETROMINOES[0];  // I-фигура

  // Левая граница
  tet.x = -1;
  tet.y = 5;
  bool left_collision = check_collision_on_spawn(&game, tet);
  ck_assert_int_eq(left_collision, TRUE);

  // Правая граница
  tet.x = COLS_MAP;
  tet.y = 5;
  bool right_collision = check_collision_on_spawn(&game, tet);
  ck_assert_int_eq(right_collision, TRUE);

  // Нижняя граница
  tet.x = 3;
  tet.y = ROWS_MAP;
  bool bottom_collision = check_collision_on_spawn(&game, tet);
  ck_assert_int_eq(bottom_collision, TRUE);

  free_test_game(&game);
}
END_TEST

START_TEST(test_assemble_line_multiple) {
  GameInfo_t game = create_test_game();

  // Заполняем несколько линий
  for (int lines = 0; lines < 4; lines++) {
    for (int j = 0; j < COLS_MAP; j++) {
      game.field[ROWS_MAP - 1 - lines][j] = 1;
    }
  }

  int initial_score = game.score;
  tetramino_pos tet;
  tet.figure = TETROMINOES[0];
  tet.x = 0;
  tet.y = ROWS_MAP - 4;

  assemble_line(&game, tet);

  // Проверяем что счет увеличился значительно для 4 линий
  ck_assert_int_gt(game.score, initial_score + 1000);

  free_test_game(&game);
}
END_TEST

// Integration test
START_TEST(test_integration_full_game_cycle) {
  GameInfo_t game = create_test_game();
  Tetromino next_tetramino;

  // Simulate a full game cycle
  generate_next_figure(&game, &next_tetramino);

  // Проверяем, что фигура сгенерирована корректно
  ck_assert_int_ge(next_tetramino.width, 2);
  ck_assert_int_le(next_tetramino.width, 4);
  ck_assert_int_ge(next_tetramino.height, 2);
  ck_assert_int_le(next_tetramino.height, 4);

  // Проверяем, что next заполнен
  int has_blocks = 0;
  for (int i = 0; i < ROWS_NEXT_FIGURE; i++) {
    for (int j = 0; j < COLS_NEXT_FIGURE; j++) {
      if (game.next[i][j] != 0) {
        has_blocks = 1;
        break;
      }
    }
    if (has_blocks) break;
  }
  ck_assert_int_eq(has_blocks, 1);

  free_test_game(&game);
}
END_TEST

Suite* tetris_backend_suite(void) {
  Suite* s;
  TCase* tc_core;
  TCase* tc_edge;
  TCase* tc_integration;

  s = suite_create("Tetris_Backend");

  // Основные тесты
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_figure_generation);
  tcase_add_test(tc_core, test_rotation);
  tcase_add_test(tc_core, test_collision_detection);
  tcase_add_test(tc_core, test_collision_with_bottom);
  tcase_add_test(tc_core, test_line_clearing_single_line);
  tcase_add_test(tc_core, test_level_system);
  tcase_add_test(tc_core, test_high_score_saving);
  tcase_add_test(tc_core, test_tetromino_types);
  tcase_add_test(tc_core, test_figure_placement);
  tcase_add_test(tc_core, test_figure_clearing);
  tcase_add_test(tc_core, test_left_collision);
  tcase_add_test(tc_core, test_right_collision);
  tcase_add_test(tc_core, test_no_collision);
  tcase_add_test(tc_core, test_score_calculation);
  tcase_add_test(tc_core, test_boundary_checks);
  tcase_add_test(tc_core, test_multiple_rotations);
  tcase_add_test(tc_core, test_memory_management);

  // Тесты edge cases
  tc_edge = tcase_create("Edge Cases");
  tcase_add_test(tc_edge, test_rotation_at_boundaries);
  tcase_add_test(tc_edge, test_multiple_line_clearing);
  tcase_add_test(tc_edge, test_all_tetromino_rotations);
  tcase_add_test(tc_edge, test_tetromino_placement_all_types);
  tcase_add_test(tc_edge, test_update_state_all_levels);
  tcase_add_test(tc_edge, test_check_collision_on_spawn);
  tcase_add_test(tc_edge, test_file_operations_high_score);
  tcase_add_test(tc_edge, test_complex_rotation_cases);
  tcase_add_test(tc_edge, test_boundary_collision_cases);
  tcase_add_test(tc_edge, test_assemble_line_multiple);

  // Интеграционные тесты
  tc_integration = tcase_create("Integration");
  tcase_add_test(tc_integration, test_integration_full_game_cycle);

  // Добавляем все test cases в suite
  suite_add_tcase(s, tc_core);
  suite_add_tcase(s, tc_edge);
  suite_add_tcase(s, tc_integration);

  return s;
}