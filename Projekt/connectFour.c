// Copyright 2019 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#include <stdio.h>
#include <string.h>
#include "./connectFour.h"

game_t cGame;
char saveFile[50] = "current.four";

uint16_t readCharAsU16(void) {
  uint16_t res = 0;
  char c = ' ';
  while (c != '\n') {
    c = getchar();
    if (c >= '0' && c <= '9') {
      res *= 10;
      res += (c - '0');
    }
  }
  return res;
}

// Default callback for the game - can be overwritten by application
// e.g. for games against NPCs or OpenGL
int16_t playerInput(const game_t *cg, uint16_t x) {
  printf("Spieler %i, wo moechtest Du einen Stein einwerfen? ", x);
  return readCharAsU16()-1;
}

bool drawField(const game_t *cg) {
  printf("\n| 1 | 2 | 3 | 4 | 5 | 6 | 7 |");
  printf("\n|---|---|---|---|---|---|---|\n");
  for (uint8_t y = 0; y < 6; y++) {
    for (uint8_t x = 0; x < 7; x++) {
      printf("|");
      if ((cg->player[0].stones[5-y]) & (uint8_t)(0x40 >> x)) {
        printf(" o ");
      } else if ((cg->player[1].stones[5-y]) & (uint8_t)(0x40 >> x)) {
        printf(" x ");
      } else {
        printf("   ");
      }
    }
    printf("|\n");
  }
  printf("|---|---|---|---|---|---|---|\n\n");
  return true;
}

bool registerInputHandler(Fnct16_t fnct, uint8_t playerId) {
  if (playerId > 1 || !fnct)
    return false;

  cGame.player[playerId].input_callback = fnct;
  return true;
}

bool registerRenderHandler(rndrFnc fnct) {
  if (!fnct)
    return false;

  cGame.renderer = fnct;
  return true;
}

bool initConnectFour(void) {
  cGame.player[0].input_callback = playerInput;
  cGame.player[1].input_callback = playerInput;
  cGame.renderer = drawField;
  cGame.player_active = 0;
  clearField();
  return true;
}

bool clearField(void) {
  for (uint8_t i = 0; i < 6; i++) {
    cGame.player[0].stones[i] = 0;
    cGame.player[1].stones[i] = 0;
  }
  return true;
}

bool playConnectFour(void) {
  int16_t column = 0;
  cGame.renderer(&cGame);
  while (1) {
    column = cGame.player[cGame.player_active].input_callback(&cGame,
              cGame.player_active+1);
    if (column == -1) {
      printf("Das Spiel wurde vorzeitig abgebrochen.\n");
      break;
    } else if (column == 8) {
      exportGameToFile(saveFile);
      continue;
    }

    if (dropStone(&cGame.player[cGame.player_active], column)) {
      cGame.renderer(&cGame);

      if (checkWin(&cGame.player[cGame.player_active])) {
        printf("Spieler %i hat gewonnen!\n", 1+cGame.player_active);
        return true;
      }

      if (checkDraw()) {
        printf("Das Spiel ist zu Ende, unentschieden!\n");
        return false;
      }

      cGame.player_active = 1 - cGame.player_active;
    }
  }

  // Should never get here, I guess
  return false;
}

bool dropStone(player_t *p, uint16_t column) {
  if (column > 6)
    return false;

  // Schauen ob die Spalte noch frei ist.
  if ((cGame.player[0].stones[5] | cGame.player[1].stones[5])
      & (uint8_t)(0x40 >> column)) {
    printf("Ungueliger Zug, Spalte %i ist voll.\n", column+1);
    return false;
  }

  // Drop stone to lowest position possible
  for (uint8_t i = 0; i < 6; i++) {
    if (!((cGame.player[0].stones[i] | cGame.player[1].stones[i])
        & (uint8_t)(0x40 >> column))) {
      p->stones[i] += (uint8_t)(0x40 >> column);
      return true;
    }
  }

  // If we got here, sth. fucked up.
  return false;
}

