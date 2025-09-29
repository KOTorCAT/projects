#include "tetris.h"

int main(void) {
  WIN_INIT(0);
  setlocale(LC_ALL, "");
  srand(time(NULL));
  init_tetris_colors();
  print_overlay();
  print_start_message();
  game_loop();
  endwin();

  return SUCCESS;
}

void game_loop() {
  bool break_flag = TRUE;
  tetris_state state = return_state();

  while (break_flag) {
    updateCurrentState();
    state = return_state();
    if (state == EXIT_STATE) {
      break_flag = FALSE;
    } else if (state == MOVING || state == START || state == PAUSE) {
      set_action(GET_USER_INPUT);
    }
  }
}
