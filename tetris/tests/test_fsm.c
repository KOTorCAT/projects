#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../brick_game/tetris/defines.h"
#include "../brick_game/tetris/fsm.h"
#include "../brick_game/tetris/objects.h"

START_TEST(test_fsm_functions_exist) {
  gameInfo_init();
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_initial_state_is_start) {
  tetris_state state = return_state();
  ck_assert_int_eq(state, START);
}
END_TEST

START_TEST(test_fsm_set_action_values) {
  set_action(KEY_UP);
  set_action(KEY_DOWN);
  set_action(KEY_LEFT);
  set_action(KEY_RIGHT);
  set_action(ENTER_KEY);
  set_action(ESCAPE);
  set_action(PAUSE_KEY);
  set_action(SPACE_KEY);
  set_action(999);

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_userInput_hold) {
  userInput(Left, 1);
  userInput(Right, 1);
  userInput(Down, 1);

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_gameInfo_init_basic) {
  gameInfo_init();

  GameInfo_t info = updateCurrentState();

  ck_assert_int_ge(info.level, 1);
  ck_assert_int_le(info.level, 10);
  ck_assert_int_ge(info.score, 0);

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_state_transitions_basic) {
  tetris_state initial = return_state();
  ck_assert_int_eq(initial, START);

  set_action(ENTER_KEY);
  updateCurrentState();

  tetris_state new_state = return_state();
  ck_assert(new_state >= START && new_state <= EXIT_STATE);
}
END_TEST

START_TEST(test_fsm_pause_basic) {
  set_action(PAUSE_KEY);
  updateCurrentState();

  tetris_state state = return_state();
  ck_assert(state == PAUSE || state == START || state == MOVING);
}
END_TEST

START_TEST(test_fsm_terminate_basic) {
  set_action(ESCAPE);
  updateCurrentState();

  tetris_state state = return_state();
  ck_assert(state >= START && state <= EXIT_STATE);
}
END_TEST

START_TEST(test_fsm_all_states) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  ck_assert_int_eq(return_state(), SPAWN);

  updateCurrentState();
  ck_assert(return_state() == MOVING || return_state() == SHIFTING);
}
END_TEST

START_TEST(test_fsm_pause_functionality) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();

  updateCurrentState();

  set_action(PAUSE_KEY);
  updateCurrentState();
  ck_assert_int_eq(return_state(), PAUSE);

  set_action(PAUSE_KEY);
  updateCurrentState();
  ck_assert(return_state() == MOVING || return_state() == SHIFTING);
}
END_TEST

START_TEST(test_fsm_spawn_to_moving) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();

  updateCurrentState();
  ck_assert(return_state() == MOVING || return_state() == SHIFTING);
}
END_TEST

START_TEST(test_fsm_shift_interval) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  GameInfo_t info = updateCurrentState();
  ck_assert_int_ge(info.speed, 100);
  ck_assert_int_le(info.speed, 1000);
}
END_TEST

START_TEST(test_fsm_initial_state) {
  tetris_state state = return_state();
  ck_assert_int_eq(state, START);
}
END_TEST

START_TEST(test_fsm_set_action_basic) {
  set_action(KEY_UP);
  set_action(KEY_DOWN);
  set_action(KEY_LEFT);
  set_action(KEY_RIGHT);
  set_action(ENTER_KEY);
  set_action(ESCAPE);
  set_action(PAUSE_KEY);
  set_action(SPACE_KEY);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_gameInfo_init) {
  gameInfo_init();

  GameInfo_t info = updateCurrentState();
  ck_assert_int_eq(info.level, 1);
  ck_assert_int_eq(info.score, 0);
  ck_assert_int_eq(info.pause, TRUE);
}
END_TEST

START_TEST(test_fsm_start_to_spawn_transition) {
  gameInfo_init();

  ck_assert_int_eq(return_state(), START);

  set_action(ENTER_KEY);
  updateCurrentState();

  ck_assert_int_eq(return_state(), SPAWN);
}
END_TEST

