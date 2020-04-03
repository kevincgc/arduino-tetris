#include "game.h"
#include "rng.h"



void Game::displayGame(RGBmatrixPanel* matrix) {
  if (!isGameover()) {
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
      matrix->drawPixel(27, y, matrix->ColorHSV(190, 150, 70, true));
      matrix->drawPixel(28, y, matrix->ColorHSV(190, 150, 70, true));
    }
    for (int i = 0; i < 4; i++) {
      if (piece.getLocation()[i][0] >= 0) {
        matrix->drawPixel(piece.getLocation()[i][1] + 3, piece.getLocation()[i][0] + 3, matrix->ColorHSV(HUE[lastType], 255, 75, true));
      }
    }
  }
}


void Game::newGame () {
  for (int x = 0; x < BOARD_X; x++) {
    for (int y = 0; y < BOARD_Y; y++) {
      base[x][y] = 0;
      adjacent[x][y] = 0;
    }
  }
  findAdjacent();
  score = 0;
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
    if (base[x][0]) {
      adjacent[x][0] = 0;
    } else {
      adjacent[x][0] = 1;
    }
    for (int y = 0; y < BOARD_Y; y++) {
      if (base[x][y] && !base[x][y + 1]) {
        adjacent[x][y + 1] = 1;
      } else {
        adjacent[x][y + 1] = 0;
      }
    }
  }
}


int** Game::initiateArray() {
  int** arr = new int*[BOARD_X];
  for (int i = 0; i < BOARD_X; i++) {
    arr[i] = new int[BOARD_Y];
  }
  for (int x = 0; x < BOARD_X; x++) {
    for (int y = 0; y < BOARD_Y; y++) {
      arr[x][y] = 0;
    }
  }
  return arr;
}

void Game::tick() {
  if (!piece.isPieceExist()) {
    lastType = nextType;
    nextType = getTrueRotateRandomByte() % 7;
    if (nextType == lastType) {
      nextType = getTrueRotateRandomByte() % 7;
    }
    piece.initiatePiece(lastType);
    return;
  }
  if (piece.canMoveDown(adjacent)) {
    piece.moveDown();
  } else {
    fixPiece();
    clearFullRows();
    piece.destroyPiece();
    findAdjacent();
  }
}

Game::Game() {
  base = initiateArray();
  location = piece.getLocation();
  adjacent = initiateArray();
  newGame();
  lastType = getTrueRotateRandomByte() % 7;
  nextType = getTrueRotateRandomByte() % 7;
}
