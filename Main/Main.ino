#include <RGBmatrixPanel.h>
#include "game.h"

#define CLK 11
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

long counter = 0;
PieceType nextPiece;
Game game;
const int UP_PIN = 2, DOWN_PIN = 3, LEFT_PIN = 18, RIGHT_PIN = 19, MODE_PIN = 20;
volatile boolean upPressed, downPressed, leftPressed, rightPressed, fastMode;
unsigned long prevTick;

void setup() {
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
  pinMode(MODE_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(UP_PIN), upISR, RISING);
  attachInterrupt(digitalPinToInterrupt(DOWN_PIN), downISR, RISING);
  attachInterrupt(digitalPinToInterrupt(LEFT_PIN), leftISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_PIN), rightISR, RISING);
  attachInterrupt(digitalPinToInterrupt(MODE_PIN), modeISR, CHANGE);
  matrix.begin();
  Serial.begin(9600);
  Serial.println("Start");
  prevTick = millis();
  game.init();
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

  if (upPressed || downPressed || leftPressed || rightPressed) {
    if (upPressed) {
      Serial.println("up");
    }
    if (downPressed) {
      Serial.println("down");
    }
    if (leftPressed) {
      Serial.println("left");
    }
    if (rightPressed) {
      Serial.println("right");
    }
    game.receiveInput(&upPressed, &downPressed, &leftPressed, &rightPressed);
  }

  if (millis() > prevTick + 30) {
    prevTick = millis();
    if (game.isGameover()) {
      Serial.println("Game Over!");
      game.newGame();
    } else {
      game.tick();
    }
  }

  game.displayGame(&matrix);
}

void printArr(int** arr) {
  for (int y = 25; y >= 0; y--) {
    for (int x = 0; x < 10; x++) {
      if (arr[x][y]) {
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


void upISR() {
  upPressed = true;
}
void downISR() {
  downPressed = true;
}
void leftISR() {
  leftPressed = true;
}
void rightISR() {
  rightPressed = true;
}
void modeISR() {
  fastMode = !fastMode;
}
