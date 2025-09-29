#include <ncurses.h>

#include "objects.h"

const Tetromino TETROMINOES[7] = {
    /* I-фигура */
    {.shape = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},
     .width = 4,
     .height = 3,
     .color = COLOR_CYAN},
    /* J-фигура */
    {.shape = {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}},
     .width = 3,
     .height = 3,
     .color = COLOR_BLUE},
    /* L-фигура */
    {.shape = {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}},
     .width = 3,
     .height = 3,
     .color = COLOR_WHITE},
    /* O-фигура */
    {.shape = {{1, 1}, {1, 1}}, .width = 2, .height = 2, .color = COLOR_YELLOW},
    /* S-фигура */
    {.shape = {{0, 1, 1}, {1, 1, 0}},
     .width = 3,
     .height = 2,
     .color = COLOR_GREEN},
    /* T-фигура */
    {.shape = {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}},
     .width = 3,
     .height = 3,
     .color = COLOR_MAGENTA},
    /* Z-фигура */
    {.shape = {{1, 1, 0}, {0, 1, 1}},
     .width = 3,
     .height = 2,
     .color = COLOR_RED}};