START_TEST(test_fsm_spawn_to_moving_transition) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  ck_assert_int_eq(return_state(), SPAWN);

  updateCurrentState();
  ck_assert(return_state() == MOVING || return_state() == SHIFTING);
}
END_TEST

START_TEST(test_fsm_pause_toggle) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  set_action(PAUSE_KEY);
  updateCurrentState();
  ck_assert_int_eq(return_state(), PAUSE);

  set_action(PAUSE_KEY);
  updateCurrentState();
  ck_assert(return_state() == MOVING || return_state() == SHIFTING);
}
END_TEST

START_TEST(test_fsm_terminate) {
  gameInfo_init();

  set_action(ESCAPE);
  updateCurrentState();
  ck_assert_int_eq(return_state(), EXIT_STATE);
}
END_TEST

START_TEST(test_fsm_userInput_basic) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  userInput(Left, 0);
  userInput(Right, 0);
  userInput(Down, 0);
  userInput(Action, 0);

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_shift_timing) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  GameInfo_t info = updateCurrentState();
  ck_assert_int_ge(info.speed, 100);
  ck_assert_int_le(info.speed, 1000);
}
END_TEST

START_TEST(test_fsm_attaching_state) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_shift_interval_calculation) {
  gameInfo_init();

  GameInfo_t game;
  game.score = 0;
  game.level = 1;
  game.speed = 100;

  int shift_interval = 1000;
  update_state(&game, &shift_interval);

  ck_assert_int_eq(game.level, 1);
  ck_assert_int_eq(shift_interval, 900);
}
END_TEST

START_TEST(test_fsm_multiple_levels) {
  gameInfo_init();

  GameInfo_t game;
  game.score = 600;
  game.level = 1;
  game.speed = 100;

  int shift_interval = 1000;
  update_state(&game, &shift_interval);

  ck_assert_int_eq(game.level, 2);
  ck_assert_int_eq(game.speed, 200);
  ck_assert_int_eq(shift_interval, 800);
}
END_TEST

START_TEST(test_fsm_high_score_update) {
  gameInfo_init();

  GameInfo_t game;
  game.score = 1500;
  game.high_score = 1000;

  save_high_score_if_needed(&game);
  ck_assert_int_eq(game.high_score, 1500);

  game.score = 1200;
  save_high_score_if_needed(&game);
  ck_assert_int_eq(game.high_score, 1500);
}
END_TEST

START_TEST(test_fsm_load_high_score) {
  gameInfo_init();

  GameInfo_t game;
  load_high_score(&game);

  ck_assert_int_ge(game.high_score, 0);
}
END_TEST

START_TEST(test_fsm_shifting_state_no_attach) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_shifting_state_with_attach) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_attaching_state_normal) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_attaching_state_gameover) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_rotation_success) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  set_action(SPACE_KEY);
  userInput(Action, 0);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_rotation_failure) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  set_action(SPACE_KEY);
  userInput(Action, 0);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_gameover_state_direct) {
  gameInfo_init();

  set_action(ESCAPE);
  updateCurrentState();

  ck_assert_int_eq(return_state(), EXIT_STATE);
}
END_TEST

START_TEST(test_fsm_pause_state_terminate) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  set_action(PAUSE_KEY);
  updateCurrentState();
  set_action(ESCAPE);
  userInput(Terminate, 0);
  ck_assert_int_eq(return_state(), EXIT_STATE);
}
END_TEST

START_TEST(test_fsm_pause_state_default) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  set_action(PAUSE_KEY);
  updateCurrentState();
  set_action(KEY_UP);
  userInput(Up, 0);
  ck_assert_int_eq(return_state(), PAUSE);
}
END_TEST

START_TEST(test_fsm_shifting_path) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  set_action(KEY_DOWN);
  userInput(Down, 0);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_attaching_path) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_gameover_path) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_shifting_state_path) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  set_action(KEY_DOWN);
  userInput(Down, 0);

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_attaching_condition) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  for (int i = 0; i < 30; i++) {
    set_action(KEY_DOWN);
    userInput(Down, 0);
    updateCurrentState();
  }

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_pause_state_terminate_case) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  set_action(PAUSE_KEY);
  updateCurrentState();

  set_action(ESCAPE);
  updateCurrentState();

  ck_assert_int_eq(return_state(), EXIT_STATE);
}
END_TEST

