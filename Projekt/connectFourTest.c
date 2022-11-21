// Copyright 2019 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "./connectFour.h"

int main(void) {
  initConnectFour();

  // Check for return of valid gameState
  game_t *g = getGameState();

  // Check that field is empty
  for (uint8_t line = 0; line < 6; line++) {
    assert(!(g->player[0].stones[line]|g->player[0].stones[line]));
  }

  assert(dropStone(&g->player[0], 0));
  assert((g->player[0].stones[0]|g->player[1].stones[0]) == 0x40);

  assert(dropStone(&g->player[1], 1));
  assert((g->player[0].stones[0]|g->player[1].stones[0]) == 0x60);

  assert(dropStone(&g->player[0], 2));
  assert(dropStone(&g->player[1], 3));
  assert(dropStone(&g->player[0], 4));
  assert(dropStone(&g->player[1], 5));
  assert(dropStone(&g->player[0], 6));

  assert((g->player[0].stones[0] | g->player[1].stones[0]) == 0x7F);
  assert(!(g->player[0].stones[0] & g->player[1].stones[0]));

  // Clear stuff
  initConnectFour();

  // Check "checkWin" in all combinations
  assert(!checkWin(&g->player[0]));
  assert(!checkWin(&g->player[1]));
  g->player[0].stones[0] = 0x0F;
  assert(checkWin(&g->player[0]));
  assert(!checkWin(&g->player[1]));
  g->player[0].stones[0] = 0x78;
  assert(checkWin(&g->player[0]));
  // To be continued

  // Check loading/Saving
  exportGameToFile("test1.four");
  clearField();
  importGameFromFile("test1.four");
  exportGameToFile("test2.four");

  // Compare imported file to exported one ..
  FILE *fihnd = fopen("test1.four", "rb");
  if (!fihnd) {
    printf("Die Datei 'test1.four' kann nicht geoeffnet werden. \n");
    return false;
  }


  FILE *fohnd = fopen("test2.four", "rb");
  if (!fohnd) {
    printf("Die Datei 'test2.four' kann nicht geoeffnet werden.\n");
    fclose(fihnd);
    return false;
  }
  char tmp[2] = {0};
  while (1) {
    tmp[0] = fgetc(fihnd);
    tmp[1] = fgetc(fohnd);
    assert(tmp[0] == tmp[1]);

    if (tmp[0] == EOF)
      break;
  }

  fclose(fihnd);
  fclose(fohnd);

  // Cleaning up
  remove("test1.four");
  remove("test2.four");

  return 0;
}
