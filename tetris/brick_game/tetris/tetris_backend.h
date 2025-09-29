#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <ncurses.h>
#include <stdlib.h>

#include "defines.h"
#include "objects.h"

void generate_next_figure(GameInfo_t* game, Tetromino* new_figure);
bool can_rotate();
void rotate_matrix(Tetromino* tet);
bool check_collision_on_spawn(GameInfo_t* game, tetramino_pos tet);
bool can_rotate(GameInfo_t* game, tetramino_pos* tet);
void place_figure(GameInfo_t* game, tetramino_pos tet);
void clear_figure(GameInfo_t* game, tetramino_pos tet);
void clear_field(GameInfo_t* game);
bool check_attaching(GameInfo_t* game, tetramino_pos tet);
bool check_collide_left(GameInfo_t* game, tetramino_pos tet);
bool check_collide_right(GameInfo_t* game, tetramino_pos tet);
void assemble_line(GameInfo_t* game, tetramino_pos tet);
void update_state(GameInfo_t* game, int* shift_interval);
void load_high_score(GameInfo_t* game);
void save_high_score_if_needed(GameInfo_t* game);

#endif