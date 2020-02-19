#include "game.h"

void Game::displayGame(RGBmatrixPanel* matrix) {
  for (int x = 0; x < BOARD_X; x++) {
    for (int y = 0; y < BOARD_Y; y++) {
      if (base[x][y]) {
        matrix->drawPixel(y + 3, x + 3, matrix->Color333(1, 1, 1));
      } else {
        matrix->drawPixel(y + 3, x + 3, matrix->Color333(0, 0, 0));
      }
    }
  }
  for (int y = 3; y < 13; y++) {
    matrix->drawPixel(27, y, matrix->ColorHSV(0, 150, 100, true));
    matrix->drawPixel(28, y, matrix->ColorHSV(0, 150, 100, true));
  }
  for (int i = 0; i < 4; i++) {
    if (piece.getLocation()[i][0] >= 0) {
      matrix->drawPixel(piece.getLocation()[i][1] + 3, piece.getLocation()[i][0] + 3, matrix->Color333(2, 0, 2));
    }
  }
}


void Game::newGame () {
  for (int x = 0; x < BOARD_X; x++) {
    for (int y = 0; y < BOARD_Y; y++) {
      base[x][y] = 0;
    }
  }
  findAdjacent();
}


bool Game::isGameover() {
  for (int x = 0; x < BOARD_X; x++) {
    if (base[x][24]) {
      return true;
    }
  }
  return false;
}

void Game::findAdjacent() {
  for (int x = 0; x < BOARD_X; x++) {
    if (isRowEmpty(x)) {
      base[x][0] = 1;
      return;
    }
    for (int y = 0; y < BOARD_Y; y++) {
      if (base[x][y] && !base[x][y + 1] && y <= BOARD_Y - 2) {
        adjacent[x][y + 1] = 1;
      } else {
        adjacent[x][y + 1] = 0;
      }
    }
  }
}


int** Game::initiateAdjacent() {
  int** arr = new int*[10];
  for (int i = 0; i < 10; i++) {
    arr[i] = new int[26];
  }
  return arr;
}