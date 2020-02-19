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

    bool isPieceExist() {
      return pieceExist;
    }


  private:
    PieceType type = random(7), nextType = random(7);
    int** location;
    bool pieceExist;
};