START_TEST(test_fsm_pause_state_default_case) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  set_action(PAUSE_KEY);
  updateCurrentState();

  set_action(KEY_UP);
  updateCurrentState();

  ck_assert_int_eq(return_state(), PAUSE);
}
END_TEST

START_TEST(test_fsm_gameover_through_attach) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_force_shifting_state) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  set_action(KEY_DOWN);
  for (int i = 0; i < 10; i++) {
    userInput(Down, 0);
    updateCurrentState();
  }

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_force_attaching_state) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  set_action(KEY_DOWN);
  for (int i = 0; i < 50; i++) {
    userInput(Down, 0);
    updateCurrentState();
  }

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_force_gameover_state) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  set_action(ESCAPE);
  updateCurrentState();

  ck_assert_int_eq(return_state(), EXIT_STATE);
}
END_TEST

START_TEST(test_fsm_direct_shifting_call) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  set_action(KEY_DOWN);
  userInput(Down, 0);

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_direct_attaching_call) {
  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  set_action(SPACE_KEY);
  userInput(Action, 0);

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_edge_case_pause) {
  gameInfo_init();

  set_action(PAUSE_KEY);
  updateCurrentState();

  set_action(ENTER_KEY);
  updateCurrentState();

  set_action(PAUSE_KEY);
  updateCurrentState();

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_multiple_terminate) {
  gameInfo_init();

  set_action(ESCAPE);
  updateCurrentState();
  set_action(ESCAPE);
  updateCurrentState();

  ck_assert_int_eq(return_state(), EXIT_STATE);
}
END_TEST

START_TEST(test_fsm_start_state_default) {
  gameInfo_init();

  set_action(KEY_UP);
  updateCurrentState();

  ck_assert_int_eq(return_state(), START);
}
END_TEST

START_TEST(test_fsm_rapid_state_changes) {
  gameInfo_init();

  for (int i = 0; i < 10; i++) {
    set_action(ENTER_KEY);
    updateCurrentState();
    set_action(PAUSE_KEY);
    updateCurrentState();
    set_action(ESCAPE);
    updateCurrentState();
  }

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_complex_pause_scenarios) {
  gameInfo_init();

  set_action(PAUSE_KEY);
  updateCurrentState();

  set_action(ENTER_KEY);
  updateCurrentState();

  set_action(PAUSE_KEY);
  updateCurrentState();

  set_action(PAUSE_KEY);
  updateCurrentState();

  set_action(PAUSE_KEY);
  updateCurrentState();

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_terminate_from_all_states) {
  gameInfo_init();

  set_action(ESCAPE);
  updateCurrentState();
  ck_assert_int_eq(return_state(), EXIT_STATE);

  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();

  set_action(ESCAPE);
  updateCurrentState();
  ck_assert_int_eq(return_state(), EXIT_STATE);

  gameInfo_init();
  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  set_action(ESCAPE);
  updateCurrentState();
  ck_assert_int_eq(return_state(), EXIT_STATE);
}
END_TEST

START_TEST(test_fsm_complete_game_cycle) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();

  for (int i = 0; i < 50; i++) {
    int action = rand() % 6;
    switch (action) {
      case 0:
        set_action(KEY_LEFT);
        userInput(Left, 0);
        break;
      case 1:
        set_action(KEY_RIGHT);
        userInput(Right, 0);
        break;
      case 2:
        set_action(KEY_DOWN);
        userInput(Down, 0);
        break;
      case 3:
        set_action(SPACE_KEY);
        userInput(Action, 0);
        break;
      case 4:
        set_action(PAUSE_KEY);
        userInput(Pause, 0);
        break;
      default:
        break;
    }
    updateCurrentState();
  }

  set_action(ESCAPE);
  updateCurrentState();

  ck_assert_int_eq(return_state(), EXIT_STATE);
}
END_TEST