bool checkWin(player_t *p) {
  uint8_t tmp8;
  for (uint8_t x = 0; x < 5; x++) {
    for (uint8_t y = 0; y < sizeof(p->stones)/sizeof(p->stones[0]); y++) {
      tmp8 = p->stones[y] >> x;
      if ((tmp8 & 0x0F) == 0x0F) {
        // Got a horizonzal row of four - win
        return true;
      }
    }
  }

  for (uint8_t y = 0; y < (sizeof(p->stones)/sizeof(p->stones[0]))-3; y++) {
    // Checking vertical rows
    tmp8 = p->stones[y] & p->stones[y+1] & p->stones[y+2] & p->stones[y+3];

    // Checking diagonal rows / down
    if (!tmp8)
      tmp8 = p->stones[y] & p->stones[y+1] >> 1
           & p->stones[y+2] >> 2 & p->stones[y+3] >> 3;

    // Checking diagonal rows \ down
    if (!tmp8)
      tmp8 = p->stones[y] >> 3 & p->stones[y+1] >> 2
           & p->stones[y+2] >> 1 & p->stones[y+3];

    // If we found any pair - win!
    if (tmp8)
      return true;
  }

  return false;
}


bool checkDraw(void) {
  if (checkWin(&cGame.player[0]) || checkWin(&cGame.player[1]))
    return false;

  if ((cGame.player[0].stones[5]|cGame.player[1].stones[5]) == 0x7F)
    return true;

  return false;
}

bool exportGameToFile(char *filename) {
  FILE *fhnd;
  fhnd = fopen(filename, "wb");
  if (!fhnd) {
    printf("Die Datei '%s' kann nicht geoeffnet werden.", filename);
    return false;
  }

  for (uint8_t row=0; row < 6; row++) {
    for (uint8_t col = 0; col < 7; col++) {
      if (cGame.player[0].stones[5-row] & (0x40 >> col)) {
        fputc('1', fhnd);
      } else if (cGame.player[1].stones[5-row] & (0x40 >> col)) {
        fputc('2', fhnd);
      } else {
        fputc('.', fhnd);
      }
    }
    fputc('\n', fhnd);
  }
  fclose(fhnd);
  printf("Spielstand gespeichert in '%s'.\n", filename);
  return true;
}

bool importGameFromFile(char *filename) {
  FILE *fhnd;
  char tmp = 0;
  clearField();

  fhnd = fopen(filename, "rb");
  if (!fhnd) {
    printf("Die Datei '%s' kann nicht geoeffnet werden.", filename);
    return false;
  }

  uint8_t row = 0;
  uint8_t col = 0;
  uint8_t stones = 0;
  while (1) {
    tmp = fgetc(fhnd);

    if (tmp == EOF) {
      cGame.player_active = stones % 2;
      break;
    }

    if (tmp == '.') {
      col++;
      continue;
    }

    if (tmp == '1' || tmp == '2') {
      if (col > 6 || row > 5) {
        printf("Die Datei '%s' ist kein gueliger Spielstand.", filename);
        clearField();
        break;
      }
      cGame.player[tmp - '1'].stones[5-row] |= (0x40 >> col);
      col++;
      stones++;
      continue;
    }

    if (tmp == '\n' && col > 0) {
      col = 0;
      row++;
      continue;
    }
  }

  fclose(fhnd);
  printf("'%s' geoeffnet.\n", filename);
  return false;
}

game_t *getGameState(void) {
  return &cGame;
}

bool setSaveFile(char *filename) {
  char *tmp = filename;
  uint8_t len = 0;
  while (len < 49 || *tmp == 0) {
    tmp++;
    len++;
  }
  printf("Setting save file from '%s' to '%s", saveFile, filename);
  memcpy(saveFile, filename, len+1);
  return true;
}
