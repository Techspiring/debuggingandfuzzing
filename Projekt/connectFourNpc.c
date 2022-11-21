// Copyright 2019 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#include <stdio.h>
#include "./connectFourNpc.h"
#include "./connectFour.h"

uint16_t npcDoMove(const game_t * cg, uint16_t x) {
  if (x > 100)  // @@@
    return 0;
  uint16_t dropped = 0;
  // dropped = tryFinishGame(currentGame);
  if (!dropped)
    dropped = tryAvoidLoss(cg);
  // if (!dropped)
  //  dropped = tryAvoidTrap(currentGame);
  // if (!dropped)
  // dropped = tryCreateTrap(currentGame);
  if (!dropped)
    dropped  = 7;
    // Do sth. useful here!
  return dropped-1;
}
/*
uint16_t tryFinishGame(game_t *cG) {
  return 0;
}
*/
uint16_t tryAvoidLoss(const game_t *cG) {
  uint8_t tmpOponent;  // , tmpNpc;

  // Check for rows
  for (uint8_t x = 0; x < 6; x++) {
    for (uint8_t y = 0; y < sizeof(cG->player[0].stones)
                            /sizeof(cG->player[0].stones[0]);
    y++) {
      tmpOponent = cG->player[0].stones[y] >> x;
      // tmpNpc = cG->player[1].stones[y] >> x;
      printf("AI checking row %i, shift %i: %02x!\n", y, x, tmpOponent);
      if ((tmpOponent & 0x07) == 0x07) {
        // Got a horizonzal row of 3 - dangerous!
        printf("Found a row of 3!\n");
        // Try block right
        // Try block left
        return true;
      }
    }
  }
  return 0;
}
/*
uint16_t tryAvoidTrap(game_t *cG) {
  return 0;
}

uint16_t tryCreateTrap(game_t *cG) {
  return 0;
}
*/
