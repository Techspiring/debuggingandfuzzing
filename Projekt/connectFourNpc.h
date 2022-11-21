// Copyright 2019 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#ifndef CONNECTFOURNPC_H_
#define CONNECTFOURNPC_H_

#include <stdint.h>
#include <stdbool.h>
#include "./connectFour.h"

uint16_t npcDoMove(const game_t *, uint16_t);

// If pair of 3 exists and can be finished to pair of 4
// uint16_t tryFinishGame(game_t *);

// If opponent has pair of 3 that could cause hi to win next round - destroy
uint16_t tryAvoidLoss(const game_t *);

// uint16_t tryAvoidTrap(game_t *);

// uint16_t tryCreateTrap(game_t *);

#endif  // CONNECTFOURNPC_H_
