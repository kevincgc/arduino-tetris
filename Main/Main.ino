#include <RGBmatrixPanel.h>
#include "game.h"

#define CLK 11
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, true);

long counter = 0;
PieceType nextPiece;
Game game;

void setup() {
  int seed = (analogRead(A) + analogRead(B) + analogRead(C) + analogRead(A3) + analogRead(A4) + analogRead(A5) + analogRead(A6) + analogRead(A7) + analogRead(A8));
  randomSeed(seed);
  matrix.begin();
  Serial.begin(9600);
  Serial.print(seed);
  Serial.println("    Start");
  game.newGame();
//  printBase();
//  printAdjacent();
//  game.getBase()[0][0] = 1;
//  game.getBase()[0][5] = 1;
//  game.getBase()[3][2] = 1;
//  game.findAdjacent();
//  printBase();
//  printAdjacent();

}

void loop() {

    for (int x = 0; x < 32; x++) {
      for (int y = 0; y < 16; y++) {
        if (!(y > 2 && y < 13 && x > 2 && x < 29)) {
          matrix.drawPixel(x, y, matrix.ColorHSV(counter, 255, 75, true));
        }
      }
    }
    counter += 5;
  
    if (game.isGameover()) {
      Serial.println("Game Over!");
      printBase();
      printAdjacent();
      game.newGame();
      printBase();
      printAdjacent();
    } else {
      game.displayGame(&matrix);
      game.tick();
    }
    //printAdjacent();
  
    delay(20);
    matrix.swapBuffers(false);

}
void printBase() {
  int** adjacent = game.getBase();
  for (int y = 25; y >= 0; y--) {
    for (int x = 0; x < 10; x++) {
      if (adjacent[x][y]) {
        Serial.print("1");
      } else {
        Serial.print("0");
      }
    }
    Serial.print('\n');
  }
  Serial.print("==========================================================\n");

}

void printAdjacent() {
  int** adjacent = game.getAdjacent();
  for (int y = 25; y >= 0; y--) {
    for (int x = 0; x < 10; x++) {
      if (adjacent[x][y]) {
        Serial.print("1");
      } else {
        Serial.print("0");
      }
    }
    Serial.print('\n');
  }
  Serial.print("==========================================================\n");

}

//void drawBase() {
//  for(int i = 0; i < 32; i++) {
//    for(int j = 0; j < 16; j++) {
//      if (base[i][j]) {
//        matrix.drawPixel(i, j, matrix.Color333(7, 7, 7));
//      } else {
//        matrix.drawPixel(i, j, matrix.Color333(0, 0, 0));
//      }
//    }
//  }
//}
