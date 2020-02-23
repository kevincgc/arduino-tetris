#include "game.h"
#include "rng.h"

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
      adjacent[x][y] = 0;
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
    bool isPieceInCol = false;
    for (int y = 0; y < BOARD_Y - 2; y++) {
      isPieceInCol = isPieceInCol || base[x][y];
    }
    if (!isPieceInCol) {
      adjacent[x][0] = 1;
      continue;
    }
    if (base[x][0]) {
      adjacent[x][0] = 0;
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
    nextType = getTrueRotateRandomByte() % 7;
    if (nextType == lastType) {
      nextType = getTrueRotateRandomByte() % 7;
    }
    lastType = nextType;
    piece.initiatePiece(nextType);
    return;
  }
  //random(2) ? (canMoveRight() ? piece.moveRight() : delay(0)) : (canMoveLeft() ? piece.moveLeft() : delay(0));
  if (piece.canMoveDown(adjacent)) {
    piece.moveDown();
  } else {
    fixPiece();
    clearFullRows();
    piece.destroyPiece();
    findAdjacent();
  }
}

void Game::init() {
  newGame();
  piece.init();
  lastType = getTrueRotateRandomByte() % 7;
  nextType = getTrueRotateRandomByte() % 7;
}
