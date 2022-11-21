// Copyright 2019 Kevin Mader
// Author: Kevin Mader <mail@kevin-mader.de>

#include <stdio.h>
#include <string.h>
#include "./connectFour.h"
#include "./connectFourNpc.h"
#include "./connectFourGles.h"

int main(int argc, char *argv[]) {
  initConnectFour();

  if (argc > 1) {
    for (uint8_t i = 1; i < argc; i++) {
      if (!strcmp(argv[i], "--help")) {
        printf("*==================== Vier Gewinnt ====================*\n");
        printf("| Regeln:                                              |\n");
        printf("| - Abwechselnd werfen die Spieler Steine in das Feld. |\n");
        printf("| - Der Spieler der als erster eine Reihe mit 4        |\n");
        printf("|   Steinen aneinander (vertikal, horizontal oder      |\n");
        printf("|   diagonal) erreicht hat das Spiel gewonnen.         |\n");
        printf("*------------------------------------------------------*\n");
        printf("| Parameter:                                           |\n");
        printf("| - '--help' zeigt diesen Hilfe-Dialog an              |\n");
        printf("| - '--gl' startet das Spiel im OpenGL-Modus           |\n");
        printf("| - '--ai' startet ein Spiel gegen einen NPC           |\n");
        printf("| - '-load=FILE' läd einen gespeicherten Spielstand    |\n");
        printf("|   aus der Datei FILE.                                |\n");
        printf("| - '-save=FILE' erlaubt das speichern eines aktiven   |\n");
        printf("|   Spielstands in die Datei FILE. Wird keine Datei    |\n");
        printf("|   angegeben, wird der Spielstand in current.four     |\n");
        printf("|   gespeichert.                                       |\n");
        printf("*------------------------------------------------------*\n");
        printf("| Bedienung:                                           |\n");
        printf("|  Im Textmodus:                                       |\n");
        printf("|  - '0' beendet das Spiel                             |\n");
        printf("|  - '1'-'7' wirft einen Stein in die gewaehlte Reihe, |\n");
        printf("|    wenn in selbiger ein Platz frei ist.              |\n");
        printf("|  - '9' speichert das aktuelle Spiel.                 |\n");
        printf("|  Im Open-GL Modus:                                   |\n");
        printf("|  - Der Stein wird bei einem Linksklick in die        |\n");
        printf("|    gewaehlte Spalte geworfen, wenn platz ist.        |\n");
        printf("|  - Mit Rechtsklick wird der Spielstand gespeichert.  |\n");
        printf("*------------------------------------------------------*\n");
        printf("| Credits:                                             |\n");
        printf("| - Author: Kevin Mader <mail@kevin-mader.de>          |\n");
        printf("| - No support for this, enjoy and optimize yourself.  |\n");
        printf("| - Abschlussprojekt zu 'Programmieren in C' SS2019.   |\n");
        printf("*==================== Vier Gewinnt ====================*\n");
        return 0;
      }
      if (!strcmp(argv[i], "--ai")) {
        printf("Die AI ist leider (noch) nicht implementiert.\n");
        // registerInputHandler(npcDoMove, 1);
      }
      if (!strcmp(argv[i], "--gl")) {
        printf("Now working in OpenGL-Mode\n");
        initOpenGl();
        registerRenderHandler(glesRenderGame);
        registerInputHandler(glesPlayerInput, 0);
        registerInputHandler(glesPlayerInput, 1);
      }
      if (!strncmp(argv[i], "-load=", 6)) {
        importGameFromFile(argv[i]+6);
      }
      if (!strncmp(argv[i], "-save=", 6)) {
        setSaveFile(argv[i]+6);
      }
    }
  }

  playConnectFour();

  return 0;
}
