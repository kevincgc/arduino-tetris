#include <RGBmatrixPanel.h>
#include "piece.h"
#define BOARD_X 10
#define BOARD_Y 26

class Game {
  public:
    void newGame (int* base[10][26]) {
      for (int x = 0; x < BOARD_X; x++) {
        for (int y = 0; y < BOARD_Y; y++) {
          *base[x][y] = 0;
        }
      }
    }
    void clearFullRows (int* base[10][26]) {
      for (int y = 0; y < BOARD_Y; y++) {
        bool isFull = 1;
        for (int x = 0; x < BOARD_X; x++) {
          isFull &= *base[x][y];
        }
        if (isFull) {
          clearRow(base, y);
        }
      }
    }
    void findAdjacent(const int* base[10][26], int* adjacent[10]) {
      for (int x = 0; x < BOARD_X; x++) {
        int index;
        for (int y = BOARD_Y - 1; y >= 0; y--) {
          index = y;
          if (*base[x][y]) {
            break;
          }
        }
        *adjacent[x] = index + 1;
      }
    }
    bool isGameover(const int* base[10][26]) {
      for (int x = 0; x < BOARD_X; x++) {
        if (*base[x][25]) {
          return true;
        }
        return false;
      }
    }
    void displayGame(int* base[10][26], RGBmatrixPanel* matrix) {
      for (int x = 0; x < BOARD_X; x++) {
        for (int y = 0; y < BOARD_Y; y++) {
          if (base[x][y]) {
            matrix->drawPixel(y + 3, x + 3, matrix->Color333(4, 4, 4));
          } else {
            matrix->drawPixel(y + 3, x + 3, matrix->Color333(0, 0, 0));
          }
        }
      }
    }
    void tick() {
      
    }


  private:
    void clearRow(int* base[10][26], int y_del) {
      for (int y = y_del; y < BOARD_Y - 1; y++) {
        for (int x = 0; x < BOARD_X; x++) {
          *base[x][y] = *base[x][y + 1];
        }
      }
      for (int x = 0; x < BOARD_X; x++) {
        *base[x][25] = 0;
      }
    }
    int base[10][26] = {};
    int adjacent[10] = {};
    //    int** getBase() {
    //      return base[10][26];
    //    }
};
