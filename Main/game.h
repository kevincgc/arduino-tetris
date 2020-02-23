#include <RGBmatrixPanel.h>

#include "piece.h"
#define BOARD_X 10
#define BOARD_Y 26

class Game {
  public:
    bool isGameover();
    void displayGame(RGBmatrixPanel* matrix);
    void newGame ();
    void findAdjacent();
    int** initiateArray();
    int** getPieceLoc() {
      return piece.getLocation();
    }
    int** getAdjacent() {
      return adjacent;
    }
    int** getBase() {
      return base;
    }
    Game();

    void clearFullRows () {
      int y = 0;
      while (y < BOARD_Y - 1) {
        bool isFull = true;
        for (int x = 0; x < BOARD_X; x++) {
          isFull &= base[x][y];
        }
        if (isFull) {
          clearRow(y);
        } else {
          y++;
        }
      }
    }

    void tick();

    void receiveInput(bool* up, bool* down, bool* left, bool* right) {
      if (*left) {
        if (canMoveLeft()) piece.moveLeft();
        *left = false;
      }
      if (*right) {
        if (canMoveRight()) piece.moveRight();
        *right = false;
      }
      if (*down) {
        while (piece.canMoveDown(adjacent)) {
          piece.moveDown();
        }
        *down = false;
      }
      if (*up) {
        if (piece.canRotate(base)) {
          piece.rotate();
        }
        *up = false;
      }
    }

  private:
    void clearRow(int y_del) {
      for (int y = y_del; y < BOARD_Y - 1; y++) {
        for (int x = 0; x < BOARD_X; x++) {
          base[x][y] = base[x][y + 1];
        }
      }
      for (int x = 0; x < BOARD_X; x++) {
        base[x][25] = 0;
      }
    }
    void fixPiece() {
      for (int i = 0; i < 4; i++) {
        base[location[i][0]][location[i][1]] = 1;
      }
    }
    bool canMoveRight() {
      for (int i = 0; i < 4; i++) {
        if (location[i][0] + 1 > BOARD_X - 1) {
          return false;
        }
      }
      for (int i = 0; i < 4; i++) {
        if (base[location[i][0] + 1][location[i][1]]) {
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
      for (int i = 0; i < 4; i++) {
        if (base[location[i][0] - 1][location[i][1]]) {
          return false;
        }
      }
      return true;
    }
    bool canRotate() {

    }

    PieceType lastType, nextType;
    Piece piece;
    int** base;
    int** adjacent;
    const int** location;
};
