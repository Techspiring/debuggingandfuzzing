// Copyright 2019 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#ifndef CONNECTFOUR_H_
#define CONNECTFOUR_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct player player_t;
typedef struct game game_t;

typedef int16_t (*Fnct16_t) (const game_t *, uint16_t);
typedef bool (*rndrFnc) (const game_t *);

struct player {
  // ein uint8_t = eine Zeile
  uint8_t stones[6];
  Fnct16_t input_callback;
};

struct game {
  player_t player[2];
  uint8_t player_active;
  rndrFnc renderer;
};

bool registerInputHandler(Fnct16_t fnct, uint8_t playerId);
bool registerRenderHandler(rndrFnc fnct);
bool initConnectFour(void);
bool clearField(void);
bool playConnectFour(void);
bool dropStone(player_t *p, uint16_t column);
bool checkWin(player_t *p);
bool checkDraw(void);
game_t *getGameState(void);

bool exportGameToFile(char *filename);
bool importGameFromFile(char *filename);

bool setSaveFile(char *filename);

#endif  // CONNECTFOUR_H_
