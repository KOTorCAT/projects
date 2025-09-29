#include "fsm.h"

#include "../../gui/cli/tetris_frontend.h"
#include "tetris_backend.h"

static tetris_state current_state = START;
static GameInfo_t game;
static UserAction_t action = -1;

static tetramino_pos current_tetramino;
static Tetromino next_tetramino;

static clock_t last_shift_time = 0;
static int shift_interval = 1000;

void on_start_state();
void on_spawn_state();
void on_shifting_state();
void on_attaching_state();
void on_pause_state();
void on_gameover_state();
void moveleft();
void moveright();
void movedown();
void rotation();

void gameInfo_init() {
  game.level = 1;
  game.pause = TRUE;
  game.score = 0;
  game.speed = 100;
  load_high_score(&game);
  shift_interval = 1000;
  game.field = calloc(20, sizeof(int*));
  if (game.field) {
    for (int i = 0; i < 20; i++) {
      game.field[i] = calloc(10, sizeof(int));
      for (int j = 0; j < 10; j++) {
        game.field[i][j] = 0;
      }
    }
  }
  game.next = calloc(4, sizeof(int*));
  if (game.next) {
    for (int i = 0; i < 4; i++) {
      game.next[i] = calloc(4, sizeof(int));
      for (int j = 0; j < 4; j++) {
        game.next[i][j] = 0;
      }
    }
  }
  generate_next_figure(&game, &next_tetramino);
}

tetris_state return_state() { return current_state; }

void set_action(int user_input) {
  if (user_input == KEY_UP)
    action = Up;
  else if (user_input == KEY_DOWN)
    action = Down;
  else if (user_input == KEY_LEFT)
    action = Left;
  else if (user_input == KEY_RIGHT)
    action = Right;
  else if (user_input == ENTER_KEY)
    action = Start;
  else if (user_input == ESCAPE)
    action = Terminate;
  else if (user_input == PAUSE_KEY)
    action = Pause;
  else if (user_input == SPACE_KEY)
    action = Action;
  else
    action = -1;
}

void userInput(UserAction_t action, int hold) {
  if (hold != 0) return;

  switch (action) {
    case Up:
      break;
    case Down:
      movedown();
      break;
    case Right:
      moveright();
      break;
    case Left:
      moveleft();
      break;
    case Action:
      rotation();
      break;
    case Terminate:
      current_state = EXIT_STATE;
      break;
    case Pause:
      current_state = PAUSE;
      break;
    default:
      break;
  }
  print_map(&game);
}

GameInfo_t updateCurrentState() {
  clock_t current_time = clock() * 1000 / CLOCKS_PER_SEC;
  switch (current_state) {
    case START:
      on_start_state();
      break;
    case SPAWN:
      on_spawn_state();
      break;
    case PAUSE:
      on_pause_state();
      break;
    case MOVING:
      userInput(action, 0);
      if (current_time - last_shift_time >= shift_interval) {
        current_state = SHIFTING;
        last_shift_time = current_time;
      }
      break;
    case SHIFTING:
      on_shifting_state();
      break;
    case ATTACHING:
      on_attaching_state();
      break;
    case GAMEOVER:
      on_gameover_state();
      break;
    default:
      break;
  }
  return game;
}

void on_start_state() {
  switch (action) {
    case Start:
      gameInfo_init();
      print_stats(&game);
      current_state = SPAWN;
      break;
    case Terminate:
      current_state = EXIT_STATE;
      break;
    default:
      current_state = START;
      break;
  }
}

void on_pause_state() {
  switch (action) {
    case Pause:
      current_state = (current_state == PAUSE) ? MOVING : PAUSE;
      break;
    case Terminate:
      current_state = EXIT_STATE;
      break;
    default:
      current_state = PAUSE;
      break;
  }
}

void on_spawn_state() {
  current_tetramino.figure = next_tetramino;
  current_tetramino.x = SPAWN_X;
  current_tetramino.y = SPAWN_Y;
  place_figure(&game, current_tetramino);
  generate_next_figure(&game, &next_tetramino);
  print_next_figure(&game);
  print_map(&game);
  current_state = MOVING;
}

void on_shifting_state() {
  if (check_attaching(&game, current_tetramino)) {
    current_state = ATTACHING;
  } else {
    clear_figure(&game, current_tetramino);
    current_tetramino.y++;
    place_figure(&game, current_tetramino);
    current_state = MOVING;
    print_map(&game);
    print_stats(&game);
    print_next_figure(&game);
  }
}

void on_attaching_state() {
  if (current_tetramino.y <= 1) {
    current_state = GAMEOVER;
  } else {
    assemble_line(&game, current_tetramino);
    update_state(&game, &shift_interval);
    current_state = SPAWN;
  }
}

void moveleft() {
  if (!check_collide_left(&game, current_tetramino)) {
    clear_figure(&game, current_tetramino);
    current_tetramino.x--;
    place_figure(&game, current_tetramino);
  }
}

void moveright() {
  if (!check_collide_right(&game, current_tetramino)) {
    clear_figure(&game, current_tetramino);
    current_tetramino.x++;
    place_figure(&game, current_tetramino);
  }
}

void movedown() {
  while (!check_attaching(&game, current_tetramino)) {
    clear_figure(&game, current_tetramino);
    current_tetramino.y++;
    place_figure(&game, current_tetramino);
  }
}

void rotation() {
  if (can_rotate(&game, &current_tetramino)) {
    clear_figure(&game, current_tetramino);
    rotate_matrix(&current_tetramino.figure);
    place_figure(&game, current_tetramino);
  }
}

void on_gameover_state() {
  clear();
  refresh();
  clear_field(&game);
  print_end_message();
  print_overlay();
  save_high_score_if_needed(&game);
  current_state = START;
}