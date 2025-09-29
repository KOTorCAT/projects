#ifndef OBJECTS_H
#define OBJECTS_H
#include "defines.h"

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef enum {
  START = 0,
  PAUSE,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  EXIT_STATE
} tetris_state;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef struct {
  int shape[4][4];
  int width;
  int height;
  int color;
} Tetromino;

typedef struct {
  Tetromino figure;
  int x;
  int y;
} tetramino_pos;

extern const Tetromino TETROMINOES[7];

#endif