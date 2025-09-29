#include "tetris_backend.h"

void generate_next_figure(GameInfo_t* game, Tetromino* new_figure) {
  int type = rand() % 7;
  *new_figure = TETROMINOES[type];

  for (int i = 0; i < ROWS_NEXT_FIGURE; i++) {
    for (int j = 0; j < COLS_NEXT_FIGURE; j++) {
      game->next[i][j] = 0;
    }
  }

  for (int i = 0; i < new_figure->height; i++) {
    for (int j = 0; j < new_figure->width; j++) {
      if (new_figure->shape[i][j]) {
        game->next[i][j] = new_figure->color;
      }
    }
  }
}

bool check_collision_on_spawn(GameInfo_t* game, tetramino_pos tet) {
  for (int i = 0; i < tet.figure.height; i++) {
    for (int j = 0; j < tet.figure.width; j++) {
      if (tet.figure.shape[i][j] &&
          (tet.y + i >= ROWS_MAP || tet.x + j < 0 || tet.x + j >= COLS_MAP ||
           (tet.y + i >= 0 && game->field[tet.y + i][tet.x + j]))) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

void clear_field(GameInfo_t* game) {
  for (int i = 0; i < ROWS_MAP; i++) {
    for (int j = 0; j < COLS_MAP; j++) {
      game->field[i][j] = 0;
    }
  }
}

void place_figure(GameInfo_t* game, tetramino_pos tet) {
  for (int i = 0; i < tet.figure.height && i + tet.y < ROWS_MAP; i++) {
    for (int j = 0; j < tet.figure.width && j + tet.x < COLS_MAP; j++) {
      if (tet.figure.shape[i][j]) {
        game->field[i + tet.y][j + tet.x] = tet.figure.color;
      }
    }
  }
}

void clear_figure(GameInfo_t* game, tetramino_pos tet) {
  for (int i = 0; i < tet.figure.height && i + tet.y < ROWS_MAP; i++) {
    for (int j = 0; j < tet.figure.width && j + tet.x < COLS_MAP; j++) {
      if (tet.figure.shape[i][j]) {
        game->field[i + tet.y][j + tet.x] = 0;
      }
    }
  }
}

bool check_attaching(GameInfo_t* game, tetramino_pos tet) {
  bool rc = FALSE;
  if (game->field == NULL) {
    return FALSE;
  }
  clear_figure(game, tet);

  for (int i = 0; i < tet.figure.height && i + tet.y < ROWS_MAP; i++) {
    for (int j = 0; j < tet.figure.width && j + tet.x < COLS_MAP; j++) {
      if (tet.figure.shape[i][j]) {
        if (i + tet.y == ROWS_MAP - 1 ||
            game->field[i + tet.y + 1][j + tet.x]) {
          rc = TRUE;
        }
      }
    }
  }
  place_figure(game, tet);
  return rc;
}

bool check_collide_left(GameInfo_t* game, tetramino_pos tet) {
  bool rc = FALSE;
  clear_figure(game, tet);
  for (int i = 0; i < tet.figure.width; i++) {
    for (int j = 0; j < tet.figure.height; j++) {
      if (tet.figure.shape[j][i]) {
        if (i + tet.x == 0 || game->field[tet.y + j][tet.x + i - 1]) {
          rc = TRUE;
        }
      }
    }
  }
  place_figure(game, tet);
  return rc;
}

bool check_collide_right(GameInfo_t* game, tetramino_pos tet) {
  bool rc = FALSE;
  clear_figure(game, tet);
  for (int i = 0; i < tet.figure.width; i++) {
    for (int j = 0; j < tet.figure.height; j++) {
      if (tet.figure.shape[j][i]) {
        if (i + tet.x == COLS_MAP - 1 ||
            game->field[tet.y + j][tet.x + i + 1]) {
          rc = TRUE;
        }
      }
    }
  }
  place_figure(game, tet);
  return rc;
}

bool can_rotate(GameInfo_t* game, tetramino_pos* tet_pos) {
  int rc = TRUE;
  tetramino_pos temp_tet;
  temp_tet.figure.width = tet_pos->figure.width;
  temp_tet.figure.height = tet_pos->figure.height;
  temp_tet.figure.color = tet_pos->figure.color;
  temp_tet.x = tet_pos->x;
  temp_tet.y = tet_pos->y;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      temp_tet.figure.shape[i][j] = tet_pos->figure.shape[i][j];
    }
  }
  clear_figure(game, *tet_pos);
  rotate_matrix(&temp_tet.figure);

  for (int i = 0; i < temp_tet.figure.height; i++) {
    for (int j = 0; j < temp_tet.figure.width; j++) {
      if (temp_tet.figure.shape[i][j]) {
        int new_x = temp_tet.x + j;
        int new_y = temp_tet.y + i;

        if (new_x < 0 || new_x >= COLS_MAP || new_y < 0 || new_y >= ROWS_MAP ||
            game->field[new_y][new_x]) {
          rc = FALSE;
        }
      }
    }
  }
  place_figure(game, *tet_pos);
  return rc;
}

void rotate_matrix(Tetromino* tet) {
  int temp[4][4] = {0};

  for (int i = 0; i < tet->height; i++) {
    for (int j = 0; j < tet->width; j++) {
      temp[tet->width - 1 - j][i] = tet->shape[i][j];
    }
  }
  for (int i = 0; i < tet->width; i++) {
    for (int j = 0; j < tet->height; j++) {
      tet->shape[i][j] = temp[i][j];
    }
  }
  int old_width = tet->width;
  tet->width = tet->height;
  tet->height = old_width;
}

void assemble_line(GameInfo_t* game, tetramino_pos tet) {
  int add_score = 0;
  for (int i = tet.y; i < ROWS_MAP; i++) {
    bool is_line = TRUE;
    for (int j = 0; j < COLS_MAP; j++) {
      if (!game->field[i][j]) {
        is_line = FALSE;
      }
    }
    if (is_line) {
      add_score = add_score * 2 + 100;
      for (int j = 0; j < COLS_MAP; j++) {
        game->field[i][j] = 0;
      }
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < COLS_MAP; j++) {
          game->field[k][j] = game->field[k - 1][j];
        }
      }
    }
  }
  game->score += add_score;
}

void update_state(GameInfo_t* game, int* shift_interval) {
  if (game->level < 10) {
    game->level = (game->score / 600) + 1;
    game->speed = game->level * 100;
  }
  *shift_interval = 1000 - game->speed;
  if (*shift_interval < 100) *shift_interval = 100;

  if (game->score >= game->high_score) {
    game->high_score = game->score;
  }
}

void load_high_score(GameInfo_t* game) {
  FILE* file = fopen(HIGH_SCORE_INFO, "r");
  if (file == NULL) {
    file = fopen(HIGH_SCORE_INFO, "w");
    if (file != NULL) {
      fprintf(file, "0");
      fclose(file);
    }
    game->high_score = 0;
    return;
  }

  char buffer[32];
  if (fgets(buffer, sizeof(buffer), file) != NULL) {
    game->high_score = atoi(buffer);
  } else {
    game->high_score = 0;
  }

  fclose(file);
}

void save_high_score_if_needed(GameInfo_t* game) {
  if (game->score >= game->high_score) {
    game->high_score = game->score;
    FILE* file = fopen(HIGH_SCORE_INFO, "w");
    if (file != NULL) {
      fprintf(file, "%d", game->high_score);
      fclose(file);
    }
  }
}