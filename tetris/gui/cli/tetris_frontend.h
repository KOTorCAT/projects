#ifndef TETRIS_FRONTEND_H
#define TETRIS_FRONTEND_H

#include <ncurses.h>
#include <string.h>

#include "../../brick_game/tetris/defines.h"
#include "../../brick_game/tetris/objects.h"

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
void print_overlay(void);
void print_start_message();
void print_end_message();
void print_map(GameInfo_t *game);
void print_next_figure(GameInfo_t *game);
void print_stats(GameInfo_t *game);
void init_tetris_colors();

#endif