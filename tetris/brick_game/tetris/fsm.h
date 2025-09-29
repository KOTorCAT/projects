#ifndef FSM_H
#define FSM_H

#include <time.h>

#include "../../gui/cli/tetris_frontend.h"
#include "defines.h"
#include "objects.h"
#include "tetris_backend.h"

void gameInfo_init();
void set_action(int user_input);
tetris_state return_state();

void userInput(UserAction_t action, int hold);
GameInfo_t updateCurrentState();

#endif