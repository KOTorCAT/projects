#include <stdlib.h>

#include "../brick_game/tetris/defines.h"
#include "../brick_game/tetris/objects.h"

GameInfo_t create_test_game() {
  GameInfo_t game;
  game.field = calloc(ROWS_MAP, sizeof(int *));
  for (int i = 0; i < ROWS_MAP; i++) {
    game.field[i] = calloc(COLS_MAP, sizeof(int));
  }

  game.next = calloc(ROWS_NEXT_FIGURE, sizeof(int *));
  for (int i = 0; i < ROWS_NEXT_FIGURE; i++) {
    game.next[i] = calloc(COLS_NEXT_FIGURE, sizeof(int));
  }

  game.score = 0;
  game.level = 1;
  game.speed = 100;
  game.high_score = 0;
  game.pause = 0;

  return game;
}

void free_test_game(GameInfo_t *game) {
  if (game->field) {
    for (int i = 0; i < ROWS_MAP; i++) {
      if (game->field[i]) {
        free(game->field[i]);
      }
    }
    free(game->field);
    game->field = NULL;
  }

  if (game->next) {
    for (int i = 0; i < ROWS_NEXT_FIGURE; i++) {
      if (game->next[i]) {
        free(game->next[i]);
      }
    }
    free(game->next);
    game->next = NULL;
  }
}