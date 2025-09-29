#include "tetris_frontend.h"

#include "../../brick_game/tetris/tetris_backend.h"

void init_tetris_colors() {
  start_color();
  use_default_colors();

  init_color(COLOR_ORANGE, 1000, 500, 0);
  init_color(COLOR_PINK, 1000, 750, 900);
  init_color(8, 300, 300, 300);

  init_pair(COLOR_MY_RED, COLOR_MY_RED, -1);
  init_pair(COLOR_ORANGE, COLOR_ORANGE, -1);
  init_pair(COLOR_YELLOW, COLOR_YELLOW, -1);
  init_pair(COLOR_MAGENTA, COLOR_MAGENTA, -1);
  init_pair(COLOR_GREEN, COLOR_GREEN, -1);
  init_pair(COLOR_BLUE, COLOR_BLUE, -1);
  init_pair(COLOR_PINK, COLOR_PINK, -1);
  init_pair(COLOR_CYAN, COLOR_CYAN, -1);
  init_pair(COLOR_WHITE, COLOR_WHITE, -1);
  init_pair(8, 8, -1);
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  MVADDCH(top_y, left_x, ACS_ULCORNER);
  int i = left_x + 1;
  for (; i < right_x; i++) {
    MVADDCH(top_y, i, ACS_HLINE);
  }
  MVADDCH(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    MVADDCH(i, left_x, ACS_VLINE);
    MVADDCH(i, right_x, ACS_VLINE);
  }

  MVADDCH(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) {
    MVADDCH(bottom_y, i, ACS_HLINE);
  }
  MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void print_overlay(void) {
  print_rectangle(0, BOARD_N, 0, BOARD_M);
  print_rectangle(0, BOARD_N, BOARD_M + 1, BOARD_M + HUD_WIDTH + 3);

  print_rectangle(1, 4, BOARD_M + 5, BOARD_M + HUD_WIDTH);

  print_rectangle(5, 7, BOARD_M + 2, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(8, 10, BOARD_M + 2, BOARD_M + HUD_WIDTH + 2);
  print_rectangle(11, 13, BOARD_M + 2, BOARD_M + HUD_WIDTH + 2);

  MVPRINTW(6, BOARD_M + 5, "LEVEL");
  MVPRINTW(9, BOARD_M + 5, "SCORE");
  MVPRINTW(12, BOARD_M + 5, "SPEED");
  MVPRINTW(15, BOARD_M + 5, "HI-SCORE");

  MVPRINTW(3, BOARD_M + 25, "Esc - exit");
  MVPRINTW(5, BOARD_M + 25, "p - pause");
  MVPRINTW(7, BOARD_M + 25, "< - left ");
  MVPRINTW(9, BOARD_M + 25, "> - right");
  MVPRINTW(11, BOARD_M + 25, "v - hard down");
  MVPRINTW(13, BOARD_M + 25, "SPACE - rotation");
}

void print_map(GameInfo_t *game) {
  // Очищаем поле
  for (int i = 0; i < ROWS_MAP; i++) {
    for (int j = 0; j < COLS_MAP; j++) {
      MVADDCH(i + 1, j * 2 + 2, ' ');
      MVADDCH(i + 1, j * 2 + 3, ' ');
    }
  }

  for (int i = 0; i < ROWS_MAP; i++) {
    for (int j = 0; j < COLS_MAP; j++) {
      attron(COLOR_PAIR(8) | A_DIM);
      MVADDCH(i + 1, j * 2 + 2, ACS_PLUS);
      attroff(COLOR_PAIR(8) | A_DIM);

      if (game->field[i][j]) {
        attron(COLOR_PAIR(game->field[i][j]) | A_BOLD);
        MVADDCH(i + 1, j * 2 + 2, '[');
        MVADDCH(i + 1, j * 2 + 3, ']');
        attroff(COLOR_PAIR(game->field[i][j]) | A_BOLD);
      } else {
        MVADDCH(i + 1, j * 2 + 3, ' ');
      }
    }
  }

  for (int i = 0; i <= ROWS_MAP + 1; i++) {
    MVADDCH(i, 1, ACS_VLINE);
    MVADDCH(i, COLS_MAP * 2 + 2, ACS_VLINE);
  }
  for (int j = 1; j <= COLS_MAP * 2 + 2; j++) {
    MVADDCH(0, j, ACS_HLINE);
    MVADDCH(ROWS_MAP + 1, j, ACS_HLINE);
  }

  MVADDCH(0, 1, ACS_ULCORNER);
  MVADDCH(0, COLS_MAP * 2 + 2, ACS_URCORNER);
  MVADDCH(ROWS_MAP + 1, 1, ACS_LLCORNER);
  MVADDCH(ROWS_MAP + 1, COLS_MAP * 2 + 2, ACS_LRCORNER);
}

void print_end_message() {
  MVPRINTW(BOARD_N / 2, (BOARD_M - END_MESSAGE_LEN_1) / 2 + 1, END_MESSAGE_1);
  MVPRINTW(BOARD_N / 2 + 2, (BOARD_M - INTRO_MESSAGE_LEN_1) / 2 + 1,
           INTRO_MESSAGE_1);
  MVPRINTW(BOARD_N / 2 + 3, (BOARD_M - END_MESSAGE_LEN_2) / 2 + 1,
           END_MESSAGE_2);
}

void print_start_message() {
  MVPRINTW(BOARD_N / 2, (BOARD_M - INTRO_MESSAGE_LEN_1) / 2 + 1,
           INTRO_MESSAGE_1);
  MVPRINTW(BOARD_N / 2 + 1, (BOARD_M - INTRO_MESSAGE_LEN_2) / 2 + 1,
           INTRO_MESSAGE_2);
}

void print_next_figure(GameInfo_t *game) {
  for (int i = 0; i < ROWS_NEXT_FIGURE; i++) {
    for (int j = 0; j < COLS_NEXT_FIGURE; j++) {
      if (game->next[i][j]) {
        attron(COLOR_PAIR(game->next[i][j]) | A_BOLD);
        MVADDCH(i + 2, j * 2 + 7 + BOARD_M, '[');
        MVADDCH(i + 2, j * 2 + 8 + BOARD_M, ']');
        attroff(COLOR_PAIR(game->next[i][j]) | A_BOLD);
      } else {
        MVADDCH(i + 2, j * 2 + 7 + BOARD_M, ' ');
        MVADDCH(i + 2, j * 2 + 8 + BOARD_M, ' ');
      }
    }
  }
}

void print_stats(GameInfo_t *game) {
  MVPRINTW(6, BOARD_M + 12, "%d", game->level);
  MVPRINTW(9, BOARD_M + 12, "%d", game->score);
  MVPRINTW(12, BOARD_M + 12, "%d", game->speed);
  MVPRINTW(15, BOARD_M + 14, "%d", game->high_score);
}