#include <RGBmatrixPanel.h>
#include "defines.h"
#include "game.h"

#define CLK 11
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

const int UP_PIN = 2, DOWN_PIN = 3, LEFT_PIN = 18, RIGHT_PIN = 19, FAST_PIN = 20, SLOW_PIN = 21;
const int DISPLAY_REFRESH_RATE = 100;
const int TICK_RATE[] = {800, 600, 400};


RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
long counter = 0;
PieceType nextPiece;
Game game;
volatile boolean upPressed, downPressed, leftPressed, rightPressed, fastPressed, slowPressed;
unsigned long prevTick, oldDisplayTime;
GameSpeed gameSpeed;

void setup() {
  pinMode(UP_PIN, INPUT);
  pinMode(DOWN_PIN, INPUT);
  pinMode(LEFT_PIN, INPUT);
  pinMode(RIGHT_PIN, INPUT);
  pinMode(FAST_PIN, INPUT);
  pinMode(SLOW_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(UP_PIN), upISR, RISING);
  attachInterrupt(digitalPinToInterrupt(DOWN_PIN), downISR, RISING);
  attachInterrupt(digitalPinToInterrupt(LEFT_PIN), leftISR, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_PIN), rightISR, RISING);
  attachInterrupt(digitalPinToInterrupt(FAST_PIN), fastISR, RISING);
  attachInterrupt(digitalPinToInterrupt(SLOW_PIN), slowISR, RISING);
  gameSpeed = NORMAL;
  prevTick = millis();
  oldDisplayTime = millis();

  matrix.begin();
  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  if (upPressed || downPressed || leftPressed || rightPressed) {
    game.receiveInput(&upPressed, &downPressed, &leftPressed, &rightPressed);
  }
  updateSpeed();

  if (millis() > prevTick + TICK_RATE[gameSpeed]) {
    prevTick = millis();
    if (game.isGameover()) {
      Serial.println("Game Over!");
      game.newGame();
    } else {
      game.tick();
    }
    //    printArr(game.getBase());
    //printArr1(game.getAdjacent());
  }
  if (millis() > oldDisplayTime + DISPLAY_REFRESH_RATE) {
    drawBorder();
    game.displayGame(&matrix);
    oldDisplayTime = millis();
  }
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

void drawBorder() {
  Color nextColor = (Color)game.getNextPieceType();
  for (int x = 0; x < 32; x++) {
    for (int y = 0; y < 16; y++) {
      if (gameSpeed == SLOW) {
        if (!(y > 2 && y < 13 && x > 2 && x < 29) && !(x < 2 || x > 29 || y < 2 || y > 13)) {
          matrix.drawPixel(x, y, matrix.ColorHSV(50000L, 255, 75, true));
        }
      }
      if (gameSpeed == NORMAL) {
        if (!(y > 2 && y < 13 && x > 2 && x < 29) && !(x < 1 || x > 30 || y < 1 || y > 14)) {
          matrix.drawPixel(x, y, matrix.ColorHSV(HUE[nextColor], 255, 75, true));
        }
      }
      if (gameSpeed == FAST) {
        if (!(y > 2 && y < 13 && x > 2 && x < 29)) {
          matrix.drawPixel(x, y, matrix.ColorHSV(150000L, 255, 75, true));
        }
      }
    }
  }
}
void updateSpeed() {
  if (fastPressed) {
    if (gameSpeed != FAST) gameSpeed = gameSpeed + 1;
    fastPressed = false;
    drawBorder();
  }
  if (slowPressed) {
    if (gameSpeed != SLOW) gameSpeed = gameSpeed - 1;
    fastPressed = false;
    drawBorder();
  }
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
void fastISR() {
  fastPressed = true;
}
void slowISR() {
  slowPressed = true;
}
