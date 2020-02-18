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
    Piece(PieceType pieceType) {
      type = pieceType;
    }
    bool canMove(int* adjacent[10]) {
      for (int i = 0; i < 4; i++) {
        for (int x = 0; x < BOARD_X; x++) {
          if (location[i][0] == x && location[i][1] == *adjacent[x]) {
            return false;
          }
        }
      }
      return true;
    }
    void initiatePiece() {
      switch(type) {
        
      }
    }

  private:
    PieceType type;
    int location[4][2];
};
