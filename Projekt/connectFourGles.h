// Copyright 2019 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#ifndef CONNECTFOURGLES_H_
#define CONNECTFOURGLES_H_

#include <stdint.h>
#include <stdbool.h>
#include "./connectFour.h"

typedef struct d2_double {
  double x;
  double y;
} d2_double_t;

typedef struct d2_int32 {
  int32_t x;
  int32_t y;
} d2_int32_t;

int8_t initOpenGl(void);
int8_t destroyOpenGl(void);

bool glesRenderGame(const game_t *cg);
int16_t glesPlayerInput(const game_t *cg, uint16_t x);

#endif  // CONNECTFOURGLES_H_
