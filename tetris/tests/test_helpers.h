#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "../brick_game/tetris/objects.h"

GameInfo_t create_test_game();
void free_test_game(GameInfo_t *game);

#endif