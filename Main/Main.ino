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
    game.receiveInput(&upPressed, &downPressed, &leftPressed, &rightPressed);
  }

  if (millis() > prevTick + 1000) {
    prevTick = millis();
    if (game.isGameover()) {
      Serial.println("Game Over!");
      game.newGame();
    } else {
      game.tick();
    }
    //    printArr(game.getBase());
        printArr1(game.getAdjacent());
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
void printArr1(int** arr) {
  for (int y = 25; y >= 0; y--) {
    for (int x = 0; x < 10; x++) {
      if (arr[x][y]) {
        Serial.print("X");
      } else {
        Serial.print("O");
      }
    }
    Serial.print('\n');
  }
  Serial.print("==========================================================\n");
}

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