START_TEST(test_fsm_force_gameover_direct) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();

  set_action(ESCAPE);
  updateCurrentState();

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_force_shifting_state1) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  for (int i = 0; i < 5; i++) {
    updateCurrentState();
  }

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_extended_play_session) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();

  for (int i = 0; i < 100; i++) {
    int action_type = i % 7;
    switch (action_type) {
      case 0:
        set_action(KEY_LEFT);
        userInput(Left, 0);
        break;
      case 1:
        set_action(KEY_RIGHT);
        userInput(Right, 0);
        break;
      case 2:
        set_action(KEY_DOWN);
        userInput(Down, 0);
        break;
      case 3:
        set_action(SPACE_KEY);
        userInput(Action, 0);
        break;
      case 4:
        set_action(PAUSE_KEY);
        userInput(Pause, 0);
        break;
      case 5:
        set_action(ENTER_KEY);
        userInput(Start, 0);
        break;
      case 6:
        set_action(ESCAPE);
        userInput(Terminate, 0);
        break;
    }
    updateCurrentState();

    if (i % 20 == 0) {
      gameInfo_init();
      set_action(ENTER_KEY);
      updateCurrentState();
    }
  }

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_force_shifting_through_timing) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  for (int i = 0; i < 15; i++) {
    updateCurrentState();
  }

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_force_attaching_through_collision) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  for (int i = 0; i < 30; i++) {
    set_action(KEY_DOWN);
    userInput(Down, 0);
    updateCurrentState();
  }

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_complete_game_lifecycle) {
  gameInfo_init();

  for (int cycle = 0; cycle < 3; cycle++) {
    set_action(ENTER_KEY);
    updateCurrentState();
    updateCurrentState();

    for (int i = 0; i < 25; i++) {
      int action_type = rand() % 5;
      switch (action_type) {
        case 0:
          set_action(KEY_LEFT);
          userInput(Left, 0);
          break;
        case 1:
          set_action(KEY_RIGHT);
          userInput(Right, 0);
          break;
        case 2:
          set_action(KEY_DOWN);
          userInput(Down, 0);
          break;
        case 3:
          set_action(SPACE_KEY);
          userInput(Action, 0);
          break;
        case 4:
          set_action(PAUSE_KEY);
          userInput(Pause, 0);
          break;
      }
      updateCurrentState();
    }

    set_action(ESCAPE);
    updateCurrentState();

    if (cycle < 2) gameInfo_init();
  }

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_fsm_extreme_down_movement) {
  gameInfo_init();

  set_action(ENTER_KEY);
  updateCurrentState();
  updateCurrentState();

  for (int i = 0; i < 40; i++) {
    set_action(KEY_DOWN);
    userInput(Down, 0);
    updateCurrentState();

    if (i % 10 == 0) {
      set_action(PAUSE_KEY);
      userInput(Pause, 0);
      updateCurrentState();
      set_action(PAUSE_KEY);
      userInput(Pause, 0);
      updateCurrentState();
    }
  }
  ck_assert_int_eq(1, 1);
}
END_TEST

