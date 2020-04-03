#include <RGBmatrixPanel.h>
#include "defines.h"
#include "game.h"
#include <SoftwareSerial.h>

#define CLK 11
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

const int UP_PIN = 2, DOWN_PIN = 3, LEFT_PIN = 18, RIGHT_PIN = 19, FAST_PIN = 20, SLOW_PIN = 21;
const int DISPLAY_REFRESH_RATE = 100;
SoftwareSerial lcd(3, 4);  // pin 4 = TX

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
long counter = 0;
PieceType nextPiece;
Game game;
volatile boolean upPressed, downPressed, leftPressed, rightPressed, fastPressed, slowPressed;
unsigned long prevTick, oldDisplayTime;
unsigned int tickRate;
int oldScore = -1, oldSpeed = 0;
bool printOnce = true;

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
  prevTick = millis();
  oldDisplayTime = millis();
  tickRate = 600;

  matrix.begin();
  lcd.begin(9600);
  lcd.write("test");
  lcd.write("                ");
  lcd.write("                ");
  Serial.begin(9600);
  Serial.println("Game start");
}

void loop() {
  if (!game.isGameover()) {
    if (upPressed || downPressed || leftPressed || rightPressed) {
      game.receiveInput(&upPressed, &downPressed, &leftPressed, &rightPressed);
    }
  }
  updateSpeed();

  if (millis() > prevTick + tickRate) {
    prevTick = millis();
    if (game.isGameover()) {
      if (printOnce) {
        printGameOver();
        printOnce = false;
      }
      if (upPressed || downPressed || leftPressed || rightPressed) {
        printOnce = true;
        game.newGame();
        updateLcd();
      }
    } else {
      game.tick();
    }
  }
  if (millis() > oldDisplayTime + DISPLAY_REFRESH_RATE) {
    drawBorder();
    game.displayGame(&matrix);
    oldDisplayTime = millis();
  }

  if (oldScore != game.getScore() || oldSpeed != tickRate) {
    updateLcd();
    oldScore = game.getScore();
    oldSpeed = tickRate;
    Serial.println(tickRate);
  }
}

void updateLcd() {
  char score[5];
  itoa(game.getScore(), score, 5);
  lcd.write(254);
  lcd.write(128);
  lcd.write("Score: ");
  lcd.write(score);
  lcd.write("     ");
  lcd.write(254);
  lcd.write(192);
  lcd.write("Speed: ");
  char spd[5];
  itoa(tickRate, spd, 5);
  lcd.write(spd);
  lcd.write("     ");
}

void printGameOver() {
  lcd.write(254);
  lcd.write(128);
  lcd.write("Game Over!");
  lcd.write(254);
  lcd.write(192);
  char score[5];
  itoa(game.getScore(), score, 5);
  lcd.write("Score: ");
  lcd.write(score);
}


//void printArr(int** arr) {
//  for (int y = 25; y >= 0; y--) {
//    for (int x = 0; x < 10; x++) {
//      if (arr[x][y]) {
//        Serial.print("1");
//      } else {
//        Serial.print("0");
//      }
//    }
//    Serial.print('\n');
//  }
//  Serial.print("==========================================================\n");
//}
//void printArr1(int** arr) {
//  for (int y = 25; y >= 0; y--) {
//    for (int x = 0; x < 10; x++) {
//      if (arr[x][y]) {
//        Serial.print("X");
//      } else {
//        Serial.print("O");
//      }
//    }
//    Serial.print('\n');
//  }
//  Serial.print("==========================================================\n");
//}

void drawBorder() {
  Color nextColor = (Color)game.getNextPieceType();
  for (int x = 0; x < 32; x++) {
    for (int y = 0; y < 16; y++) {
      if (!(y > 2 && y < 13 && x > 2 && x < 29)) {
        matrix.drawPixel(x, y, matrix.ColorHSV(HUE[nextColor], 255, 75, true));
      }
    }
  }
  //  for (int x = 0; x < 32; x++) {
  //    for (int y = 0; y < 16; y++) {
  //      if (gameSpeed == SLOW) {
  //        if (!(y > 2 && y < 13 && x > 2 && x < 29) && !(x < 2 || x > 29 || y < 2 || y > 13)) {
  //          matrix.drawPixel(x, y, matrix.ColorHSV(50000L, 255, 75, true));
  //        }
  //      }
  //      if (gameSpeed == NORMAL) {
  //        if (!(y > 2 && y < 13 && x > 2 && x < 29) && !(x < 1 || x > 30 || y < 1 || y > 14)) {
  //          matrix.drawPixel(x, y, matrix.ColorHSV(HUE[nextColor], 255, 75, true));
  //        }
  //      }
  //      if (gameSpeed == FAST) {
  //        if (!(y > 2 && y < 13 && x > 2 && x < 29)) {
  //          matrix.drawPixel(x, y, matrix.ColorHSV(150000L, 255, 75, true));
  //        }
  //      }
  //    }
  //  }
}
void updateSpeed() {
  if (fastPressed) {
    tickRate += 100;
    fastPressed = false;
  }
  if (slowPressed) {
    if (tickRate >= 300) {
      tickRate -= 100;
    } else if (tickRate >= 150) {
      tickRate -= 50;
    }
    slowPressed = false;
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
