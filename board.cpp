#include "board.h"
#include <QIcon>

Board::Board() {}

void Board::FillMap() {
  map = {{0, 2, 0, 2, 0, 2, 0, 2}, {2, 0, 2, 0, 2, 0, 2, 0},
         {0, 2, 0, 2, 0, 2, 0, 2}, {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}, {1, 0, 1, 0, 1, 0, 1, 0},
         {0, 1, 0, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0, 1, 0}};

  mapOfSymbols = {{"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8"},
                  {"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7"},
                  {"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6"},
                  {"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5"},
                  {"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4"},
                  {"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3"},
                  {"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2"},
                  {"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"}

  };
}

void Board::SetFiguresOnBoard() {
  QIcon whiteChecker = QIcon(":/source/img/whiteChecker.svg");
  QIcon blackChecker = QIcon(":/source/img/blackChecker.svg");
  QIcon blackQueen = QIcon(":/source/img/blackQueen.svg");
  QIcon whiteQueen = QIcon(":/source/img/whiteQueen.svg");
  for (int i = 0; i < mapSize; i++) {
    for (int j = 0; j < mapSize; j++) {
      if (map[i][j] == 1)
        buttonsOnBoard[i][j]->setIcon(whiteChecker);
      else if (map[i][j] == 2)
        buttonsOnBoard[i][j]->setIcon(blackChecker);
      else if (map[i][j] == 3)
        buttonsOnBoard[i][j]->setIcon(whiteQueen);
      else if (map[i][j] == 4)
        buttonsOnBoard[i][j]->setIcon(blackQueen);
      else
        buttonsOnBoard[i][j]->setIcon(QIcon());
      buttonsOnBoard[i][j]->setIconSize(QSize(cellSize - 25, cellSize - 25));
    }
  }
}
