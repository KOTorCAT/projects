#ifndef DEFINES_H
#define DEFINES_H

#define WIN_INIT(time)    \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    keypad(stdscr, TRUE); \
    timeout(time);        \
  }

#define GET_USER_INPUT getch()

#define MVPRINTW(y, x, ...) \
  mvprintw(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), __VA_ARGS__)
#define MVADDCH(y, x, c) mvaddch(BOARDS_BEGIN + (y), BOARDS_BEGIN + (x), c)

#define HIGH_SCORE_INFO "high_score.txt"

#define INTRO_MESSAGE_1 "Press ENTER"
#define INTRO_MESSAGE_LEN_1 11
#define INTRO_MESSAGE_2 "to start!"
#define INTRO_MESSAGE_LEN_2 9

#define END_MESSAGE_1 "GAMEOVER"
#define END_MESSAGE_LEN_1 8
#define END_MESSAGE_2 "to restart"
#define END_MESSAGE_LEN_2 10

#define ROWS_MAP 20
#define COLS_MAP 10

#define ROWS_NEXT_FIGURE 2
#define COLS_NEXT_FIGURE 4

#define BOARDS_BEGIN 2

#define BOARD_N (ROWS_MAP + 1)
#define BOARD_M (COLS_MAP * 2 + 1)
#define HUD_WIDTH 16

#define SUCCESS 0
#define ERROR 1

#define NO_INPUT -1

#define ESCAPE 27
#define ENTER_KEY 10
#define PAUSE_KEY 'p'
#define SPACE_KEY ' '

#define COLOR_ORANGE 9
#define COLOR_PINK 213
#define COLOR_MY_RED 196

#define SPAWN_X 3
#define SPAWN_Y 0

#define INITIAL_TIMEOUT 1100

#endif