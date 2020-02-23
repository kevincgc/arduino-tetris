#include "Arduino.h"
#define BOARD_X 10
#define BOARD_Y 26

enum PieceType {
  I,
  O,
  J,
  L,
  S,
  Z,
  T
};

class Piece {
  public:
    int** initiateLocation();
    bool canMoveDown(const int** adjacent);
    Piece() {
      location = initiateLocation();
      destroyPiece();
    }

    int** getLocation() {
      return location;
    }
    void moveDown() {
      for (int i = 0; i < 4; i++) {
        location[i][1] -= 1;
      }
    }
    void destroyPiece() {
      for (int i = 0; i < 4; i++) {
        location[i][0] = -1;
      }
      pieceExist = false;
    }

    void initiatePiece(PieceType next);

    bool canMoveRight() {
      for (int i = 0; i < 4; i++) {
        if (location[i][0] + 1 > BOARD_X - 1) {
          return false;
        }
      }
      return true;
    }
    bool canMoveLeft() {
      for (int i = 0; i < 4; i++) {
        if (location[i][0] - 1 < 0) {
          return false;
        }
      }
      return true;
    }
    void moveLeft() {
      if (canMoveLeft()) {
        for (int i = 0; i < 4; i++) {
          location[i][0] -= 1;
        }
      }
    }

    void moveRight() {
      if (canMoveRight()) {
        for (int i = 0; i < 4; i++) {
          location[i][0] += 1;
        }
      }
    }

    bool canRotate(const int** base) {
      Serial.print("Type: ");
      Serial.print(type);
      Serial.print('\n');
      bool ret;
      switch (type) {
        case I:
          if (location[1][0] >= 2 && location[1][0] <= 8 && location[1][1] <= 23) {
            ret = true;
          } else {
            ret = false;
          }
          break;
        case O:
          ret = false;
          break;
        default:
          if (location[1][0] >= 1 && location[1][0] <= 8 && location[1][1] <= 24) {
            ret = true;
          } else {
            ret = false;
          }
      }
      for (int i = 0; i < 4; i++) {
        if (base[location[i][0]][location[i][1]]) {
          ret = false;
        }
      }
      return ret;
    }

    void rotate() {
      switch (type) {
        case I:
          if (!orientation) {
            location[0][0] = location[1][0];
            location[2][0] = location[1][0];
            location[3][0] = location[1][0];
            location[0][1] = location[1][1] - 1;
            location[2][1] = location[1][1] + 1;
            location[3][1] = location[1][1] + 2;
            orientation = 1;
            break;
          } else {
            location[0][0] = location[1][0] + 1;
            location[2][0] = location[1][0] - 1;
            location[3][0] = location[1][0] - 2;
            location[0][1] = location[1][1];
            location[2][1] = location[1][1];
            location[3][1] = location[1][1];
            orientation = 0;
            break;
          }
        case J:
          if (orientation == 0 || orientation == 2) {
            location[0][0] = location[1][0];
            location[2][0] = location[1][0];
            location[0][1] = location[1][1] - 1;
            location[2][1] = location[1][1] + 1;
          }
          if (orientation == 0) {
            location[3][0] = location[1][0] - 1;
            location[3][1] = location[1][1] - 1;
            orientation = 1;
            break;
          }
          if (orientation == 2) {
            location[3][0] = location[1][0] + 1;
            location[3][1] = location[1][1] + 1;
            orientation = 3;
            break;
          }
          if (orientation == 1 || orientation == 3) {
            location[0][0] = location[1][0] - 1;
            location[2][0] = location[1][0] + 1;
            location[0][1] = location[1][1];
            location[2][1] = location[1][1];
          }
          if (orientation == 1) {
            location[3][0] = location[1][0] - 1;
            location[3][1] = location[1][1] + 1;
            orientation = 2;
            break;
          }
          if (orientation == 3) {
            location[3][0] = location[1][0] + 1;
            location[3][1] = location[1][1] - 1;
            orientation = 0;
            break;
          }
        case L:
          if (orientation == 0 || orientation == 2) {
            location[0][0] = location[1][0];
            location[2][0] = location[1][0];
            location[0][1] = location[1][1] - 1;
            location[2][1] = location[1][1] + 1;
          }
          if (orientation == 0) {
            location[3][0] = location[1][0] - 1;
            location[3][1] = location[1][1] + 1;
            orientation = 1;
            break;
          }
          if (orientation == 2) {
            location[3][0] = location[1][0] + 1;
            location[3][1] = location[1][1] - 1;
            orientation = 3;
            break;
          }
          if (orientation == 1 || orientation == 3) {
            location[0][0] = location[1][0] - 1;
            location[2][0] = location[1][0] + 1;
            location[0][1] = location[1][1];
            location[2][1] = location[1][1];
          }
          if (orientation == 1) {
            location[3][0] = location[1][0] + 1;
            location[3][1] = location[1][1] + 1;
            orientation = 2;
            break;
          }
          if (orientation == 3) {
            location[3][0] = location[1][0] - 1;
            location[3][1] = location[1][1] - 1;
            orientation = 0;
            break;
          }
        case S:
          if (!orientation) {
            location[0][0] = location[1][0];
            location[2][0] = location[1][0] + 1;
            location[3][0] = location[1][0] + 1;
            location[0][1] = location[1][1] + 1;
            location[2][1] = location[1][1];
            location[3][1] = location[1][1] - 1;
            orientation = 1;
            break;
          } else {
            location[0][0] = location[1][0] + 1;
            location[2][0] = location[1][0];
            location[3][0] = location[1][0] - 1;
            location[0][1] = location[1][1];
            location[2][1] = location[1][1] - 1;
            location[3][1] = location[1][1] - 1;
            orientation = 0;
            break;
          }
        case Z:
          if (!orientation) {
            location[0][0] = location[1][0];
            location[2][0] = location[1][0] + 1;
            location[3][0] = location[1][0] + 1;
            location[0][1] = location[1][1] - 1;
            location[2][1] = location[1][1];
            location[3][1] = location[1][1] + 1;
            orientation = 1;
            break;
          } else {
            location[0][0] = location[1][0] - 1;
            location[2][0] = location[1][0];
            location[3][0] = location[1][0] + 1;
            location[0][1] = location[1][1];
            location[2][1] = location[1][1] - 1;
            location[3][1] = location[1][1] - 1;
            orientation = 0;
            break;
          }
        case T:
          if (orientation == 0 || orientation == 2) {
            location[0][0] = location[1][0];
            location[2][0] = location[1][0];
            location[0][1] = location[1][1] - 1;
            location[2][1] = location[1][1] + 1;
          }
          if (orientation == 0) {
            location[3][0] = location[1][0] - 1;
            location[3][1] = location[1][1];
            orientation = 1;
            break;
          }
          if (orientation == 2) {
            location[3][0] = location[1][0] + 1;
            location[3][1] = location[1][1];
            orientation = 3;
            break;
          }
          if (orientation == 1 || orientation == 3) {
            location[0][0] = location[1][0] - 1;
            location[2][0] = location[1][0] + 1;
            location[0][1] = location[1][1];
            location[2][1] = location[1][1];
          }
          if (orientation == 1) {
            location[3][0] = location[1][0];
            location[3][1] = location[1][1] + 1;
            orientation = 2;
            break;
          }
          if (orientation == 3) {
            location[3][0] = location[1][0];
            location[3][1] = location[1][1] - 1;
            orientation = 0;
            break;
          }
      }
    }

    bool isPieceExist() {
      return pieceExist;
    }


  private:
    PieceType type;
    int** location;
    bool pieceExist;
    int orientation;
};
