#pragma once
const int waitTime = 16;
uint8_t lastuint8_t = 0;
uint8_t leftStack = 0;
uint8_t rightStack = 0;

uint8_t rotate_byte(uint8_t b, int r) {
  return (b << r) | (b >> (8 - r));
}

void pushLeftStack(uint8_t bitToPush) {
  leftStack = (leftStack << 1) ^ bitToPush ^ leftStack;
}
void pushRightStackRight(uint8_t bitToPush) {
  rightStack = (rightStack >> 1) ^ (bitToPush << 7) ^ rightStack;
}

uint8_t getTrueRotateRandomByte() {
  uint8_t finaluint8_t = 0;

  uint8_t lastStack = leftStack ^ rightStack;

  for (int i = 0; i < 4; i++) {
    delayMicroseconds(waitTime);
    int leftBits = analogRead(1);

    delayMicroseconds(waitTime);
    int rightBits = analogRead(1);

    finaluint8_t ^= rotate_byte(leftBits, i);
    finaluint8_t ^= rotate_byte(rightBits, 7 - i);

    for (int j = 0; j < 8; j++) {
      uint8_t leftBit = (leftBits >> j) & 1;
      uint8_t rightBit = (rightBits >> j) & 1;

      if (leftBit != rightBit) {
        if (lastStack % 2 == 0) {
          pushLeftStack(leftBit);
        } else {
          pushRightStackRight(leftBit);
        }
      }
    }

  }
  lastuint8_t ^= (lastuint8_t >> 3) ^ (lastuint8_t << 5) ^ (lastuint8_t >> 4);
  lastuint8_t ^= finaluint8_t;

  return lastuint8_t ^ leftStack ^ rightStack;
}