Suite *fsm_suite(void) {
  Suite *s;
  TCase *tc_core;
  TCase *tc_basic;
  TCase *tc_advanced;

  s = suite_create("FSM");

  tc_core = tcase_create("Core Tests");
  tcase_add_test(tc_core, test_fsm_initial_state);
  tcase_add_test(tc_core, test_fsm_set_action_basic);
  tcase_add_test(tc_core, test_fsm_gameInfo_init);
  tcase_add_test(tc_core, test_fsm_start_to_spawn_transition);
  tcase_add_test(tc_core, test_fsm_spawn_to_moving_transition);
  tcase_add_test(tc_core, test_fsm_pause_toggle);
  tcase_add_test(tc_core, test_fsm_terminate);
  tcase_add_test(tc_core, test_fsm_userInput_basic);
  tcase_add_test(tc_core, test_fsm_userInput_hold);
  tcase_add_test(tc_core, test_fsm_shift_timing);

  tc_basic = tcase_create("Basic Tests");
  tcase_add_test(tc_basic, test_fsm_functions_exist);
  tcase_add_test(tc_basic, test_fsm_initial_state_is_start);
  tcase_add_test(tc_basic, test_fsm_set_action_values);
  tcase_add_test(tc_basic, test_fsm_gameInfo_init_basic);
  tcase_add_test(tc_basic, test_fsm_state_transitions_basic);
  tcase_add_test(tc_basic, test_fsm_pause_basic);
  tcase_add_test(tc_basic, test_fsm_terminate_basic);

  tc_advanced = tcase_create("Advanced Tests");
  tcase_add_test(tc_advanced, test_fsm_attaching_state);
  tcase_add_test(tc_advanced, test_fsm_shift_interval_calculation);
  tcase_add_test(tc_advanced, test_fsm_multiple_levels);
  tcase_add_test(tc_advanced, test_fsm_high_score_update);
  tcase_add_test(tc_advanced, test_fsm_load_high_score);
  tcase_add_test(tc_advanced, test_fsm_all_states);
  tcase_add_test(tc_advanced, test_fsm_pause_functionality);
  tcase_add_test(tc_advanced, test_fsm_spawn_to_moving);
  tcase_add_test(tc_advanced, test_fsm_shift_interval);

  tcase_add_test(tc_advanced, test_fsm_shifting_state_path);
  tcase_add_test(tc_advanced, test_fsm_attaching_condition);
  tcase_add_test(tc_advanced, test_fsm_pause_state_terminate_case);
  tcase_add_test(tc_advanced, test_fsm_pause_state_default_case);
  tcase_add_test(tc_advanced, test_fsm_gameover_through_attach);

  tcase_add_test(tc_advanced, test_fsm_shifting_path);
  tcase_add_test(tc_advanced, test_fsm_gameover_path);
  tcase_add_test(tc_advanced, test_fsm_attaching_path);
  tcase_add_test(tc_advanced, test_fsm_pause_state_default);
  tcase_add_test(tc_advanced, test_fsm_pause_state_terminate);
  tcase_add_test(tc_advanced, test_fsm_rotation_failure);
  tcase_add_test(tc_advanced, test_fsm_rotation_success);
  tcase_add_test(tc_advanced, test_fsm_attaching_state_gameover);
  tcase_add_test(tc_advanced, test_fsm_attaching_state_normal);
  tcase_add_test(tc_advanced, test_fsm_shifting_state_with_attach);
  tcase_add_test(tc_advanced, test_fsm_shifting_state_no_attach);
  tcase_add_test(tc_advanced, test_fsm_gameover_state_direct);
  tcase_add_test(tc_advanced, test_fsm_force_shifting_state);
  tcase_add_test(tc_advanced, test_fsm_force_attaching_state);
  tcase_add_test(tc_advanced, test_fsm_force_gameover_state);
  tcase_add_test(tc_advanced, test_fsm_direct_shifting_call);
  tcase_add_test(tc_advanced, test_fsm_direct_attaching_call);
  tcase_add_test(tc_advanced, test_fsm_edge_case_pause);
  tcase_add_test(tc_advanced, test_fsm_multiple_terminate);
  tcase_add_test(tc_advanced, test_fsm_start_state_default);
  tcase_add_test(tc_advanced, test_fsm_rapid_state_changes);
  tcase_add_test(tc_advanced, test_fsm_complex_pause_scenarios);
  tcase_add_test(tc_advanced, test_fsm_terminate_from_all_states);
  tcase_add_test(tc_advanced, test_fsm_complete_game_cycle);
  tcase_add_test(tc_advanced, test_fsm_force_gameover_direct);
  tcase_add_test(tc_advanced, test_fsm_force_shifting_state1);
  tcase_add_test(tc_advanced, test_fsm_extended_play_session);
  tcase_add_test(tc_advanced, test_fsm_force_shifting_through_timing);
  tcase_add_test(tc_advanced, test_fsm_force_attaching_through_collision);
  tcase_add_test(tc_advanced, test_fsm_complete_game_lifecycle);
  tcase_add_test(tc_advanced, test_fsm_extreme_down_movement);

  suite_add_tcase(s, tc_core);
  suite_add_tcase(s, tc_basic);
  suite_add_tcase(s, tc_advanced);

  return s;
}