#include "piece.h"

int** Piece::initiateLocation() {
  int** newLocation = new int*[4];
  for (int i = 0; i < 4; i++) {
    newLocation[i] = new int[2];
  }
  return newLocation;
}

bool Piece::canMoveDown(const int** adjacent) {
  for (int i = 0; i < 4; i++) {
    if (adjacent[location[i][0]][location[i][1]]) {
      return false;
    }
  }
  return true;
}

void Piece::initiatePiece(PieceType next) {
  type = nextType;
  nextType = next;
  switch (type) {
    case I:
      location[0][0] = 3;
      location[1][0] = 4;
      location[2][0] = 5;
      location[3][0] = 6;
      location[0][1] = 25;
      location[1][1] = 25;
      location[2][1] = 25;
      location[3][1] = 25;
      break;
    case O:
      location[0][0] = 4;
      location[1][0] = 4;
      location[2][0] = 5;
      location[3][0] = 5;
      location[0][1] = 25;
      location[1][1] = 26;
      location[2][1] = 25;
      location[3][1] = 26;
      break;
    case J:
      location[0][0] = 4;
      location[1][0] = 5;
      location[2][0] = 6;
      location[3][0] = 6;
      location[0][1] = 26;
      location[1][1] = 26;
      location[2][1] = 26;
      location[3][1] = 25;
      break;
    case L:
      location[0][0] = 4;
      location[1][0] = 5;
      location[2][0] = 6;
      location[3][0] = 6;
      location[0][1] = 25;
      location[1][1] = 25;
      location[2][1] = 25;
      location[3][1] = 26;
      break;
    case S:
      location[0][0] = 6;
      location[1][0] = 5;
      location[2][0] = 5;
      location[3][0] = 4;
      location[0][1] = 26;
      location[1][1] = 26;
      location[2][1] = 25;
      location[3][1] = 25;
      break;
    case Z:
      location[0][0] = 4;
      location[1][0] = 5;
      location[2][0] = 5;
      location[3][0] = 6;
      location[0][1] = 26;
      location[1][1] = 26;
      location[2][1] = 25;
      location[3][1] = 25;
      break;
    case T:
      location[0][0] = 4;
      location[1][0] = 5;
      location[2][0] = 5;
      location[3][0] = 6;
      location[0][1] = 26;
      location[1][1] = 26;
      location[2][1] = 25;
      location[3][1] = 26;
      break;
  }
  pieceExist = true;
}
