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
    int** initiateAdjacent();
    int** getPieceLoc() {
      return piece.getLocation();
    }
    int** getAdjacent() {
      return adjacent;
    }
    int** getBase() {
      return base;
    }
    Game() {
      location = piece.getLocation();
      adjacent = initiateAdjacent();
      base = initiateAdjacent();
    }

    void clearFullRows () {
      for (int y = 0; y < BOARD_Y; y++) {
        bool isFull = 1;
        for (int x = 0; x < BOARD_X; x++) {
          isFull &= base[x][y];
        }
        if (isFull) {
          clearRow(y);
        }
      }
    }

    void tick() {
      if (!piece.isPieceExist()) {
        piece.initiatePiece(random(7));
        return;
      }
      random(2) ? (canMoveRight() ? piece.moveRight() : delay(0)) : (canMoveLeft() ? piece.moveLeft() : delay(0));
      if (piece.canMoveDown(adjacent)) {
        piece.moveDown();
      } else {
        fixPiece();
        clearFullRows();
        piece.destroyPiece();
        findAdjacent();
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


    Piece piece;
//    int base[10][26] =
//    {
//      {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//      {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
//    };

    int** base;
    int** adjacent;
    const int** location;
};
