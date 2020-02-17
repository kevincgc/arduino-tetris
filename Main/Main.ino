#include <RGBmatrixPanel.h>

#define CLK 11 
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
int base[32][16] = {};

void setup() {
  matrix.begin();
  Serial.begin(9600);
  Serial.println("Start");

}

void loop() {
  for(int i = 0; i < 32; i++) {
    for(int j = 0; j < 16; j++) {
      base[i][j] = random(2);
    }
  }

  drawBase();

  delay(3000);

}

void drawBase() {
  for(int i = 0; i < 32; i++) {
    for(int j = 0; j < 16; j++) {
      if (base[i][j]) {
        matrix.drawPixel(i, j, matrix.Color333(7, 7, 7));
      } else {
        matrix.drawPixel(i, j, matrix.Color333(0, 0, 0));
      }
    }
  }
}
